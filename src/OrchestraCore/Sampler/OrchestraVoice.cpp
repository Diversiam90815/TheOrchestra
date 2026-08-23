/*
  ==============================================================================
	Module			OrchestraVoice
	Description		Custom voice that picks which dynamic layer & round-robin is being played
  ==============================================================================
*/

#include "OrchestraVoice.h"


OrchestraVoice::OrchestraVoice(const ControllerState *controllerState) : mControllerState(controllerState) {}


bool OrchestraVoice::canPlaySound(juce::SynthesiserSound *sound)
{
	return dynamic_cast<OrchestraSound *>(sound) != nullptr;
}


void OrchestraVoice::startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound *sound, int currentPitchWheelPosition)
{
	juce::ignoreUnused(currentPitchWheelPosition);

	auto *orchestraSound = static_cast<OrchestraSound *>(sound);

	if (orchestraSound == nullptr)
		return;

	mSourceSamplePosition = 0.0;
	mIsPlaying			  = true;

	const auto art		  = orchestraSound->getArticulation();
	mIsShortArticulation  = (art == Articulation::pizzicato) || (art == Articulation::staccato) || (art == Articulation::spiccato) || (art == Articulation::hits);

	// Short articulations are one-shots shaped by velocity; sustained notes are shaped by mCC1/mCC11.
	mNoteGain			  = mIsShortArticulation ? velocity : 1.0f;

	const int layerCount  = juce::jmin(orchestraSound->dynamicLayers.size(), OrchestraVoiceConstant::MaxDynamicLayers);
	mNumLayerBuffers	  = layerCount;

	for (int d = 0; d < layerCount; ++d)
	{
		const juce::AudioBuffer<float> *chosen = nullptr;

		if (auto *layer = orchestraSound->dynamicLayers[d])
		{
			const int rrIndex = pickRoundRobin(*layer);

			if (rrIndex >= 0 && rrIndex < layer->roundRobinSamples.size())
				chosen = layer->roundRobinSamples[rrIndex];
		}

		mLayerBuffers[static_cast<size_t>(d)] = chosen;
	}

	// Pitch shifting
	const double semiToneShift = static_cast<double>(midiNoteNumber - orchestraSound->getRootNote());
	mPitchRatio				   = std::pow(2.0, semiToneShift / 12.0); // If root note = midiNoteNumber, pitch ratio = 1.0 => no shift

	const double sr			   = getSampleRate();

	mCC1.reset(sr, 0.005);
	mCC11.reset(sr, 0.005);

	const float initialCC1	= (mControllerState != nullptr) ? mControllerState->cc1.load(std::memory_order_relaxed) : 0.0f;
	const float initialCC11 = (mControllerState != nullptr) ? mControllerState->cc11.load(std::memory_order_relaxed) : 127.0f;

	mCC1.setCurrentAndTargetValue(initialCC1);
	mCC11.setCurrentAndTargetValue(initialCC11);

	mAdsrParams.attack	= OrchestraVoiceConstant::AttackSeconds; // short fade-in so note-on does not click
	mAdsrParams.decay	= 0.0f;
	mAdsrParams.sustain = 1.0f;
	mAdsrParams.release = mIsShortArticulation ? OrchestraVoiceConstant::ShortRelease : OrchestraVoiceConstant::SustainRelease;

	mAdsr.setSampleRate(sr);
	mAdsr.setParameters(mAdsrParams);
	mAdsr.noteOn();
}


void OrchestraVoice::stopNote(float velocity, bool allowTailOff)
{
	juce::ignoreUnused(velocity);

	if (!allowTailOff)
	{
		mAdsr.reset();
		clearCurrentNote();
		mIsPlaying = false;
		return;
	}

	if (mIsShortArticulation)
		return;

	// Start the release
	mAdsr.noteOff();
}


void OrchestraVoice::controllerMoved(int controllerNumber, int newControllerValue)
{
	if (controllerNumber == kModWheelCc)
		mCC1.setTargetValue(static_cast<float>(newControllerValue));

	else if (controllerNumber == kExpressionCc)
		mCC11.setTargetValue(static_cast<float>(newControllerValue));
}


void OrchestraVoice::renderNextBlock(juce::AudioBuffer<float> &outputBuffer, int startSample, int numSamples)
{
	if (!mIsPlaying || mNumLayerBuffers == 0)
		return;

	const int numOutputChannels = outputBuffer.getNumChannels();

	if (numOutputChannels <= 0)
		return;

	float *outLeft	= outputBuffer.getWritePointer(0, startSample);
	float *outRight = (numOutputChannels > 1) ? outputBuffer.getWritePointer(1, startSample) : nullptr;

	while (--numSamples >= 0)
	{
		const float dynPos = mapDynamicPosition();

		int			i	   = static_cast<int>(std::floor(dynPos));
		float		alpha  = dynPos - static_cast<float>(i);

		if (i < 0)
		{
			i	  = 0;
			alpha = 0.0f;
		}

		if (i >= mNumLayerBuffers - 1)
		{
			i	  = mNumLayerBuffers - 1;
			alpha = 0.0f;
		}

		const int						j		 = juce::jmin(i + 1, mNumLayerBuffers - 1);

		const juce::AudioBuffer<float> *bufferI	 = mLayerBuffers[static_cast<size_t>(i)];
		const juce::AudioBuffer<float> *bufferJ	 = mLayerBuffers[static_cast<size_t>(j)];

		const int						pos		 = static_cast<int>(mSourceSamplePosition);
		const float						frac	 = static_cast<float>(mSourceSamplePosition - pos);

		const int						bufISize = (bufferI != nullptr) ? bufferI->getNumSamples() : 0;
		const int						bufJSize = (bufferJ != nullptr) ? bufferJ->getNumSamples() : 0;

		if (pos + 1 >= bufISize && pos + 1 >= bufJSize) // Both buffers exhausted (or absent): stop
		{
			mAdsr.reset();
			clearCurrentNote();
			mIsPlaying = false;
			break;
		}

		const StereoSample sampleI	  = readFrame(bufferI, pos, frac);
		const StereoSample sampleJ	  = readFrame(bufferJ, pos, frac);

		// Crossfade between the two adjacent dynamic layers
		float			   lMix		  = sampleI.left * (1.f - alpha) + sampleJ.left * alpha;
		float			   rMix		  = sampleI.right * (1.f - alpha) + sampleJ.right * alpha;

		const float		   expression = mCC11.getNextValue() / 127.f;
		const float		   envelope	  = mAdsr.getNextSample();
		const float		   amp		  = (mIsShortArticulation ? mNoteGain : mNoteGain * expression) * envelope;

		lMix *= amp;
		rMix *= amp;

		*outLeft++ += lMix;

		if (outRight != nullptr)
			*outRight++ += rMix;

		mSourceSamplePosition += mPitchRatio;

		if (!mAdsr.isActive()) // Release finished
		{
			clearCurrentNote();
			mIsPlaying = false;
			break;
		}
	}
}


int OrchestraVoice::pickRoundRobin(DynamicLayer &layer)
{
	const int numRoundRobins = layer.roundRobinSamples.size();

	if (numRoundRobins == 0)
		return -1;

	const unsigned next = layer.roundRobinCounter.fetch_add(1u, std::memory_order_relaxed);

	return static_cast<int>(next % static_cast<unsigned>(numRoundRobins));
}


float OrchestraVoice::mapDynamicPosition()
{
	if (mNumLayerBuffers < 1)
		return -1.0f;

	const float span = static_cast<float>(mNumLayerBuffers - 1);

	// Short articulations are picked by velocity, which is fixed for the life of the note.
	if (mIsShortArticulation)
		return mNoteGain * span;

	return (mCC1.getNextValue() / 127.0f) * span;
}


inline float OrchestraVoice::readHermite(const juce::AudioBuffer<float> &buffer, int channel, int pos, float frac)
{
	const int	 numSamples = buffer.getNumSamples();
	const float *data		= buffer.getReadPointer(channel);

	const float	 y0			= data[juce::jmax(0, pos - 1)];
	const float	 y1			= data[pos];
	const float	 y2			= data[juce::jmin(numSamples - 1, pos + 1)];
	const float	 y3			= data[juce::jmin(numSamples - 1, pos + 2)];

	const float	 c0			= y1;
	const float	 c1			= 0.5f * (y2 - y0);
	const float	 c2			= y0 - 2.5f * y1 + 2.0f * y2 - 0.5f * y3;
	const float	 c3			= 0.5f * (y3 - y0) + 1.5f * (y1 - y2);

	return ((c3 * frac + c2) * frac + c1) * frac + c0;
}


inline StereoSample OrchestraVoice::readFrame(const juce::AudioBuffer<float> *buffer, int pos, float frac)
{
	StereoSample out;

	if (buffer == nullptr || pos + 1 >= buffer->getNumSamples())
		return out;

	out.left  = readHermite(*buffer, 0, pos, frac);
	out.right = (buffer->getNumChannels() > 1) ? readHermite(*buffer, 1, pos, frac) : out.left;

	return out;
}
