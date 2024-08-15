/*
  ==============================================================================

	SamplesManagement.cpp
	Created: 30 May 2024 12:55:35pm
	Author:  Jens.Langenberg

  ==============================================================================
*/

#include "SamplesManagement.h"
#include "InstrumentInfoModel.h"


SamplesManagement::SamplesManagement()
{
	mSamplesFolder = File::getCurrentWorkingDirectory().getChildFile("Assets/Samples");
}


void SamplesManagement::init()
{
	if (mSamplesFolder.exists() && mSamplesFolder.isDirectory())
	{
		parseSampleFiles();
	}

	mFormatManager.registerBasicFormats();
}


File SamplesManagement::getInstrumentSamplesPath(const int &instrumentKey)
{
	for (const auto &section : mSamplesFolder.findChildFiles(File::findDirectories, false))
	{
		String sectionName = section.getFileName();

		for (const auto &instrument : section.findChildFiles(File::findDirectories, false))
		{
			String instrumentName = instrument.getFileName();

			int	   currentKey	  = InstrumentInfoModel::getInstrumentKey(sectionName, instrumentName);
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
			int	   key			 = InstrumentInfoModel::getInstrumentKey(sectionStr, instrumentStr);

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
		return; // Invalid file name format

	String note									  = parts[0];
	String roundRobinString						  = parts[1];
	String dynamicString						  = parts[2];

	int	   roundRobin							  = 0;
	roundRobin									  = stoi(roundRobinString.toStdString());

	int								   dynamic	  = getIndexOfDynamics(dynamicString);


	String							   instrumentName = file.getParentDirectory().getFileName();


	//// Load audio data
	//std::unique_ptr<AudioSampleBuffer> buffer	  = std::make_unique<AudioSampleBuffer>();

	//std::unique_ptr<AudioFormatReader> reader(mFormatManager.createReaderFor(file));

	//if (reader != nullptr)
	//{
	//	buffer->setSize(reader->numChannels, (int)reader->lengthInSamples);
	//	reader->read(buffer.get(), 0, (int)reader->lengthInSamples, 0, true, true);
	//}

	//Sample sampleInfo(instrumentName, note, roundRobin, dynamic, std::move(buffer));
	//mInstrumentSamples[key].emplace_back(sampleInfo);

	
    // Create an AudioFormatReader
	std::unique_ptr<AudioFormatReader> reader(mFormatManager.createReaderFor(file));

	if (reader != nullptr)
	{
		Sample sampleInfo(instrumentName, note, roundRobin, dynamic, std::move(reader));
		mInstrumentSamples[key].emplace_back(std::move(sampleInfo));
	}
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
	return {};
}
