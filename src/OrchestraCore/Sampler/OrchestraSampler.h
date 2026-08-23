/*
  ==============================================================================
	Module			OrchestraSampler
	Description		Sampling the instrument and making them ready for playback
  ==============================================================================
*/

#pragma once

#include <atomic>
#include <functional>
#include <vector>

#include "JuceIncludes.h"
#include "SamplesManagement.h"
#include "Logging.h"
#include "OrchestraVoice.h"
#include "Helper.h"
#include "InstrumentController.h"


using SampleLoadCallback = std::function<void(bool)>;


class OrchestraSampler
{
public:
	static constexpr int kNumVoices = 64;

	OrchestraSampler()				= default;
	~OrchestraSampler();

	void				   init(InstrumentController &controller);

	std::set<Articulation> getAvailableArticulationsForInstrument(const InstrumentID key);

	void				   addSoundsFromInstrumentToSampler(const InstrumentID key, Articulation articulationUsed);

	void				   loadInstrumentAsync(const InstrumentID key, Articulation articulationUsed, SampleLoadCallback onComplete);

	bool				   isLoading() const { return mLoadPool.getNumJobs() > 0; }

	void				   process(juce::AudioBuffer<float> &buffer, juce::MidiBuffer &midiMessages);
	void				   prepare(double sampleRate, int samplesPerBlock);

	void				   reset();

	bool				   getSamplesAreReady();
	void				   setSamplesAreReady(bool value);

	bool				   reloadSamples(std::string samplesDirectory);

private:
	std::map<int, std::map<int, std::vector<juce::File>>> createDynamicMap(std::vector<Sample> &samples);
	std::vector<int>									  createNoteList(std::map<int, std::map<int, std::vector<juce::File>>> &noteDynamicMap);
	std::map<int, std::pair<int, int>>					  createNoteRangeMap(std::map<int, std::map<int, std::vector<juce::File>>> &noteDynamicMap, const int key);

	std::vector<Sample>									  filterArticulation(std::vector<Sample> &allSamples, Articulation articulationUsed);

	std::pair<int, int>									  getRangesOfInstrument(const InstrumentID key);

	std::vector<juce::SynthesiserSound::Ptr>			  buildSounds(const InstrumentID key, Articulation articulationUsed);
	void												  installSounds(std::vector<juce::SynthesiserSound::Ptr> sounds);


	juce::Synthesiser									  mSampler;

	ControllerState										  mControllerState;

	juce::AudioFormatManager							  mFormatManager;

	std::unique_ptr<SamplesManagement>					  mSamplesManager;

	std::atomic<bool>									  mSamplesAreReady		= false;

	InstrumentController								 *mInstrumentController = nullptr;

	juce::ThreadPool									  mLoadPool{1};

	std::atomic<int>									  mLoadGeneration{0};

	JUCE_DECLARE_WEAK_REFERENCEABLE(OrchestraSampler)
};
