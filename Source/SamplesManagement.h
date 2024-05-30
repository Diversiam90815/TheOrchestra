/*
  ==============================================================================

	SamplesManagement.h
	Created: 30 May 2024 12:55:35pm
	Author:  Jens.Langenberg

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

enum dynamics
{
	piano = 1,
	mezzoForte,
	fortissimo
};


struct Sample
{
	Sample(const File &file, const String &note, const int &roundRobin, const int &dynamic, std::unique_ptr<AudioSampleBuffer> buffer)
		: file(file), note(note), roundRobin(roundRobin), dynamic(dynamic), buffer(std::move(buffer))
	{
	}

	File							   file;
	String							   note;
	int								   roundRobin;
	int								   dynamic;
	std::unique_ptr<AudioSampleBuffer> buffer;
};


class SamplesManagement
{
public:
	SamplesManagement();
	~SamplesManagement() = default;

	void				init();


	std::vector<Sample> getSamplesForInstrument(const int &instrumentKey) const;


private:
	void								  parseSampleFiles();
	
	void								  addSample(const File &file);

	File								  getInstrumentSamplesPath(const int &instrumentKey);


	File								  mSamplesFolder;
	std::map<String, std::vector<Sample>> mInstrumentSamples;
};