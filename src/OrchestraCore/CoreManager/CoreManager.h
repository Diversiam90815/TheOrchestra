/*
  ==============================================================================
	Module			CoreManager
	Description		Manager of the Core Project
  ==============================================================================
*/

#pragma once

#include <memory>
#include <array>
#include <atomic>

#include "JuceIncludes.h"
#include "InstrumentController.h"
#include "OrchestraSampler.h"
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

	void					 sendControllerChange(int ccNumber, int value);
	int						 getLastControllerValue(int ccNumber) const;

	void					 changeInstrument(InstrumentID key);
	bool					 changeArticulation(InstrumentID key, Articulation articulation);
	void					 changeSamplesFolder(std::string &samplesFolder);
	InstrumentProfile		 getInstrument(InstrumentID key);

	std::vector<std::pair<InstrumentID, std::string>> getInstrumentsForFamily(Family family);

	std::set<Articulation>	 getAvailableArticulations(InstrumentID instrumentKey);

	void					 processAudioBlock(juce::AudioBuffer<float> &buffer, juce::MidiBuffer &midiMessages);

	void					 setSamplesFolder(std::string &directory);

private:
	void									 logProjectInfo();

	Logging									 mLogger;

	std::unique_ptr<InstrumentController>	 mInstrumentController;
	std::unique_ptr<OrchestraSampler>		 mSampler;
	std::unique_ptr<juce::MidiKeyboardState> mMidiKeyboardState;

	juce::MidiMessageCollector				 mUiMidiCollector;
	std::array<std::atomic<int>, 128>		 mCcValues;	  // last-seen value per CC number, -1 = unknown

	int										 mCurrentInstrumentKey{0};
};
