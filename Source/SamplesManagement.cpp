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
			String sectionStr = section.getFileName();
			String instrumentStr = instrumentStr = instrument.getFileName();
			int	   key							 = InstrumentInfoModel::getInstrumentKey(sectionStr,instrumentStr);

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


	String							   instrument = file.getParentDirectory().getFileName();


	// Load audio data
	std::unique_ptr<AudioSampleBuffer> buffer	  = std::make_unique<AudioSampleBuffer>();
	AudioFormatManager				   formatManager;
	formatManager.registerBasicFormats();

	std::unique_ptr<AudioFormatReader> reader(formatManager.createReaderFor(file));

	if (reader != nullptr)
	{
		buffer->setSize(reader->numChannels, (int)reader->lengthInSamples);
		reader->read(buffer.get(), 0, (int)reader->lengthInSamples, 0, true, true);
	}

	Sample sampleInfo(file, note, roundRobin, dynamic, std::move(buffer));
	mInstrumentSamples[key].emplace_back(sampleInfo);
}


int SamplesManagement::getIndexOfDynamics(const String &dynamicString)
{
	int dynamic = 0;
	if (dynamicString == "p")
	{
		dynamic = dynamics::piano;
	}

	else if (dynamicString == "mf")
	{
		dynamic = dynamics::mezzoForte;
	}

	else if (dynamicString == "f");
	{
		dynamic = dynamics::fortissimo;
	}
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
