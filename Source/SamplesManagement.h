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
	pianissimo = 1,
	piano,
	mezzoPiano,
	mezzoForte,
	forte,
	fortissimo
};

std::map<String, dynamics> dynamicMap = {{"pp", dynamics::pianissimo}, {"p", dynamics::piano}, {"mp", dynamics::mezzoPiano},
										 {"mf", dynamics::mezzoForte}, {"f", dynamics::forte}, {"ff", dynamics::fortissimo}};

struct Sample
{
	Sample(const String &instrument, const String &note, const int &roundRobin, const int &dynamic, std::unique_ptr<AudioSampleBuffer> buffer)
		: instrument(instrument), note(note), roundRobin(roundRobin), dynamic(dynamic), buffer(std::move(buffer))
	{
	}

	String							   instrument;
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
	void							   parseSampleFiles();

	void							   addSample(const File &file, const int &key);

	File							   getInstrumentSamplesPath(const int &instrumentKey);

	int								   getIndexOfDynamics(const String &dynamicsString);

	File							   mSamplesFolder;
	AudioFormatManager				   mFormatManager;
	std::map<int, std::vector<Sample>> mInstrumentSamples;
};