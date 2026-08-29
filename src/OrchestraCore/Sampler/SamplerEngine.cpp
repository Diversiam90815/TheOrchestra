/*
  ==============================================================================
	Module			SamplerEngine
	Description		Sampling the instrument and making them ready for playback
  ==============================================================================
*/

#include "SamplerEngine.h"
#include "InstrumentController.h" // For note ranges


SamplerEngine::~SamplerEngine()
{
	mLoadPool.removeAllJobs(true, 5000);

	mSampler.allNotesOff(0, false);
	mSampler.clearSounds();
	mSampler.clearVoices();
}


void SamplerEngine::init(InstrumentController &controller, SampleLoadCallback onCatalogReady)
{
	mInstrumentController = &controller;
	mSamplesManager		  = std::make_unique<SampleCatalog>();

	mSamplesManager->init();

	juce::WeakReference<SamplerEngine> weakThis(this);

	mSamplesManager->loadSamplesAsync(
		[weakThis, onCatalogReady](bool success)
		{
			juce::MessageManager::callAsync(
				[weakThis, success, onCatalogReady]()
				{
					if (weakThis == nullptr)
						return;

					if (onCatalogReady)
						onCatalogReady(success);
				});
		});

	mFormatManager.registerBasicFormats();

	// Add voices to the synthesiser
	for (int i = 0; i < kNumVoices; ++i)
	{
		mSampler.addVoice(new ArticulationVoice(&mControllerState));
	}
}


std::set<Articulation> SamplerEngine::getAvailableArticulationsForInstrument(const InstrumentID key)
{
	auto				   samples = mSamplesManager->getSamplesForInstrument(key);

	std::set<Articulation> availableArticulations{};

	for (auto &s : samples)
	{
		availableArticulations.insert(s.articulation);
	}

	return availableArticulations;
}


std::vector<juce::SynthesiserSound::Ptr> SamplerEngine::buildSounds(const InstrumentID key, Articulation articulationUsed)
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

		auto	  orchestraSound   = juce::SynthesiserSound::Ptr(new SampleSound(rangeLow, rangeHigh, midiNote));
		auto	 *asOrchestraSound = static_cast<SampleSound *>(orchestraSound.get());

		asOrchestraSound->setArticulation(articulationUsed);

		for (auto &dynPair : notePair.second)
		{
			const int								   dynValue	  = dynPair.first;
			auto									  &fileVector = dynPair.second;

			juce::OwnedArray<juce::AudioBuffer<float>> rrBuffers;

			for (auto &file : fileVector)
			{
				std::unique_ptr<juce::AudioFormatReader> reader(mFormatManager.createReaderFor(juce::File(file.string())));

				if (reader)
				{
					auto *newBuffer = new juce::AudioBuffer<float>((int)reader->numChannels, (int)reader->lengthInSamples);
					reader->read(newBuffer, 0, (int)reader->lengthInSamples, 0, true, true);
					rrBuffers.add(newBuffer);
				}
				else
				{
					LOG_ERROR("Failed to read sample file: {}", file.string());
				}
			}

			asOrchestraSound->addDynamicLayer(static_cast<Dynamics>(dynValue), std::move(rrBuffers));
		}

		built.push_back(orchestraSound);
	}

	return built;
}


void SamplerEngine::installSounds(std::vector<juce::SynthesiserSound::Ptr> sounds)
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


void SamplerEngine::addSoundsFromInstrumentToSampler(const InstrumentID key, Articulation articulationUsed)
{
	installSounds(buildSounds(key, articulationUsed));
}


void SamplerEngine::loadInstrumentAsync(const InstrumentID key, Articulation articulationUsed, SampleLoadCallback onComplete)
{
	const int generation = mLoadGeneration.fetch_add(1) + 1;

	reset();

	juce::WeakReference<SamplerEngine> weakThis(this);

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


void SamplerEngine::process(juce::AudioBuffer<float> &buffer, juce::MidiBuffer &midiMessages)
{
	if (!getSamplesAreReady())
		return;

	for (const auto meta : midiMessages)
	{
		const auto m = meta.getMessage();

		if (!m.isController())
			continue;

		const float value = static_cast<float>(m.getControllerValue());

		if (m.getControllerNumber() == MIDI::ModWheelCC)
			mControllerState.cc1.store(value, std::memory_order_relaxed);

		else if (m.getControllerNumber() == MIDI::ExpressionCC)
			mControllerState.cc11.store(value, std::memory_order_relaxed);
	}

	mSampler.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());
}


void SamplerEngine::prepare(double sampleRate, int samplesPerBlock)
{
	juce::ignoreUnused(samplesPerBlock);

	mSampler.setCurrentPlaybackSampleRate(sampleRate);
}


void SamplerEngine::reset()
{
	setSamplesAreReady(false);

	mSampler.allNotesOff(0, false);
	mSampler.clearSounds();
}


bool SamplerEngine::reloadSamples(std::string samplesDirectory, SampleLoadCallback onComplete)
{
	// Path to samples have been reset, so we will trigger a reload
	mSamplesManager->setSampleDirectory(samplesDirectory);

	juce::WeakReference<SamplerEngine> weakThis(this);

	mSamplesManager->reloadSamplesAsync(
		[weakThis, onComplete](bool success)
		{
			juce::MessageManager::callAsync(
				[weakThis, success, onComplete]()
				{
					if (weakThis == nullptr)
						return;

					if (onComplete)
						onComplete(success);
				});
		});

	return true;
}


std::map<int, std::map<int, std::vector<std::filesystem::path>>> SamplerEngine::createDynamicMap(std::vector<Sample> &samples)
{
	std::map<int, std::map<int, std::vector<std::filesystem::path>>> noteDynMap;

	for (auto &s : samples)
	{
		int midiNote = s.noteMidiValue;
		int dynValue = static_cast<int>(s.dynamic);
		noteDynMap[midiNote][dynValue].push_back(s.file);
	}

	return noteDynMap;
}


std::vector<Sample> SamplerEngine::filterArticulation(std::vector<Sample> &allSamples, Articulation articulationUsed)
{
	std::vector<Sample> filteredSamples;
	std::ranges::copy_if(allSamples, std::back_inserter(filteredSamples), [articulationUsed](const Sample &sample) { return sample.articulation == articulationUsed; });
	return filteredSamples;
}


std::vector<int> SamplerEngine::createNoteList(std::map<int, std::map<int, std::vector<std::filesystem::path>>> &noteDynamicMap)
{
	// Extract all unique MIDI notes into a sorted list
	std::vector<int> noteList;
	noteList.reserve(noteDynamicMap.size());

	for (auto &val : noteDynamicMap)
		noteList.push_back(val.first);

	std::sort(noteList.begin(), noteList.end());

	return noteList;
}


std::map<int, std::pair<int, int>> SamplerEngine::createNoteRangeMap(std::map<int, std::map<int, std::vector<std::filesystem::path>>> &noteDynamicMap, const int key)
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


std::pair<int, int> SamplerEngine::getRangesOfInstrument(const InstrumentID key)
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


void SamplerEngine::setSamplesAreReady(bool value)
{
	if (mSamplesAreReady.load() != value)
	{
		mSamplesAreReady.store(value);
	}
}


bool SamplerEngine::getSamplesAreReady()
{
	return mSamplesAreReady.load();
}
