/*
  ==============================================================================
	Module			OrchestraSampler
	Description		Sampling the instrument and making them ready for playback
  ==============================================================================
*/

#include "OrchestraSampler.h"
#include "InstrumentController.h" // For note ranges


OrchestraSampler::~OrchestraSampler()
{
	mLoadPool.removeAllJobs(true, 5000);

	mSampler.allNotesOff(0, false);
	mSampler.clearSounds();
	mSampler.clearVoices();
}


void OrchestraSampler::init(InstrumentController &controller)
{
	mInstrumentController = &controller;

	mSamplesManager		  = std::make_unique<SamplesManagement>();
	mSamplesManager->init();

	// registerBasicFormats() only covers WAV and AIFF; the sample pack is FLAC.
	mFormatManager.registerBasicFormats();
	mFormatManager.registerFormat(new juce::FlacAudioFormat(), false);

	// Add voices to the synthesiser
	for (int i = 0; i < kNumVoices; ++i)
	{
		mSampler.addVoice(new OrchestraVoice(&mControllerState));
	}
}


std::set<Articulation> OrchestraSampler::getAvailableArticulationsForInstrument(const InstrumentID key)
{
	auto				   samples = mSamplesManager->getSamplesForInstrument(key);

	std::set<Articulation> availableArticulations{};

	for (auto &s : samples)
	{
		availableArticulations.insert(s.articulation);
	}

	return availableArticulations;
}


std::vector<juce::SynthesiserSound::Ptr> OrchestraSampler::buildSounds(const InstrumentID key, Articulation articulationUsed)
{
	std::vector<juce::SynthesiserSound::Ptr> built;

	auto									 samples = mSamplesManager->getSamplesForInstrument(key);

	if (samples.empty())
	{
		LOG_WARNING("No samples found for instrument key {}", key);
		return built;
	}

	auto filteredSamples = filterArticulation(samples, articulationUsed);
	auto noteDynamicMap	 = createDynamicMap(filteredSamples);
	auto noteRanges		 = createNoteRangeMap(noteDynamicMap, key);

	if (noteRanges.empty())
		return built;

	built.reserve(noteDynamicMap.size());

	for (auto &notePair : noteDynamicMap)
	{
		const int midiNote		   = notePair.first;
		const int rangeLow		   = noteRanges[midiNote].first;
		const int rangeHigh		   = noteRanges[midiNote].second;

		auto	  orchestraSound   = juce::SynthesiserSound::Ptr(new OrchestraSound(rangeLow, rangeHigh, midiNote));
		auto	 *asOrchestraSound = static_cast<OrchestraSound *>(orchestraSound.get());

		asOrchestraSound->setArticulation(articulationUsed);

		for (auto &dynPair : notePair.second)
		{
			const int								   dynValue	  = dynPair.first;
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

			asOrchestraSound->addDynamicLayer(static_cast<Dynamics>(dynValue), std::move(rrBuffers));
		}

		built.push_back(orchestraSound);
	}

	return built;
}


void OrchestraSampler::installSounds(std::vector<juce::SynthesiserSound::Ptr> sounds)
{
	reset();

	for (auto &sound : sounds)
		mSampler.addSound(sound.get());

	if (mSampler.getNumSounds() > 0)
	{
		setSamplesAreReady(true);
		LOG_INFO("Samples loaded! (NumSounds = {})", mSampler.getNumSounds());
	}
}


void OrchestraSampler::addSoundsFromInstrumentToSampler(const InstrumentID key, Articulation articulationUsed)
{
	installSounds(buildSounds(key, articulationUsed));
}


void OrchestraSampler::loadInstrumentAsync(const InstrumentID key, Articulation articulationUsed, SampleLoadCallback onComplete)
{
	const int generation = mLoadGeneration.fetch_add(1) + 1;

	reset();

	juce::WeakReference<OrchestraSampler> weakThis(this);

	mLoadPool.addJob(
		[weakThis, key, articulationUsed, generation, onComplete]() mutable
		{
			if (weakThis == nullptr)
				return;

			auto sounds = weakThis->buildSounds(key, articulationUsed);

			juce::MessageManager::callAsync(
				[weakThis, sounds = std::move(sounds), generation, onComplete]() mutable
				{
					if (weakThis == nullptr)
						return;

					// A newer request has already been issued; this result is stale.
					if (generation != weakThis->mLoadGeneration.load())
						return;

					weakThis->installSounds(std::move(sounds));

					if (onComplete)
						onComplete(weakThis->getSamplesAreReady());
				});
		});
}


void OrchestraSampler::process(juce::AudioBuffer<float> &buffer, juce::MidiBuffer &midiMessages)
{
	if (!getSamplesAreReady())
		return;

	for (const auto meta : midiMessages)
	{
		const auto m = meta.getMessage();

		if (!m.isController())
			continue;

		const float value = static_cast<float>(m.getControllerValue());

		if (m.getControllerNumber() == kModWheelCc)
			mControllerState.cc1.store(value, std::memory_order_relaxed);

		else if (m.getControllerNumber() == kExpressionCc)
			mControllerState.cc11.store(value, std::memory_order_relaxed);
	}

	mSampler.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());
}


void OrchestraSampler::prepare(double sampleRate, int samplesPerBlock)
{
	juce::ignoreUnused(samplesPerBlock);

	mSampler.setCurrentPlaybackSampleRate(sampleRate);
}


void OrchestraSampler::reset()
{
	setSamplesAreReady(false);

	mSampler.allNotesOff(0, false);
	mSampler.clearSounds();
}


bool OrchestraSampler::reloadSamples(std::string samplesDirectory)
{
	// Path to samples have been reset, so we will trigger a reload
	mSamplesManager->setSampleDirectory(samplesDirectory);
	mSamplesManager->reloadSamples();
	return true;
}


std::map<int, std::map<int, std::vector<juce::File>>> OrchestraSampler::createDynamicMap(std::vector<Sample> &samples)
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


std::vector<Sample> OrchestraSampler::filterArticulation(std::vector<Sample> &allSamples, Articulation articulationUsed)
{
	std::vector<Sample> filteredSamples;
	std::ranges::copy_if(allSamples, std::back_inserter(filteredSamples), [articulationUsed](const Sample &sample) { return sample.articulation == articulationUsed; });
	return filteredSamples;
}


std::vector<int> OrchestraSampler::createNoteList(std::map<int, std::map<int, std::vector<juce::File>>> &noteDynamicMap)
{
	// Extract all unique MIDI notes into a sorted list
	std::vector<int> noteList;
	noteList.reserve(noteDynamicMap.size());

	for (auto &val : noteDynamicMap)
		noteList.push_back(val.first);

	std::sort(noteList.begin(), noteList.end());

	return noteList;
}


std::map<int, std::pair<int, int>> OrchestraSampler::createNoteRangeMap(std::map<int, std::map<int, std::vector<juce::File>>> &noteDynamicMap, const int key)
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


std::pair<int, int> OrchestraSampler::getRangesOfInstrument(const InstrumentID key)
{
	if (mInstrumentController == nullptr)
		return {};

	auto  instrument	  = mInstrumentController->getInstrument(key);
	auto &range			  = instrument.getRange();
	auto &higherNote	  = range.getWrittenHighNote();
	auto &lowerNote		  = range.getWrittenLowNote();

	int	  lowerNoteValue  = turnNotenameIntoMidinumber(lowerNote);
	int	  higherNoteValue = turnNotenameIntoMidinumber(higherNote);

	return std::pair<int, int>(lowerNoteValue, higherNoteValue);
}


void OrchestraSampler::setSamplesAreReady(bool value)
{
	if (mSamplesAreReady.load() != value)
	{
		mSamplesAreReady.store(value);
	}
}


bool OrchestraSampler::getSamplesAreReady()
{
	return mSamplesAreReady.load();
}
