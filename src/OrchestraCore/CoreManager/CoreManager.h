/*
  ==============================================================================
	Module			CoreManager
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

	void					 changeInstrument(InstrumentID key);
	void					 changeArticulation(InstrumentID key, Articulation articulation);
	InstrumentInfo			 getInstrument(InstrumentID key);

	std::set<Articulation>	 getAvailableArticulations(InstrumentID instrumentKey);

	void					 processAudioBlock(juce::AudioBuffer<float> &buffer, juce::MidiBuffer &midiMessages);

private:
	void									 logProjectInfo();

	Logging									 mLogger;

	std::unique_ptr<InstrumentController>	 mInstrumentController;
	std::unique_ptr<Sampler>				 mSampler;
	std::unique_ptr<juce::MidiKeyboardState> mMidiKeyboardState;

	int										 mCurrentInstrumentKey{0};
};
