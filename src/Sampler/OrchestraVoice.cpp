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
		noteNumber					= midiNoteNumber;
		sourceSamplePosition		= 0.0;
		isPlaying					= true;

		// Choose Dynamic Layer
		chosenDynamicIndex			= pickDynamicLayer(orchestraSound, velocity);

		// Choose Round Robin
		chosenRoundRobinIndex		= pickRoundRobin(orchestraSound, chosenDynamicIndex);

		// Get the buffer
		currentBuffer				= getBuffer(orchestraSound, chosenDynamicIndex, chosenRoundRobinIndex);

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
	if (!isPlaying || currentBuffer == nullptr)
		return;

	const int	 bufferSize		  = currentBuffer->getNumSamples();
	const int	 numInputChannels = currentBuffer->getNumChannels();

	float		*outLeft		  = outputBuffer.getWritePointer(0, startSample);
	float		*outRight		  = (outputBuffer.getNumChannels() > 1) ? outputBuffer.getWritePointer(1, startSample) : nullptr;

	const float *inLeft			  = currentBuffer->getReadPointer(0);
	const float *inRight		  = (numInputChannels > 1) ? currentBuffer->getReadPointer(1) : nullptr;


	while (--numSamples >= 0)
	{
		int	  pos		 = (int)sourceSamplePosition;
		float alpha		 = (float)(sourceSamplePosition - pos);
		float invAlpha	 = 1.0f - alpha;
		float cc11Value	 = CC11.getNextValue();
		float expression = cc11Value / 127.0f; // Normalized CC11 value between [0,1]


		// Stop the note if we exceed the buffer size
		if (pos + 1 >= bufferSize)
		{
			clearCurrentNote();
			isPlaying = false;
			break;
		}

		// Basic linear interpolation
		float l = inLeft[pos] * invAlpha + inLeft[pos + 1] * alpha;
		float r = 0.0f;

		if (inRight)
		{
			r = inRight[pos] * invAlpha + inRight[pos + 1] * alpha;
		}

		float amp = noteGain * expression;

		l *= amp;
		r *= amp;

		if (outLeft)
		{
			*outLeft++ += l;
		}
		if (outRight)
		{
			*outRight++ += r;
		}
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


float OrchestraVoice::mapCC1ToDynamicPosition(OrchestraSound *orchestraSound)
{
	// Get normalized current CC1 value
	float currentCC1 = CC1.getNextValue();
	float normCC1	 = currentCC1 / 127.0f;

	// Get Number of Dynamic Layers
	int	  n			 = orchestraSound->dynamicLayers.size();
	if (n == 0)
		return -1;

	// Determine "Dynamic Layer Position" ->
	float layerPosition = normCC1 * (n - 1);
	return layerPosition;
}
