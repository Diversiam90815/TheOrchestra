/*
  ==============================================================================
	Module			SampleCatalog
	Description		Scans the configured samples folder on disk and builds the map
					(InstrumentID -> Sample)
  ==============================================================================
*/


#include <filesystem>

#include "SampleCatalog.h"
#include "InstrumentController.h"
#include "Helper.h"


SampleCatalog::~SampleCatalog()
{
	if (mLoadThread.joinable())
		mLoadThread.join();
}


void SampleCatalog::init()
{
	mUserConfig.init();
	mSampleDirectory = mUserConfig.getSavedSamplesFolder();

	// If the sample directory is empty, set it to a default value
	if (mSampleDirectory.empty())
	{
		mSampleDirectory = mFileManager.getDefaultSamplesFolderPath();
		setSampleDirectory(mSampleDirectory);
	}
}


void SampleCatalog::loadSamplesAsync(CatalogLoadCallback onComplete)
{
	if (mLoadThread.joinable())
		mLoadThread.join();

	mIsLoading.store(true);

	mLoadThread = std::thread(
		[this, onComplete]()
		{
			for (const auto &section : FileManager::findChildDirectories(mSampleDirectory))
			{
				std::string sectionString = section.filename().string();

				if (sectionString == "Percussion")
					loadPercussionSection(section);
				else
					loadStandardSection(section, sectionString);
			}

			mIsLoading.store(false);

			if (onComplete)
				onComplete(true);
		});
}


void SampleCatalog::reloadSamplesAsync(CatalogLoadCallback onComplete)
{
	{
		std::scoped_lock lock(mCatalogMutex);
		mInstrumentSamples.clear();
	}

	loadSamplesAsync(onComplete);
}


void SampleCatalog::parseRhythmicPercussionFiles(const fs::path &instrument)
{
	std::string instrumentName	   = instrument.filename().string();
	std::string tmpPercSectionName = "Percussion";
	int			instrumentKey	   = getInstrumentKey(tmpPercSectionName, instrumentName);

	for (const auto &articulationFolder : FileManager::findChildDirectories(instrument))
	{
		std::string	 articulationStr = articulationFolder.filename().string();
		Articulation articulationValue{};

		const auto	 articulationIt = articulationMap.find(articulationStr);

		if (articulationIt == articulationMap.end())
		{
			LOG_ERROR("Could not locate articulation for {}", articulationStr);
			continue;
		}

		articulationValue = articulationIt->second;

		for (const auto &file : FileManager::findChildFiles(articulationFolder))
			addPercussionSamples(file, instrumentKey, articulationValue);
	}
}


void SampleCatalog::parseInstrumentSamples(const fs::path &instrumentFolder, const std::string &sectionName)
{
	std::string instrumentName = instrumentFolder.filename().string();
	int			instrumentKey  = getInstrumentKey(sectionName, instrumentName);

	for (const auto &articulationFolder : FileManager::findChildDirectories(instrumentFolder))
	{
		std::string	 articulationStr = articulationFolder.filename().string();
		Articulation articulationValue{};

		const auto	 articulationIt = articulationMap.find(articulationStr);

		if (articulationIt == articulationMap.end())
		{
			LOG_ERROR("Could not locate articulation for {}", articulationStr);
			continue;
		}

		articulationValue = articulationIt->second;

		for (const auto &file : FileManager::findChildFiles(articulationFolder))
			addSample(file, instrumentKey, articulationValue);
	}
}


void SampleCatalog::loadStandardSection(const fs::path &section, const std::string &sectionName)
{
	for (const auto &instrument : FileManager::findChildDirectories(section))
		parseInstrumentSamples(instrument, sectionName);
}


void SampleCatalog::loadPercussionSection(const fs::path &section)
{
	for (const auto &percussionType : FileManager::findChildDirectories(section))
	{
		std::string percussionTypeStr = percussionType.filename().string();

		if (percussionTypeStr == "Rhythmic")
		{
			for (const auto &instrument : FileManager::findChildDirectories(percussionType))
				parseRhythmicPercussionFiles(instrument);
		}
		else if (percussionTypeStr == "Melodic")
		{
			for (const auto &instrument : FileManager::findChildDirectories(percussionType))
				parseInstrumentSamples(instrument, "Percussion");
		}
	}
}


void SampleCatalog::addPercussionSamples(const fs::path &file, const InstrumentID &key, Articulation articulation)
{
	std::string				 filename = file.stem().string();
	std::vector<std::string> parts	  = FileManager::splitTokens(filename, '_');

	if (parts.size() < 3)
	{
		LOG_WARNING("Percussion sample has wrong format. Filename is {}", filename.c_str());
		return;
	}

	std::string note			 = parts[0];
	std::string dynamicString	 = parts[1];
	std::string roundRobinString = parts[2];

	const int	roundRobin		 = parseRoundRobin(roundRobinString);
	int			dynamic			 = getIndexOfDynamics(dynamicString);

	std::string instrumentName	 = file.parent_path().parent_path().filename().string();

	// For percussion, we'll determine the MIDI note based on a mapping
	int			midiNote		 = turnNotenameIntoMidinumber(note);
	if (midiNote == -1)
	{
		LOG_WARNING("Invalid note name for percussion: {}, defaulting to C3 (60)", note);
		midiNote = 60; // Default to middle C if parsing fails
	}

	PercussionSample sampleInfo(instrumentName, note, roundRobin, static_cast<Dynamics>(dynamic), articulation, file, midiNote);

	// Set percussion element name if we have more than 3 parts in the filename
	if (parts.size() > 3)
		sampleInfo.percussionElementName = parts[3];
	else
		sampleInfo.percussionElementName = instrumentName;

	{
		std::scoped_lock lock(mCatalogMutex);
		mInstrumentSamples[key].emplace_back(sampleInfo);
	}

	LOG_INFO("Added percussion sample for instrument {} (Note = {}, MIDI = {}, Element = {})", instrumentName, note, midiNote, sampleInfo.percussionElementName);
}


void SampleCatalog::addSample(const fs::path &file, const InstrumentID &key, Articulation articulation)
{
	std::string				 filename = file.stem().string();
	std::vector<std::string> parts	  = FileManager::splitTokens(filename, '_');

	if (parts.size() < 3)
	{
		LOG_WARNING("Instrument's sample has wrong format. Filename is {}", filename.c_str());
		return; // Invalid file name format
	}

	std::string note			 = parts[0];
	std::string dynamicString	 = parts[1];
	std::string roundRobinString = parts[2];

	const int	roundRobin		 = parseRoundRobin(roundRobinString);
	int			dynamic			 = getIndexOfDynamics(dynamicString);

	std::string instrumentName	 = file.parent_path().parent_path().filename().string();

	Sample		sampleInfo(instrumentName, note, roundRobin, static_cast<Dynamics>(dynamic), articulation, file);

	{
		std::scoped_lock lock(mCatalogMutex);
		mInstrumentSamples[key].emplace_back(sampleInfo);
	}

	LOG_DEBUG("Added sample for instrument {} (Dynamic = {}, Note = {})", instrumentName, dynamicString, note);
}


int SampleCatalog::getIndexOfDynamics(const std::string &dynamicString)
{
	int dynamic = 0;

	if (dynamicString.starts_with("v")) // If the dynamic layer is set to a v# value, we hardcode them to the following dynamic layers
	{
		auto it = velocityLayerMap.find(dynamicString);
		if (it != velocityLayerMap.end())
			return static_cast<int>(it->second);

		// Fallback:
		LOG_WARNING("Unhandled velocity layer: {}", dynamicString);
		return static_cast<int>(Dynamics::mezzoForte);
	}
	else // Otherwise see if it is in the standart dynamic map
	{
		auto it = dynamicMap.find(dynamicString);
		if (it != dynamicMap.end())
			return static_cast<int>(it->second);

		// Fallback:
		LOG_WARNING("Unknown dynamic token: {}", dynamicString);
		dynamic = static_cast<int>(Dynamics::mezzoForte);
	}

	return dynamic;
}


int SampleCatalog::parseRoundRobin(const std::string &token)
{
	try
	{
		return std::stoi(token);
	}
	catch (const std::exception &e)
	{
		LOG_WARNING("Failed to parse round robin value: {}, Error: {}", token, e.what());
		return 1;
	}
}


std::vector<Sample> SampleCatalog::getSamplesForInstrument(const InstrumentID &instrumentKey) const
{
	auto it = mInstrumentSamples.find(instrumentKey);

	if (it != mInstrumentSamples.end())
		return it->second;

	LOG_WARNING("Could not find instrument's samples with the key {}", instrumentKey);
	return {};
}


void SampleCatalog::setSampleDirectory(std::string directory)
{
	if (directory.empty())
	{
		LOG_WARNING("Tried to set an empty directory for the samples! Skipping..");
		return;
	}

	mSampleDirectory = directory;
	mUserConfig.saveSamplesFolder(directory);
}
