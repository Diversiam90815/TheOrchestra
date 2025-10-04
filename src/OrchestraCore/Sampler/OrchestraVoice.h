/*
  ==============================================================================

	Module			OrchestraVoice
	Description		Custom voice that picks which dynamic layer & round-robin is being played

  ==============================================================================
*/

#pragma once

#include "JuceIncludes.h"
#include "OrchestraSound.h"


class OrchestraVoice : public juce::SynthesiserVoice
{
public:
	OrchestraVoice()		   = default;
	~OrchestraVoice() override = default;

	bool canPlaySound(juce::SynthesiserSound *sound) override;

	void startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound *sound, int currentPitchWheelPosition) override;

	void stopNote(float velocity, bool allowTailOff) override;

	void pitchWheelMoved(int newPitchWheelValue) override;

	void controllerMoved(int controllerNumber, int newControllerValue) override;

	void renderNextBlock(juce::AudioBuffer<float> &outputBuffer, int startSample, int numSamples) override;


private:
	int											  pickRoundRobin(OrchestraSound *orchestraSound, int dynamicIndex);

	float										  mapDynamicPosition();


	bool										  isPlaying				= false;

	bool										  isShortArticulation	= false;

	double										  sourceSamplePosition	= 0.0;

	float										  pitchRatio			= 1.0f;

	float										  noteGain				= 1.0f;

	int											  noteNumber			= -1;

	int											  numDynamicLayers		= -1; // Set in startNote()

	int											  chosenDynamicIndex	= -1; // Set in startNote()

	int											  chosenRoundRobinIndex = -1; // Set in startNote()

	juce::SmoothedValue<float>					  CC1;

	juce::SmoothedValue<float>					  CC11;

	std::vector<const juce::AudioBuffer<float> *> layerBuffers; // layerBuffers[i] will hold the round robbin sample for the dynamic layer i
};
