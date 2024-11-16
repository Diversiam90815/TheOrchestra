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


class Sampler
{
public:
	Sampler();
	~Sampler();

	void init();

	void addSoundsFromInstrumentToSampler(const int key);

	bool getSamplesAreReady();
	void setSamplesAreReady(bool value);

private:
	SamplerSound					  *createSoundFromSample(const Sample &sample);

	std::vector<Sample>				   filterSamplesFromNote(const int key, const String &note = "");


	Synthesiser						   mSampler;

	AudioFormatManager				   mFormatManager; // AudioFormatManager registering the audio formats

	std::unique_ptr<SamplesManagement> mSamplesManager;

	std::atomic<bool>				   mSamplesAreReady = false;


	friend class OrchestraProcessor;
};
