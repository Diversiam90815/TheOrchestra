/*
  ==============================================================================
	Module			SampleCatalog
	Description		Managing the samples
  ==============================================================================
*/

#pragma once

#include "JuceIncludes.h"

#include "FileManager.h"
#include "Parameters.h"
#include "Helper.h"
#include "UserConfig.h"
#include "SamplerStructs.h"


class SampleCatalog
{
public:
	SampleCatalog()	 = default;
	~SampleCatalog() = default;

	void				init();

	std::vector<Sample> getSamplesForInstrument(const InstrumentID &instrumentKey) const;

	void				setSampleDirectory(std::string directory);

	void				loadSamples(); // TODO: Make async
	void				reloadSamples();

private:
	void										parseRhythmicPercussionFiles(const juce::File &instrument);
	void										parseInstrumentSamples(const juce::File &instrumentFolder, std::string &sectionName);

	void										addPercussionSamples(const juce::File &file, const InstrumentID &key, Articulation articulation);
	void										addSample(const juce::File &file, const InstrumentID &key, Articulation articulation);

	int											getIndexOfDynamics(const std::string &dynamicsString);

	int											parseRoundRobin(const std::string &token);


	std::string									mSampleDirectory;	// Folder of the samples folder ( /Assets/Samples)

	std::map<InstrumentID, std::vector<Sample>> mInstrumentSamples; // Map of the instrument and their assigned 'Sample'

	FileManager									mFileManager;

	UserConfig									mUserConfig;
};
