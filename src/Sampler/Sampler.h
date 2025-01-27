/*
  ==============================================================================

	Module			Sampler
	Description		Sampling the instrument and making them ready for playback

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "SamplesManagement.h"
#include "CustomPianoRoll.h"
#include "Logging.h"
#include "OrchestraVoice.h"
#include "Helper.h"

/*
Sampled note values and JSON note values do not match currently -> samples note values are one octave lower notated than the JSON instruments
*/


class Sampler
{
public:
	Sampler();
	~Sampler();

	void				   init(InstrumentController *controller);

	std::set<Articulation> getAvailableArticulationsForInstrument(const int key);

	void				   addSoundsFromInstrumentToSampler(const int key, Articulation articulationUsed);

	bool				   getSamplesAreReady();
	void				   setSamplesAreReady(bool value);


private:
	std::map<int, std::map<int, std::vector<juce::File>>> createDynamicMap(std::vector<Sample> &samples);

	std::vector<Sample>									  filterArticulation(std::vector<Sample> &allSamples, Articulation articulationUsed);

	std::vector<int>									  createNoteList(std::map<int, std::map<int, std::vector<juce::File>>> &noteDynamicMap);

	std::map<int, std::pair<int, int>>					  createNoteRangeMap(std::map<int, std::map<int, std::vector<juce::File>>> &noteDynamicMap, const int key);

	std::pair<int, int>									  getRangesOfInstrument(const int key);


	Synthesiser											  mSampler;

	AudioFormatManager									  mFormatManager;

	std::unique_ptr<SamplesManagement>					  mSamplesManager;

	std::atomic<bool>									  mSamplesAreReady		= false;

	InstrumentController								 *mInstrumentController = nullptr;

	friend class OrchestraProcessor;
};
