/*
  ==============================================================================
	Module			Sampler
	Description		Sampling the instrument and making them ready for playback
  ==============================================================================
*/

#pragma once

#include "JuceIncludes.h"
#include "SamplesManagement.h"
#include "Logging.h"
#include "OrchestraVoice.h"
#include "Helper.h"
#include "InstrumentController.h"


class Sampler
{
public:
	Sampler() = default;
	~Sampler();

	void				   init(InstrumentController &controller);

	std::set<Articulation> getAvailableArticulationsForInstrument(const InstrumentID key);

	void				   addSoundsFromInstrumentToSampler(const InstrumentID key, Articulation articulationUsed);

	void				   process(juce::AudioBuffer<float> &buffer, juce::MidiBuffer &midiMessages);
	void				   prepare(double sampleRate, int samplesPerBlock);

	void				   reset();

	bool				   getSamplesAreReady();
	void				   setSamplesAreReady(bool value); // TODO: Make visible to UI

	bool				   loadSamples();
	bool				   reloadSamples(std::string samplesDirectory);

private:
	std::map<int, std::map<int, std::vector<juce::File>>> createDynamicMap(std::vector<Sample> &samples);

	std::vector<Sample>									  filterArticulation(std::vector<Sample> &allSamples, Articulation articulationUsed);

	std::vector<int>									  createNoteList(std::map<int, std::map<int, std::vector<juce::File>>> &noteDynamicMap);

	std::map<int, std::pair<int, int>>					  createNoteRangeMap(std::map<int, std::map<int, std::vector<juce::File>>> &noteDynamicMap, const int key);

	std::pair<int, int>									  getRangesOfInstrument(const InstrumentID key);


	juce::Synthesiser									  mSampler;

	juce::AudioFormatManager							  mFormatManager;

	std::unique_ptr<SamplesManagement>					  mSamplesManager;

	std::atomic<bool>									  mSamplesAreReady		= false;

	InstrumentController								 *mInstrumentController = nullptr;
};
