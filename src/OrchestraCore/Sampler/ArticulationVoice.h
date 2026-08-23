/*
  ==============================================================================
	Module			ArticulationVoice
	Description		Custom voice that picks which dynamic layer & round-robin is being played
  ==============================================================================
*/

#pragma once

#include <array>
#include <atomic>

#include "JuceIncludes.h"
#include "SampleSound.h"
#include "Parameters.h"
#include "SamplerStructs.h"


class ArticulationVoice : public juce::SynthesiserVoice
{
public:
	explicit ArticulationVoice(const ControllerState *controllerState = nullptr);
	~ArticulationVoice() override = default;

	bool canPlaySound(juce::SynthesiserSound *sound) override;

	void startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound *sound, int currentPitchWheelPosition) override;
	void stopNote(float velocity, bool allowTailOff) override;

	void pitchWheelMoved(int newPitchWheelValue) override {}
	void controllerMoved(int controllerNumber, int newControllerValue) override;

	void renderNextBlock(juce::AudioBuffer<float> &outputBuffer, int startSample, int numSamples) override;

	int	 getNumDynamicLayers() const { return mNumLayerBuffers; }

	bool isEnvelopeActive() const { return mAdsr.isActive(); }

private:
	static int																			   pickRoundRobin(DynamicLayer &layer);

	float																				   mapDynamicPosition();

	inline float																		   readHermite(const juce::AudioBuffer<float> &buffer, int channel, int pos, float frac);
	inline StereoSample																	   readFrame(const juce::AudioBuffer<float> *buffer, int pos, float frac);


	const ControllerState																  *mControllerState		 = nullptr;

	bool																				   mIsPlaying			 = false;
	bool																				   mIsShortArticulation	 = false;

	double																				   mSourceSamplePosition = 0.0;
	double																				   mPitchRatio			 = 1.0;
	float																				   mNoteGain			 = 1.0f;
	int																					   mNumLayerBuffers		 = 0;

	juce::SmoothedValue<float>															   mCC1;
	juce::SmoothedValue<float>															   mCC11;

	juce::ADSR																			   mAdsr;
	juce::ADSR::Parameters																   mAdsrParams;

	std::array<const juce::AudioBuffer<float> *, OrchestraVoiceConstant::MaxDynamicLayers> mLayerBuffers{};
};
