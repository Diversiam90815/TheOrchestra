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


std::vector<Sample> Sampler::filterSamplesFromNote(const int key, const String &note)
{
	auto				allSamplesForInstrument = mSamplesManager->getSamplesForInstrument(key);
	std::vector<Sample> filteredSamples;

	for (auto &sampleFromNote : allSamplesForInstrument)
	{
		if (note.isNotEmpty() && sampleFromNote.note != note)
			continue;

		filteredSamples.push_back(sampleFromNote);
	}

	return filteredSamples;
}


SamplerSound Sampler::createSoundFromSample(const Sample &sample)
{
	int		   midiNote = CustomPianoRoll::turnNotenameIntoMidinumber(sample.note);
	Range<int> pitchRange;

	if (sample.note.contains("B") || sample.note.contains("E"))
	{
		pitchRange = Range<int>(midiNote, midiNote);
	}
	else
	{
		pitchRange = Range<int>(midiNote, midiNote + 1);
	}

	return SamplerSound(sample.instrument,	 // name
										  *sample.reader.get(), // audio data
										  pitchRange,			 // MIDI note range
										  midiNote,				 // root note
										  0.1,					 // attack time in seconds
										  0.1,					 // release time in seconds
										  10.0					 // maximum sample length in seconds
	);
}


std::vector<std::unique_ptr<SamplerSound>> Sampler::getSoundsFromInstrument(const int key)
{
	std::vector<std::unique_ptr<SamplerSound>> sounds;

	auto									   samples = filterSamplesFromNote(key);

	for (auto &sample : samples)
	{
		auto sound = createSoundFromSample(sample);
		sounds.push_back(sound);
	}

	return sounds;
}
