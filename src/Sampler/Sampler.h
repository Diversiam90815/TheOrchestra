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


class Sampler
{
public:
	Sampler();
	~Sampler();

	void				   init();

	std::set<Articulation> getAvailableArticulationsForInstrument(const int key);

	void				   addSoundsFromInstrumentToSampler(const int key, Articulation articulationUsed);

	bool				   getSamplesAreReady();
	void				   setSamplesAreReady(bool value);

private:
	Synthesiser						   mSampler;

	AudioFormatManager				   mFormatManager; // AudioFormatManager registering the audio formats

	std::unique_ptr<SamplesManagement> mSamplesManager;

	std::atomic<bool>				   mSamplesAreReady = false;


	friend class OrchestraProcessor;
};
