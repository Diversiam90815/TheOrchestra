/*
  ==============================================================================

	Module			OrchestraVoice
	Description		Custom voice that picks which dynamic layer & round-robin is being played

  ==============================================================================
*/

#include "OrchestraVoice.h"


bool OrchestraVoice::canPlaySound(juce::SynthesiserSound *sound)
{
	return dynamic_cast<OrchestraSound *>(sound) != nullptr;
}


void OrchestraVoice::startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound *sound, int currentPitchWheelPosition)
{
	if (auto *orchestraSound = dynamic_cast<OrchestraSound *>(sound))
	{
		noteNumber			 = midiNoteNumber;
		sourceSamplePosition = 0.0;
		isPlaying			 = true;

		numDynamicLayers	 = orchestraSound->dynamicLayers.size();

		layerBuffers.clear();

		// For each dynamic layer in the sound, pick a round-robin sample:
		for (int d = 0; d < orchestraSound->dynamicLayers.size(); ++d)
		{
			auto *layer = orchestraSound->dynamicLayers[d];
			if (layer == nullptr)
				continue;

			int rrIndex = pickRoundRobin(orchestraSound, d);

			// store a pointer to that buffer
			if (rrIndex >= 0 && rrIndex < layer->roundRobinSamples.size())
			{
				layerBuffers.push_back(layer->roundRobinSamples[rrIndex]);
			}
			else
			{
				// no valid sample found
				layerBuffers.push_back(nullptr);
			}
		}

		// Pitch shifting
		const double semitToneShift = static_cast<double>(midiNoteNumber - orchestraSound->getRootNote());
		pitchRatio					= std::pow(2.0, semitToneShift / 12.0); // If root note = midiNoteNumber, pitch ratio = 1.0 => no shift

		noteGain					= velocity;
	}

	// Init the CC values
	auto sampleRate = getSampleRate();
	CC1.reset(sampleRate, 0.005);
	CC11.reset(sampleRate, 0.005);
}


void OrchestraVoice::stopNote(float velocity, bool allowTailOff)
{
	if (allowTailOff)
	{
		// for now stop immediately
	}

	clearCurrentNote();
	isPlaying = false;
}


void OrchestraVoice::pitchWheelMoved(int newPitchWheelValue)
{
}


void OrchestraVoice::controllerMoved(int controllerNumber, int newControllerValue)
{
	if (controllerNumber == 1)
	{
		CC1.setTargetValue((float)newControllerValue);
	}

	else if (controllerNumber == 11)
	{
		CC11.setTargetValue((float)newControllerValue);
	}
}


void OrchestraVoice::renderNextBlock(juce::AudioBuffer<float> &outputBuffer, int startSample, int numSamples)
{
	if (!isPlaying || layerBuffers.empty())
		return;

	float	 *outLeft	= outputBuffer.getWritePointer(0, startSample);
	float	 *outRight	= (outputBuffer.getNumChannels() > 1) ? outputBuffer.getWritePointer(1, startSample) : nullptr;

	float	  dynPos	= mapCC1ToDynamicPosition(); // If CC1 = 64 in [0..127], that might be about ~1.5, which is halfway between layer 1 and layer 2, etc.

	const int numLayers = (int)layerBuffers.size();
	int		  i			= (int)std::floor(dynPos);	 // lower layer index
	int		  j			= i + 1;					 // upper layer index above
	int		  alpha		= dynPos - (float)i;		 // How much to crossfade to the upper

	// Ensure indices valid limits
	if (i < 0)
	{
		i	  = 0;
		alpha = 0.0f;
	}

	if (j >= numLayers)
	{
		j	  = numLayers - 1;
		alpha = 0.0f;
	}

	// We'll read from buffer i and buffer j
	const juce::AudioBuffer<float> *bufferI = layerBuffers[i];
	const juce::AudioBuffer<float> *bufferJ = layerBuffers[j];

	// Basic safety checks
	if (bufferI == nullptr && bufferJ == nullptr)
	{
		clearCurrentNote();
		isPlaying = false;
		return;
	}

	const int bufISize	= (bufferI != nullptr) ? bufferI->getNumSamples() : 0;
	const int bufIChans = (bufferI != nullptr) ? bufferI->getNumChannels() : 0;
	const int bufJSize	= (bufferJ != nullptr) ? bufferJ->getNumSamples() : 0;
	const int bufJChans = (bufferJ != nullptr) ? bufferJ->getNumChannels() : 0;

	while (--numSamples >= 0)
	{
		const int	pos		   = (int)sourceSamplePosition;
		const float frac	   = (float)(sourceSamplePosition - pos);
		const float invFrac	   = 1.0f - frac;

		// expression from CC11
		float		cc11Value  = CC11.getNextValue();
		float		expression = cc11Value / 127.f;
		float		amp		   = noteGain * expression;

		if (pos + 1 >= bufISize && pos + 1 >= bufJSize)	// If we exceed both buffers' lengths, time to stop
		{
			clearCurrentNote();
			isPlaying = false;
			break;
		}

		// read from bufferI if valid
		float li = 0.f, ri = 0.f;
		if (bufferI != nullptr && pos + 1 < bufISize)
		{
			auto *inL = bufferI->getReadPointer(0);
			li		  = inL[pos] * invFrac + inL[pos + 1] * frac;

			if (bufIChans > 1)
			{
				auto *inR = bufferI->getReadPointer(1);
				ri		  = inR[pos] * invFrac + inR[pos + 1] * frac;
			}
		}

		// read from bufferJ if valid
		float lj = 0.f, rj = 0.f;
		if (bufferJ != nullptr && pos + 1 < bufJSize)
		{
			auto *inL = bufferJ->getReadPointer(0);
			lj		  = inL[pos] * invFrac + inL[pos + 1] * frac;

			if (bufJChans > 1)
			{
				auto *inR = bufferJ->getReadPointer(1);
				rj		  = inR[pos] * invFrac + inR[pos + 1] * frac;
			}
		}

		// crossfade between i and j
		float lMix = li * (1.f - alpha) + lj * alpha;
		float rMix = ri * (1.f - alpha) + rj * alpha;

		// scale by amplitude
		lMix *= amp;
		rMix *= amp;

		// add to output
		*outLeft++ += lMix;
		if (outRight != nullptr)
			*outRight++ += rMix;

		// move forward
		sourceSamplePosition += pitchRatio;
	}
}


int OrchestraVoice::pickDynamicLayer(OrchestraSound *orchestraSound, float velocity)
{
	// dummy demo : if v <= 0.5 -> layer 0 ; else -> last layer

	if (orchestraSound->dynamicLayers.size() == 0)
		return -1;

	if (velocity < 0.5f)
		return 0;

	else
		return orchestraSound->dynamicLayers.size() - 1;
}


int OrchestraVoice::pickRoundRobin(OrchestraSound *orchestraSound, int dynamicIndex)
{
	if (dynamicIndex < 0 || dynamicIndex >= orchestraSound->dynamicLayers.size())
		return -1;

	auto *layer = orchestraSound->dynamicLayers[dynamicIndex];

	if (layer->roundRobinSamples.size() == 0)
		return -1;

	// Pick next RR in a static counter
	static int rrCounter = 0;
	int		   rrIndex	 = rrCounter % layer->roundRobinSamples.size();
	rrCounter++;

	return rrIndex;
}


const juce::AudioBuffer<float> *OrchestraVoice::getBuffer(OrchestraSound *orchestraSound, int dynamicIndex, int rrIndex)
{
	if (dynamicIndex < 0 || dynamicIndex >= orchestraSound->dynamicLayers.size())
		return nullptr;

	auto *layer = orchestraSound->dynamicLayers[dynamicIndex];

	if (rrIndex < 0 || rrIndex >= layer->roundRobinSamples.size())
		return nullptr;

	return layer->roundRobinSamples[rrIndex];
}


float OrchestraVoice::mapCC1ToDynamicPosition()
{
	// Get normalized current CC1 value
	float currentCC1 = CC1.getNextValue();
	float normCC1	 = currentCC1 / 127.0f;

	// Get Number of Dynamic Layers
	int	  n			 = numDynamicLayers;
	if (n < 1)
		return -1;

	// Determine "Dynamic Layer Position" -> Currently evenly distributed
	float layerPosition = normCC1 * (n - 1);
	return layerPosition;
}
