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
			if ( currentKey == instrumentKey)
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
			for (const auto &file : instrument.findChildFiles(File::findFiles, false))
			{
				addSample(file);
			}
		}
	}
}


void SamplesManagement::addSample(const File &file)
{
	String		filename = file.getFileNameWithoutExtension();
	StringArray parts	 = StringArray::fromTokens(filename, "_", "");

	if (parts.size() < 3)
		return; // Invalid file name format

	String							   note		  = parts[0];
	String							   roundRobin = parts[1];
	String							   dynamic	  = parts[2];

	// Extract the instrument name from the folder structure
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
	mInstrumentSamples[instrument].emplace_back(sampleInfo);
}


std::vector<Sample> SamplesManagement::getSamplesForInstrument(const int &instrumentKey) const
{
	auto it = mInstrumentSamples.find(instrument);
	if (it != mInstrumentSamples.end())
	{
		return it->second;
	}
	return {};
}
