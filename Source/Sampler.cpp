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

	mFormatManager.registerBasicFormats();
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

	BigInteger midiNoteRange;

	if (sample.note.contains("B") || sample.note.contains("E"))
	{
		midiNoteRange.setRange(midiNote, midiNote, true);
	}
	else
	{
		midiNoteRange.setRange(midiNote, midiNote + 1, true);
	}

	auto			  &sampleFile	= sample.file;
	AudioFormatReader *formatReader = mFormatManager.createReaderFor(sample.file);

	return SamplerSound(sample.instrument, // name
						*formatReader,
						midiNoteRange,	   // MIDI note range
						midiNote,		   // root note
						0.1,			   // attack time in seconds
						0.1,			   // release time in seconds
						10.0			   // maximum sample length in seconds
	);
}


void Sampler::addSoundsFromInstrumentToSampler(const int key)
{
	std::vector<SamplerSound> sounds;
	mSampler.clearSounds();

	auto					  samples = filterSamplesFromNote(key);

	for (auto &sample : samples)
	{
		auto &sound = createSoundFromSample(sample);
		mSampler.addSound(sound);
	}
}
