/*
  ==============================================================================
	Module			CoreMaanger
	Description		Manager of the Core Project
  ==============================================================================
*/

#pragma once

#include <memory>

#include "JuceIncludes.h"
#include "InstrumentController.h"
#include "Sampler.h"
#include "Logging.h"
#include "buildinfo.h"

class CoreManager
{
public:
	CoreManager();
	~CoreManager() = default;

	void					 init();
	void					 prepareAudio(double sampleRate, int samplesPerblock);

	juce::MidiKeyboardState &getMidiKeyboardState();

	void					 changeInstrument(int key);
	void					 changeArticulation(int key, Articulation articulation);
	InstrumentInfo			 getInstrument(int key);

	std::set<Articulation>	 getAvailableArticulations(int instrumentKey);

	void					 processAudioBlock(juce::AudioBuffer<float> &buffer, juce::MidiBuffer &midiMessages);

private:
	void									 logProjectInfo();

	Logging									 mLogger;

	std::unique_ptr<InstrumentController>	 mInstrumentController;
	std::unique_ptr<Sampler>				 mSampler;
	std::unique_ptr<juce::MidiKeyboardState> mMidiKeyboardState;

	int										 mCurrentInstrumentKey{0};
};
