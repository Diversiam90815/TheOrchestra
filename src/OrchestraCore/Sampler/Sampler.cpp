/*
  ==============================================================================
	Module			Sampler
	Description		Sampling the instrument and making them ready for playback
  ==============================================================================
*/

#include "Sampler.h"
#include "InstrumentController.h" // For note ranges


Sampler::~Sampler()
{
	mSampler.clearSounds();
	mSampler.clearVoices();
}


void Sampler::init(InstrumentController *controller)
{
	mInstrumentController = controller;

	mSamplesManager		  = std::make_unique<SamplesManagement>();
	mSamplesManager->init();

	mFormatManager.registerBasicFormats();

	// Add voices to the synthesiser
	const int numVoices = 64;
	for (int i = 0; i < numVoices; ++i)
	{
		mSampler.addVoice(new OrchestraVoice());
	}
}


std::set<Articulation> Sampler::getAvailableArticulationsForInstrument(const int key)
{
	auto				   samples = mSamplesManager->getSamplesForInstrument(key);

	std::set<Articulation> availableArticulations{};

	for (auto &s : samples)
	{
		availableArticulations.insert(s.articulation);
	}

	return availableArticulations;
}


void Sampler::addSoundsFromInstrumentToSampler(const int key, Articulation articulationUsed)
{
	std::vector<SamplerSound> sounds;
	reset();

	auto samples = mSamplesManager->getSamplesForInstrument(key);

	if (samples.empty())
	{
		LOG_WARNING("No samples found for instrument key {}", key);
		return;
	}

	auto filteredSamples = filterArticulation(samples, articulationUsed);
	auto noteDynamicMap	 = createDynamicMap(filteredSamples);
	auto noteRanges		 = createNoteRangeMap(noteDynamicMap, key);

	if (noteRanges.empty())
		return;

	for (auto &notePair : noteDynamicMap)
	{
		int	 midiNote		= notePair.first;
		int	 rangeLow		= noteRanges[midiNote].first;
		int	 rangeHigh		= noteRanges[midiNote].second;

		auto orchestraSound = std::make_unique<OrchestraSound>(rangeLow, rangeHigh, midiNote);

		orchestraSound->setArticulation(articulationUsed);

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

		mSampler.addSound(orchestraSound.release());
	}

	if (mSampler.getNumSounds() > 0)
	{
		setSamplesAreReady(true);
		LOG_INFO("Samples for instrument (Key : {}) are loaded! (NumSounds = {})", key, mSampler.getNumSounds());
	}
}


void Sampler::process(AudioBuffer<float> &buffer, MidiBuffer &midiMessages)
{
	if (!getSamplesAreReady())
		return;

	mSampler.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());
}


void Sampler::prepare(double sampleRate, int samplesPerBlock)
{
	mSampler.setCurrentPlaybackSampleRate(sampleRate);
}


void Sampler::reset()
{
	setSamplesAreReady(false);
	mSampler.clearSounds();
}


std::map<int, std::map<int, std::vector<juce::File>>> Sampler::createDynamicMap(std::vector<Sample> &samples)
{
	// Group the samples by midinote -> dynamic -> files
	std::map<int, std::map<int, std::vector<juce::File>>> noteDynMap;

	for (auto &s : samples)
	{
		int midiNote = s.noteMidiValue;
		int dynValue = static_cast<int>(s.dynamic);
		// Round Robbin' for now are not stored as value, but as count of files

		noteDynMap[midiNote][dynValue].push_back(s.file);
	}

	return noteDynMap;
}


std::vector<Sample> Sampler::filterArticulation(std::vector<Sample> &allSamples, Articulation articulationUsed)
{
	std::vector<Sample> filteredSamples;
	std::ranges::copy_if(allSamples, std::back_inserter(filteredSamples), [articulationUsed](const Sample &sample) { return sample.articulation == articulationUsed; });
	return filteredSamples;
}


std::vector<int> Sampler::createNoteList(std::map<int, std::map<int, std::vector<juce::File>>> &noteDynamicMap)
{
	// Extract all unique MIDI notes into a sorted list
	std::vector<int> noteList;
	noteList.reserve(noteDynamicMap.size());

	for (auto &val : noteDynamicMap)
		noteList.push_back(val.first);

	std::sort(noteList.begin(), noteList.end());

	return noteList;
}


std::map<int, std::pair<int, int>> Sampler::createNoteRangeMap(std::map<int, std::map<int, std::vector<juce::File>>> &noteDynamicMap, const int key)
{
	auto noteList = createNoteList(noteDynamicMap);
	if (noteList.empty())
	{
		LOG_WARNING("Notelist is empty. We are skipping.");
		return {};
	}

	// building a map of note range (low, high)
	std::map<int, std::pair<int, int>> noteRanges;
	for (auto &note : noteList)
	{
		noteRanges[note] = {0, 127}; // First initialize the values to 0-127 -> we refine them later
	}

	// Set the min and max for instrument
	auto noteLimits					   = getRangesOfInstrument(key);
	noteRanges[noteList.front()].first = std::min(noteLimits.first, noteList.front());
	noteRanges[noteList.back()].second = std::max(noteLimits.second, noteList.back());

	// Fill midpoint ranges between adjacent sampled notes
	for (size_t i = 0; i < noteList.size() - 1; ++i)
	{
		int nA				  = noteList[i];
		int nB				  = noteList[i + 1];

		int mid				  = (nA + nB) / 2;

		noteRanges[nA].second = mid;
		noteRanges[nB].first  = mid + 1;
	}

	return noteRanges;
}


std::pair<int, int> Sampler::getRangesOfInstrument(const int key)
{
	if (mInstrumentController == nullptr)
		return {};

	auto   instrument = mInstrumentController->getInstrument(key);
	String range	  = instrument.getRange();

	if (instrument.isRhythmicPercussion())
		range = instrument.getDisplayedRange();

	String lowerNote	   = getLowerOrHigherNote(range, true);
	String higherNote	   = getLowerOrHigherNote(range, false);

	int	   lowerNoteValue  = turnNotenameIntoMidinumber(lowerNote);
	int	   higherNoteValue = turnNotenameIntoMidinumber(higherNote);

	return std::pair<int, int>(lowerNoteValue, higherNoteValue);
}


void Sampler::setSamplesAreReady(bool value)
{
	if (mSamplesAreReady.load() != value)
	{
		mSamplesAreReady.store(value);
	}
}


bool Sampler::getSamplesAreReady()
{
	return mSamplesAreReady.load();
}
