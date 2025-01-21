/*
  ==============================================================================

	Module			SamplesManagerment
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


File SamplesManagement::getInstrumentSamplesPath(const int &instrumentKey)
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
			String sectionStr	 = section.getFileName();
			String instrumentStr = instrument.getFileName();
			int	   key			 = getInstrumentKey(sectionStr, instrumentStr);

			if (sectionStr == "Percussion") // Pass the percussion for now, since they need different handling
				continue;

			// Find articulations
			for (const auto &articulationFolder : instrument.findChildFiles(File::findDirectories, false))
			{
				String		 articulationStr   = articulationFolder.getFileName();
				Articulation articulationValue = articulationMap.at(articulationStr);

				for (const auto &file : articulationFolder.findChildFiles(File::findFiles, false))
				{
					addSample(file, key, articulationValue);
				}
			}
		}
	}
}


void SamplesManagement::addSample(const File &file, const int &key, Articulation articulation)
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

	int	   dynamic			= getIndexOfDynamics(dynamicString); // V values need to be adapted

	String instrumentName	= file.getParentDirectory().getFileName();

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


std::vector<Sample> SamplesManagement::getSamplesForInstrument(const int &instrumentKey) const
{
	auto it = mInstrumentSamples.find(instrumentKey);
	if (it != mInstrumentSamples.end())
	{
		return it->second;
	}
	LOG_WARNING("Could not find instrument's samples with the key {}", instrumentKey);
	return {};
}
