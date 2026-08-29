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
#include "SamplerEngine.h"
#include "Logging.h"
#include "buildinfo.h"


class CoreManager
{
public:
	CoreManager();
	~CoreManager() = default;

	void											  init();
	void											  prepareAudio(double sampleRate, int samplesPerblock);

	juce::MidiKeyboardState							 &getMidiKeyboardState();

	void											  sendControllerChange(int ccNumber, int value);
	int												  getLastControllerValue(int ccNumber) const;

	void											  changeInstrument(InstrumentID key);
	bool											  changeArticulation(InstrumentID key, Articulation articulation);
	void											  changeArticulationAsync(InstrumentID key, Articulation articulation, SampleLoadCallback onComplete);

	bool											  isLoadingSamples() const;
	void											  changeSamplesFolder(const std::string &samplesFolder, SampleLoadCallback onComplete = nullptr);
	InstrumentProfile								  getInstrument(InstrumentID key);

	std::vector<std::pair<InstrumentID, std::string>> getInstrumentsForFamily(Family family);

	ArticulationSet									  getAvailableArticulations(InstrumentID instrumentKey);

	InstrumentID									  getCurrentInstrument() const { return mCurrentInstrument; }
	Articulation									  getCurrentArticulation() const { return mCurrentArticulation; }
	bool											  hasInstrumentLoaded() const { return mCurrentInstrument > 0; }

	void											  processAudioBlock(juce::AudioBuffer<float> &buffer, juce::MidiBuffer &midiMessages);

private:
	void									 logProjectInfo();

	Logging									 mLogger;

	std::unique_ptr<InstrumentController>	 mInstrumentController;
	std::shared_ptr<SamplerEngine>			 mSampler;
	std::unique_ptr<juce::MidiKeyboardState> mMidiKeyboardState;

	juce::MidiMessageCollector				 mUiMidiCollector;
	std::array<std::atomic<int>, 128>		 mCcValues; // last-seen value per CC number, -1 = unknown

	InstrumentID							 mCurrentInstrument	  = 0;
	Articulation							 mCurrentArticulation = Articulation::sustain;
};
