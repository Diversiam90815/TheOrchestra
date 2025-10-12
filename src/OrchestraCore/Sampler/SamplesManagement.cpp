/*
  ==============================================================================
	Module			SamplesManagement
	Description		Managing the samples
  ==============================================================================
*/

#include "SamplesManagement.h"
#include "InstrumentController.h"
#include "Helper.h"

#include <filesystem>


SamplesManagement::SamplesManagement()
{
	std::string sampleFolder = mFileManager.getSamplesFolder();
	mSamplesFolder			 = File(sampleFolder);
}


void SamplesManagement::init()
{
	if (mSamplesFolder.exists() && mSamplesFolder.isDirectory())
	{
		parseSampleFiles();
	}
}


File SamplesManagement::getInstrumentSamplesPath(const InstrumentID &instrumentKey)
{
	for (const auto &section : mSamplesFolder.findChildFiles(File::findDirectories, false))
	{
		String sectionName = section.getFileName();

		for (const auto &instrument : section.findChildFiles(File::findDirectories, false))
		{
			String instrumentName = instrument.getFileName();

			int	   currentKey	  = getInstrumentKey(sectionName, instrumentName);
			if (currentKey == instrumentKey)
			{
				return instrument;
			}
		}
	}
	return File();
}


void SamplesManagement::parseSampleFiles()
{
	for (const auto &section : mSamplesFolder.findChildFiles(File::findDirectories, false))
	{
		for (const auto &instrument : section.findChildFiles(File::findDirectories, false))
		{
			String sectionStr = section.getFileName();

			if (sectionStr == "Percussion")
			{
				for (const auto &percussionType : section.findChildFiles(File::findDirectories, false))
				{
					String percussionTypeStr = percussionType.getFileName();

					if (percussionTypeStr == "Rhythmic")
					{
						for (const auto &instrument : percussionType.findChildFiles(File::findDirectories, false))
						{
							parseRhythmicPercussionFiles(instrument);
						}
					}
					else if (percussionTypeStr == "Melodic")
					{
						for (const auto &instrument : percussionType.findChildFiles(File::findDirectories, false))
						{
							parseInstrumentSamples(instrument, sectionStr);
						}
					}
				}
			}
			else
			{
				// Handle non-percussion instruments
				for (const auto &instrument : section.findChildFiles(File::findDirectories, false))
				{
					parseInstrumentSamples(instrument, sectionStr);
				}
			}
		}
	}
}


void SamplesManagement::parseRhythmicPercussionFiles(const File &instrument)
{
	String instrumentName	  = instrument.getFileName();
	String tmpPercSectionName = "Percussion";
	int	   instrumentKey	  = getInstrumentKey(tmpPercSectionName, instrumentName);

	for (const auto &articulationFolder : instrument.findChildFiles(File::findDirectories, false))
	{
		String		 articulationStr = articulationFolder.getFileName();
		Articulation articulationValue{};
		try
		{
			articulationValue = articulationMap.at(articulationStr);
		}
		catch (std::exception &e)
		{
			LOG_ERROR("Could not locate articulation for {}. Error: {}", articulationStr.toStdString(), e.what());
			continue;
		}

		for (const auto &file : articulationFolder.findChildFiles(File::findFiles, false))
		{
			addPercussionSamples(file, instrumentKey, articulationValue);
		}
	}
}


void SamplesManagement::parseInstrumentSamples(const File &instrumentFolder, String &sectionName)
{
	String instrumentName = instrumentFolder.getFileName();
	int	   instrumentKey  = getInstrumentKey(sectionName, instrumentName);

	for (const auto &articulationFolder : instrumentFolder.findChildFiles(File::findDirectories, false))
	{
		String		 articulationStr = articulationFolder.getFileName();
		Articulation articulationValue{};

		try
		{
			articulationValue = articulationMap.at(articulationStr);
		}
		catch (std::exception &e)
		{
			LOG_ERROR("Could not locate articulation for {}. Error: {}", articulationStr.toStdString(), e.what());
			continue;
		}

		for (const auto &file : articulationFolder.findChildFiles(File::findFiles, false))
		{
			addSample(file, instrumentKey, articulationValue);
		}
	}
}


void SamplesManagement::addPercussionSamples(const File &file, const InstrumentID &key, Articulation articulation)
{
	String		filename = file.getFileNameWithoutExtension();
	StringArray parts	 = StringArray::fromTokens(filename, "_", "");

	if (parts.size() < 3)
	{
		LOG_WARNING("Percussion sample has wrong format. Filename is {}", filename.toStdString().c_str());
		return;
	}

	String note				= parts[0];
	String dynamicString	= parts[1];
	String roundRobinString = parts[2];

	int	   roundRobin		= 0;
	try
	{
		roundRobin = stoi(roundRobinString.toStdString());
	}
	catch (std::exception &e)
	{
		LOG_WARNING("Failed to parse round robin value: {}, Error: {}", roundRobinString.toStdString().c_str(), e.what());
		roundRobin = 1; // Default to first round robin
	}

	int	   dynamic		  = getIndexOfDynamics(dynamicString);

	String instrumentName = file.getParentDirectory().getParentDirectory().getFileName();

	// For percussion, we'll determine the MIDI note based on a mapping
	int	   midiNote		  = turnNotenameIntoMidinumber(note);
	if (midiNote == -1)
	{
		LOG_WARNING("Invalid note name for percussion: {}, defaulting to C3 (60)", note.toStdString().c_str());
		midiNote = 60; // Default to middle C if parsing fails
	}

	PercussionSample sampleInfo(instrumentName, note, roundRobin, static_cast<Dynamics>(dynamic), articulation, file, midiNote);

	// Set percussion element name if we have more than 3 parts in the filename
	if (parts.size() > 3)
	{
		sampleInfo.percussionElementName = parts[3];
	}
	else
	{
		sampleInfo.percussionElementName = instrumentName;
	}

	mInstrumentSamples[key].emplace_back(sampleInfo);

	LOG_INFO("Added percussion sample for instrument {} (Note = {}, MIDI = {}, Element = {})", instrumentName.toStdString().c_str(), note.toStdString().c_str(), midiNote,
			 sampleInfo.percussionElementName.toStdString().c_str());
}


void SamplesManagement::addSample(const File &file, const InstrumentID &key, Articulation articulation)
{
	String		filename = file.getFileNameWithoutExtension();
	StringArray parts	 = StringArray::fromTokens(filename, "_", "");

	if (parts.size() < 3)
	{
		LOG_WARNING("Instrument's sample has wrong format. Filename is {}", filename.toStdString().c_str());
		return; // Invalid file name format
	}

	String note				= parts[0];
	String dynamicString	= parts[1];
	String roundRobinString = parts[2];

	int	   roundRobin		= 0;
	roundRobin				= stoi(roundRobinString.toStdString());

	int	   dynamic			= getIndexOfDynamics(dynamicString);

	String instrumentName	= file.getParentDirectory().getParentDirectory().getFileName();

	Sample sampleInfo(instrumentName, note, roundRobin, static_cast<Dynamics>(dynamic), articulation, file);

	mInstrumentSamples[key].emplace_back(sampleInfo);

	LOG_INFO("Added sample for instrument {} (Dynamic = {}, Note = {})", instrumentName.toStdString().c_str(), dynamicString.toStdString().c_str(), note.toStdString().c_str());
}


int SamplesManagement::getIndexOfDynamics(const String &dynamicString)
{
	int dynamic = 0;

	if (dynamicString.startsWith("v")) // If the dynamic layer is set to a v# value, we hardcode them to the following dynamic layers
	{
		auto it = velocityLayerMap.find(dynamicString);
		if (it != velocityLayerMap.end())
			return static_cast<int>(it->second);

		// Fallback:
		LOG_WARNING("Unhandled velocity layer: {}", dynamicString.toStdString().c_str());
		return static_cast<int>(Dynamics::mezzoForte);
	}
	else // Otherwise see if it is in the standart dynamic map
	{
		auto it = dynamicMap.find(dynamicString);
		if (it != dynamicMap.end())
			return static_cast<int>(it->second);

		// Fallback:
		LOG_WARNING("Unknown dynamic token: {}", dynamicString.toStdString().c_str());
		dynamic = static_cast<int>(Dynamics::mezzoForte);
	}

	return dynamic;
}


std::vector<Sample> SamplesManagement::getSamplesForInstrument(const InstrumentID &instrumentKey) const
{
	auto it = mInstrumentSamples.find(instrumentKey);
	if (it != mInstrumentSamples.end())
	{
		return it->second;
	}
	LOG_WARNING("Could not find instrument's samples with the key {}", instrumentKey);
	return {};
}
