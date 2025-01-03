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

			for (const auto &file : instrument.findChildFiles(File::findFiles, false))
			{
				addSample(file, key);
			}
		}
	}
}


void SamplesManagement::addSample(const File &file, const int &key)
{
	String		filename = file.getFileNameWithoutExtension();
	StringArray parts	 = StringArray::fromTokens(filename, "_", "");

	if (parts.size() < 3)
	{
		LOG_WARNING("Instrument's sample has wrong format. Filename is {}", filename.toStdString().c_str());
		return; // Invalid file name format
	}

	String note				= parts[0];
	String roundRobinString = parts[1];
	String dynamicString	= parts[2];

	int	   roundRobin		= 0;
	roundRobin				= stoi(roundRobinString.toStdString());

	int	   dynamic			= getIndexOfDynamics(dynamicString);

	String instrumentName	= file.getParentDirectory().getFileName();

	Sample sampleInfo(instrumentName, note, roundRobin, dynamic, file);

	mInstrumentSamples[key].emplace_back(sampleInfo);

	LOG_INFO("Added sample for instrument {} (Dynamic = {}, Note = {})", instrumentName.toStdString().c_str(), dynamicString.toStdString().c_str(), note.toStdString().c_str());
}


int SamplesManagement::getIndexOfDynamics(const String &dynamicString)
{
	int dynamic = 0;
	dynamic		= dynamicMap.at(dynamicString);
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
