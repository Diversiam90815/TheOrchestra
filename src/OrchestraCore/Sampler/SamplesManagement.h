/*
  ==============================================================================
	Module			SamplesManagement
	Description		Managing the samples
  ==============================================================================
*/

#pragma once

#include "JuceIncludes.h"

#include "FileManager.h"
#include "Parameters.h"
#include "Helper.h"


struct Sample
{
	Sample(const std::string &instrument, const std::string &note, const int &roundRobin, const Dynamics &dynamic, const Articulation &articulation, const juce::File &file)
		: instrument(instrument), note(note), roundRobin(roundRobin), dynamic(dynamic), articulation(articulation), file(file)
	{
		noteMidiValue = turnNotenameIntoMidinumber(note);
	}

	std::string	 instrument;
	std::string	 note;
	int			 noteMidiValue = 0;
	int			 roundRobin;
	Dynamics	 dynamic;
	Articulation articulation;
	juce::File	 file;

	int			 rangeLow  = 0;
	int			 rangeHigh = 0;
};


struct PercussionSample : public Sample
{
	PercussionSample(const std::string	&instrument,
					 const std::string	&note,
					 const int			&roundRobin,
					 const Dynamics		&dynamic,
					 const Articulation &articulation,
					 const juce::File	&file,
					 int				 specificMidiNote)
		: Sample(instrument, note, roundRobin, dynamic, articulation, file)
	{
		noteMidiValue = specificMidiNote; // Override the noteMidiValue with the specific value for a percussion sound
	}

	std::string percussionElementName;	  // Name of the percussion element (e.g., "Snare", "Kick")
};


class SamplesManagement
{
public:
	SamplesManagement();
	~SamplesManagement() = default;

	void				init();

	std::vector<Sample> getSamplesForInstrument(const InstrumentID &instrumentKey) const;


private:
	void										parseSampleFiles(); // TODO: Make async

	void										parseRhythmicPercussionFiles(const juce::File &instrument);

	void										parseInstrumentSamples(const juce::File &instrumentFolder, std::string &sectionName);

	void										addPercussionSamples(const juce::File &file, const InstrumentID &key, Articulation articulation);

	void										addSample(const juce::File &file, const InstrumentID &key, Articulation articulation);

	juce::File									getInstrumentSamplesPath(const InstrumentID &instrumentKey);

	int											getIndexOfDynamics(const std::string &dynamicsString);


	juce::File									mSamplesFolder;		// Folder of the samples folder ( /Assets/Samples)

	std::map<InstrumentID, std::vector<Sample>> mInstrumentSamples; // Map of the instrument and their assigned 'Sample'

	FileManager									mFileManager;
};
