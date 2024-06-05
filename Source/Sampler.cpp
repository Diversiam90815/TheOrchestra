/*
  ==============================================================================

	Sampler.cpp
	Created: 31 May 2024 12:43:50pm
	Author:  Jens.Langenberg

  ==============================================================================
*/

#include "Sampler.h"


Sampler::Sampler()
{
}


Sampler::~Sampler()
{
}


void Sampler::init()
{
	mSamplesManager = std::make_unique<SamplesManagement>();
	mSamplesManager->init();
}


std::vector<std::unique_ptr<Sample>> Sampler::filterSamplesFromNote(const int key, const String &note)
{
	auto								 allSamplesForInstrument = mSamplesManager->getSamplesForInstrument(key);
	std::vector<std::unique_ptr<Sample>> filteredSamples;

	for (auto &sampleFromNote : allSamplesForInstrument)
	{
		if (note.isNotEmpty() && sampleFromNote.note != note)
			continue;

		auto sample = std::make_unique<Sample>(sampleFromNote);
		filteredSamples.push_back(sample);
	}

	if (filteredSamples.size() > 0)
	{
		return filteredSamples;
	}
}


std::unique_ptr<SamplerSound> Sampler::createSoundFromSample(const std::unique_ptr<Sample> &sample)
{
	int		   midiNote = CustomPianoRoll::turnNotenameIntoMidinumber(sample->note);
	Range<int> pitchRange;

	if (sample->note.contains("B") || sample->note.contains("E"))
	{
		pitchRange = Range<int>(midiNote, midiNote);
	}
	else
	{
		pitchRange = Range<int>(midiNote, midiNote + 1);
	}

	return std::make_unique<SamplerSound>(sample->instrument, // name
										  *sample->buffer,	  // audio data
										  pitchRange,		  // MIDI note range
										  midiNote,			  // root note
										  0.1,				  // attack time in seconds
										  0.1,				  // release time in seconds
										  10.0				  // maximum sample length in seconds
	);
}


std::vector<std::unique_ptr<SamplerSound>> Sampler::getSoundsFromInstrument(const int key)
{
	std::vector<std::unique_ptr<SamplerSound>> sounds;

	auto samples = filterSamplesFromNote(key);
	
	for (auto& sample : samples)
	{
		auto sound = createSoundFromSample(sample);
		sounds.push_back(sound);
	}

	return sounds;
}
