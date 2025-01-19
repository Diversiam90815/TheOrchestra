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
	const int numVoices = 64;
	for (int i = 0; i < numVoices; ++i)
	{
		mSampler.addVoice(new OrchestraVoice());
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

	LOG_INFO("Filtered Samples with size {}", filteredSamples.size());
	return filteredSamples;
}


void Sampler::addSoundsFromInstrumentToSampler(const int key)
{
	std::vector<SamplerSound> sounds;
	setSamplesAreReady(false);

	mSampler.clearSounds();

	auto samples = filterSamplesFromNote(key);

	if (samples.empty())
	{
		LOG_WARNING("No samples found for instrument key {}", key);
		return;
	}

	// Group the samples by midinote -> dynamic -> files
	std::map<int, std::map<int, std::vector<juce::File>>> noteDynMap;

	for (auto &s : samples)
	{
		int midiNote = CustomPianoRoll::turnNotenameIntoMidinumber(s.note);
		int dynValue = static_cast<int>(s.dynamic);
		// Round Robbin' for now are not stored as value, but as count of files
		noteDynMap[midiNote][dynValue].push_back(s.file);
	}

	for (auto &notePair : noteDynMap)
	{
		int	  midiNote		 = notePair.first;
		auto *orchestraSound = new OrchestraSound(midiNote, midiNote);

		for (auto &dynPair : notePair.second)
		{
			int										   dynValue	  = dynPair.first;
			auto									  &fileVector = dynPair.second;

			juce::OwnedArray<juce::AudioBuffer<float>> rrBuffers;

			for (auto &file : fileVector)
			{
				std::unique_ptr<juce::AudioFormatReader> reader(mFormatManager.createReaderFor(file));
				if (reader)
				{
					auto *newBuffer = new juce::AudioBuffer<float>((int)reader->numChannels, (int)reader->lengthInSamples);
					reader->read(newBuffer, 0, (int)reader->lengthInSamples, 0, true, true);
					rrBuffers.add(newBuffer);
				}
				else
				{
					LOG_ERROR("Failed to read sample file: {}", file.getFileName().toStdString().c_str());
				}
			}

			auto mappedDyn = static_cast<Dynamics>(dynValue);
			orchestraSound->addDynamicLayer(mappedDyn, std::move(rrBuffers));
		}
		mSampler.addSound(orchestraSound);
	}

	if (mSampler.getNumSounds() > 0)
	{
		setSamplesAreReady(true);
		LOG_INFO("Samples for instrument (Key : {}) are loaded! (NumSounds = {})", key, mSampler.getNumSounds());
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
