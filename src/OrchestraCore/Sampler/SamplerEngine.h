/*
  ==============================================================================
	Module			SamplerEngine
	Description		Sampling the instrument and making them ready for playback
  ==============================================================================
*/

#pragma once

#include <atomic>
#include <functional>
#include <vector>
#include <memory>

#include "JuceIncludes.h"
#include "SampleCatalog.h"
#include "Logging.h"
#include "ArticulationVoice.h"
#include "Helper.h"
#include "InstrumentController.h"
#include "SamplerStructs.h"
#include "SamplerTypes.h"


class SamplerEngine : public std::enable_shared_from_this<SamplerEngine>
{
public:
	static constexpr int kNumVoices = 64;

	SamplerEngine()					= default;
	~SamplerEngine();

	void			init(InstrumentController &controller, SampleLoadCallback onCatalogReady = nullptr);

	ArticulationSet getAvailableArticulationsForInstrument(const InstrumentID key);

	void			addSoundsFromInstrumentToSampler(const InstrumentID key, Articulation articulationUsed);

	void			loadInstrumentAsync(const InstrumentID key, Articulation articulationUsed, SampleLoadCallback onComplete);

	bool			isLoading() const { return mIsBuilding.load(); }

	void			process(juce::AudioBuffer<float> &buffer, juce::MidiBuffer &midiMessages);
	void			prepare(double sampleRate, int samplesPerBlock);

	void			reset();

	bool			getSamplesAreReady();
	void			setSamplesAreReady(bool value);

	bool			reloadSamples(std::string samplesDirectory, SampleLoadCallback onComplete = nullptr);

private:
	void									 runBuildOnBackgroundThread(InstrumentID key, Articulation articulationUsed, int generation, SampleLoadCallback onComplete);
	void									 installBuildResult(std::vector<juce::SynthesiserSound::Ptr> sounds, int generation, SampleLoadCallback onComplete);

	NoteDynamicMap							 createDynamicMap(std::vector<Sample> &samples);
	std::vector<int>						 createNoteList(NoteDynamicMap &noteDynamicMap);
	NoteRangeMap							 createNoteRangeMap(NoteDynamicMap &noteDynamicMap, const int key);

	std::vector<Sample>						 filterArticulation(std::vector<Sample> &allSamples, Articulation articulationUsed);

	std::pair<int, int>						 getRangesOfInstrument(const InstrumentID key);

	std::vector<juce::SynthesiserSound::Ptr> buildSounds(const InstrumentID key, Articulation articulationUsed);
	void									 installSounds(std::vector<juce::SynthesiserSound::Ptr> sounds);


	juce::Synthesiser						 mSampler;

	ControllerState							 mControllerState;

	juce::AudioFormatManager				 mFormatManager;

	std::unique_ptr<SampleCatalog>			 mSamplesManager;

	std::atomic<bool>						 mSamplesAreReady	   = false;

	InstrumentController					*mInstrumentController = nullptr;

	std::thread								 mLoadThread;		 // Background sample-build worker
	std::atomic<bool>						 mIsBuilding{false}; // True while buildSounds() is running
	std::atomic<int>						 mLoadGeneration{0}; // Guards against installing a stale result if a newer load supersedes this one
};
