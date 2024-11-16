/*
  ==============================================================================

	Module			Sampler
	Description		Sampling the instrument and making them ready for playback

  ==============================================================================
*/

#include "Sampler.h"


Sampler::Sampler()
{
}


Sampler::~Sampler()
{
	mSampler.clearSounds();
	mSampler.clearVoices();
}


void Sampler::init()
{
	mSamplesManager = std::make_unique<SamplesManagement>();
	mSamplesManager->init();

	mFormatManager.registerBasicFormats();

	// Add voices to the synthesiser
	const int numVoices = 64;				   // Adjust based on your needs
	for (int i = 0; i < numVoices; ++i)
	{
		mSampler.addVoice(new SamplerVoice()); // Use the default SamplerVoice or your custom voice class
	}
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


SamplerSound *Sampler::createSoundFromSample(const Sample &sample)
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

	std::unique_ptr<AudioFormatReader> formatReader(mFormatManager.createReaderFor(sample.file));

	if (formatReader != nullptr)
	{
		SamplerSound *newsound = new SamplerSound(sample.instrument, // name
												  *formatReader,
												  midiNoteRange,	 // MIDI note range
												  midiNote,			 // root note
												  0.1,				 // attack time in seconds
												  0.3,				 // release time in seconds
												  100.0				 // maximum sample length in seconds
		);
		return newsound;
	}
	return nullptr;
}


void Sampler::addSoundsFromInstrumentToSampler(const int key)
{
	std::vector<SamplerSound> sounds;
	setSamplesAreReady(false);

	mSampler.clearSounds();

	auto samples = filterSamplesFromNote(key);

	for (auto &sample : samples)
	{
		SamplerSound *sound = createSoundFromSample(sample);
		if (sound != nullptr)
		{
			mSampler.addSound(sound);
		}
	}
	if (mSampler.getNumSounds() >= 1)
	{
		setSamplesAreReady(true);
	}
}


void Sampler::setSamplesAreReady(bool value)
{
	if (mSamplesAreReady != value)
	{
		mSamplesAreReady = value;
	}
}


bool Sampler::getSamplesAreReady()
{
	return mSamplesAreReady;
}
