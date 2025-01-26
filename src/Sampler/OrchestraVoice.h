/*
  ==============================================================================

	Module			OrchestraVoice
	Description		Custom voice that picks which dynamic layer & round-robin is being played

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
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
	int								pickDynamicLayer(OrchestraSound *orchestraSound, float velocity);

	int								pickRoundRobin(OrchestraSound *orchestraSound, int dynamicIndex);

	const juce::AudioBuffer<float> *getBuffer(OrchestraSound *orchestraSound, int dynamicIndex, int rrIndex);

	float							mapCC1ToDynamicPosition(OrchestraSound *orchestraSound);

	bool							isPlaying			  = false;

	double							sourceSamplePosition  = 0.0;

	float							pitchRatio			  = 1.0f;

	float							noteGain			  = 10.0f;

	int								noteNumber			  = -1;

	int								chosenDynamicIndex	  = -1; // Set in startNote()

	int								chosenRoundRobinIndex = -1; // Set in startNote()

	juce::SmoothedValue<float>		CC1;

	juce::SmoothedValue<float>		CC11;

	const juce::AudioBuffer<float> *currentBuffer = nullptr; // Pointer to the actual buffer we read from
};
