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


std::list<Articulation> Sampler::getAvailableArticulationsForInstrument(const int key)
{
	auto					samples = mSamplesManager->getSamplesForInstrument(key);

	std::list<Articulation> availableArticulations{};

	for (auto &s : samples)
	{
		availableArticulations.push_back(s.articulation);
	}

	return availableArticulations;
}


void Sampler::addSoundsFromInstrumentToSampler(const int key, Articulation articulationUsed)
{
	std::vector<SamplerSound> sounds;
	setSamplesAreReady(false);

	mSampler.clearSounds();

	auto samples = mSamplesManager->getSamplesForInstrument(key);

	if (samples.empty())
	{
		LOG_WARNING("No samples found for instrument key {}", key);
		return;
	}

	// Group the samples by midinote -> dynamic -> files
	std::map<int, std::map<int, std::vector<juce::File>>> noteDynMap;

	for (auto &s : samples)
	{
		int midiNote = s.noteMidiValue;
		int dynValue = static_cast<int>(s.dynamic);
		// Round Robbin' for now are not stored as value, but as count of files

		// Filter for the articulation here for now
		if (s.articulation == articulationUsed)
			noteDynMap[midiNote][dynValue].push_back(s.file);
	}


	// Extract all unique MIDI notes into a sorted list
	std::vector<int> noteList;
	noteList.reserve(noteDynMap.size());

	for (auto &val : noteDynMap)
		noteList.push_back(val.first);

	std::sort(noteList.begin(), noteList.end());

	if (noteList.empty())
	{
		LOG_ERROR("Notelist is empty. We are skipping.");
		return;
	}

	// building a map of note range (low, high)
	std::map<int, std::pair<int, int>> noteRanges;
	for (auto &note : noteList)
	{
		noteRanges[note] = {0, 127}; // First initialize the values to 0-127 -> we refine them later
	}

	// Set the min and max for instrument (for now leave it at 0 and 127)
	noteRanges[noteList.front()].first = 0;
	noteRanges[noteList.back()].first  = 127;

	// Fill midpoint ranges between adjacent sampled notes
	for (size_t i = 0; i < noteList.size() - 1; ++i)
	{
		int nA				  = noteList[i];
		int nB				  = noteList[i + 1];

		int mid				  = (nA + nB) / 2;

		noteRanges[nA].second = mid;
		noteRanges[nB].first  = mid + 1;
	}


	for (auto &notePair : noteDynMap)
	{
		int	  midiNote		 = notePair.first;
		int	  rangeLow		 = noteRanges[midiNote].first;
		int	  rangeHigh		 = noteRanges[midiNote].second;

		auto *orchestraSound = new OrchestraSound(rangeLow, rangeHigh);

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
