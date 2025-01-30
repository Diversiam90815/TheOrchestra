/*
/*
  ==============================================================================

	Module			SamplesManagement
	Description		Managing the samples

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

#include "FileManager.h"
#include "Parameters.h"
#include "Helper.h"


struct Sample
{
	Sample(const String &instrument, const String &note, const int &roundRobin, const Dynamics &dynamic, const Articulation &articulation, const File &file)
		: instrument(instrument), note(note), roundRobin(roundRobin), dynamic(dynamic), articulation(articulation), file(file)
	{
		noteMidiValue = turnNotenameIntoMidinumber(note);
	}

	String		 instrument;
	String		 note;
	int			 noteMidiValue = 0;
	int			 roundRobin;
	Dynamics	 dynamic;
	Articulation articulation;
	File		 file;

	int			 rangeLow  = 0;
	int			 rengeHigh = 0;
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

	void							   addSample(const File &file, const int &key, Articulation articulation);

	File							   getInstrumentSamplesPath(const int &instrumentKey);

	int								   getIndexOfDynamics(const String &dynamicsString);


	File							   mSamplesFolder;	   // Folder of the samples folder ( /Assets/Samples)

	std::map<int, std::vector<Sample>> mInstrumentSamples; // Map of the instrument (identified by their key) and their assigned 'Sample'

	FileManager						   mFileManager;
};
