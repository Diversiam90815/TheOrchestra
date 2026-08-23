/*
  ==============================================================================
	Module			SampleCatalog
	Description		Managing the samples
  ==============================================================================
*/

#include <filesystem>

#include "SampleCatalog.h"
#include "InstrumentController.h"
#include "Helper.h"


void SampleCatalog::init()
{
	mUserConfig.init();
	mSampleDirectory = mUserConfig.getSavedSamplesFolder();

	// If the sample directory is empty, set it to a default value for now (TODO: Give user a message)
	if (mSampleDirectory.empty())
	{
		mSampleDirectory = mFileManager.getDefaultSamplesFolderPath();
		setSampleDirectory(mSampleDirectory);
	}

	loadSamples();
}


void SampleCatalog::loadSamples()
{
	juce::File sampleDirectoryFile = (juce::File)mSampleDirectory;

	for (const auto &section : sampleDirectoryFile.findChildFiles(juce::File::findDirectories, false))
	{
		for (const auto &instrument : section.findChildFiles(juce::File::findDirectories, false))
		{
			std::string sectionStr = section.getFileName().toStdString();

			if (sectionStr == "Percussion")
			{
				for (const auto &percussionType : section.findChildFiles(juce::File::findDirectories, false))
				{
					std::string percussionTypeStr = percussionType.getFileName().toStdString();

					if (percussionTypeStr == "Rhythmic")
					{
						for (const auto &instrument : percussionType.findChildFiles(juce::File::findDirectories, false))
						{
							parseRhythmicPercussionFiles(instrument);
						}
					}
					else if (percussionTypeStr == "Melodic")
					{
						for (const auto &instrument : percussionType.findChildFiles(juce::File::findDirectories, false))
						{
							parseInstrumentSamples(instrument, sectionStr);
						}
					}
				}
			}
			else
			{
				// Handle non-percussion instruments
				for (const auto &instrument : section.findChildFiles(juce::File::findDirectories, false))
				{
					parseInstrumentSamples(instrument, sectionStr);
				}
			}
		}
	}
}


void SampleCatalog::reloadSamples()
{
	mInstrumentSamples.clear();
	loadSamples();
}


void SampleCatalog::parseRhythmicPercussionFiles(const juce::File &instrument)
{
	std::string instrumentName	   = instrument.getFileName().toStdString();
	std::string tmpPercSectionName = "Percussion";
	int			instrumentKey	   = getInstrumentKey(tmpPercSectionName, instrumentName);

	for (const auto &articulationFolder : instrument.findChildFiles(juce::File::findDirectories, false))
	{
		std::string	 articulationStr = articulationFolder.getFileName().toStdString();
		Articulation articulationValue{};

		const auto	 articulationIt = articulationMap.find(articulationStr);

		if (articulationIt == articulationMap.end())
		{
			LOG_ERROR("Could not locate articulation for {}", articulationStr);
			continue;
		}

		articulationValue = articulationIt->second;

		for (const auto &file : articulationFolder.findChildFiles(juce::File::findFiles, false))
		{
			addPercussionSamples(file, instrumentKey, articulationValue);
		}
	}
}


void SampleCatalog::parseInstrumentSamples(const juce::File &instrumentFolder, std::string &sectionName)
{
	std::string instrumentName = instrumentFolder.getFileName().toStdString();
	int			instrumentKey  = getInstrumentKey(sectionName, instrumentName);

	for (const auto &articulationFolder : instrumentFolder.findChildFiles(juce::File::findDirectories, false))
	{
		std::string	 articulationStr = articulationFolder.getFileName().toStdString();
		Articulation articulationValue{};

		const auto	 articulationIt = articulationMap.find(articulationStr);

		if (articulationIt == articulationMap.end())
		{
			LOG_ERROR("Could not locate articulation for {}", articulationStr);
			continue;
		}

		articulationValue = articulationIt->second;

		for (const auto &file : articulationFolder.findChildFiles(juce::File::findFiles, false))
		{
			addSample(file, instrumentKey, articulationValue);
		}
	}
}


void SampleCatalog::addPercussionSamples(const juce::File &file, const InstrumentID &key, Articulation articulation)
{
	juce::String	  filename = file.getFileNameWithoutExtension();
	juce::StringArray parts	   = juce::StringArray::fromTokens(filename, "_", "");

	if (parts.size() < 3)
	{
		LOG_WARNING("Percussion sample has wrong format. Filename is {}", filename.toStdString().c_str());
		return;
	}

	std::string note			 = parts[0].toStdString();
	std::string dynamicString	 = parts[1].toStdString();
	std::string roundRobinString = parts[2].toStdString();

	const int	roundRobin		 = parseRoundRobin(roundRobinString);
	int			dynamic			 = getIndexOfDynamics(dynamicString);

	std::string instrumentName	 = file.getParentDirectory().getParentDirectory().getFileName().toStdString();

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
		sampleInfo.percussionElementName = parts[3].toStdString();
	else
		sampleInfo.percussionElementName = instrumentName;

	mInstrumentSamples[key].emplace_back(sampleInfo);

	LOG_INFO("Added percussion sample for instrument {} (Note = {}, MIDI = {}, Element = {})", instrumentName, note, midiNote, sampleInfo.percussionElementName);
}


void SampleCatalog::addSample(const juce::File &file, const InstrumentID &key, Articulation articulation)
{
	juce::String	  filename = file.getFileNameWithoutExtension();
	juce::StringArray parts	   = juce::StringArray::fromTokens(filename, "_", "");

	if (parts.size() < 3)
	{
		LOG_WARNING("Instrument's sample has wrong format. Filename is {}", filename.toStdString().c_str());
		return; // Invalid file name format
	}

	std::string note			 = parts[0].toStdString();
	std::string dynamicString	 = parts[1].toStdString();
	std::string roundRobinString = parts[2].toStdString();

	const int	roundRobin		 = parseRoundRobin(roundRobinString);
	int			dynamic			 = getIndexOfDynamics(dynamicString);

	std::string instrumentName	 = file.getParentDirectory().getParentDirectory().getFileName().toStdString();

	Sample		sampleInfo(instrumentName, note, roundRobin, static_cast<Dynamics>(dynamic), articulation, file);

	mInstrumentSamples[key].emplace_back(sampleInfo);

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
