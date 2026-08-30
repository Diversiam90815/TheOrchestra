/*
  ==============================================================================
	Module			SampleCatalog
	Description		Scans the configured samples folder on disk and builds the map
					(InstrumentID -> Sample)
  ==============================================================================
*/

#pragma once

#include <filesystem>
#include <functional>

#include "JuceIncludes.h"

#include "FileManager.h"
#include "Parameters.h"
#include "Helper.h"
#include "UserConfig.h"
#include "SamplerStructs.h"
#include "SamplerTypes.h"


class SampleCatalog
{
public:
	SampleCatalog() = default;
	~SampleCatalog();

	void				init();

	std::vector<Sample> getSamplesForInstrument(const InstrumentID &instrumentKey) const;

	void				setSampleDirectory(std::string directory);

	void				loadSamplesAsync(CatalogLoadCallback onComplete = nullptr);
	void				reloadSamplesAsync(CatalogLoadCallback onComplete = nullptr);

	bool				isLoading() const { return mIsLoading.load(); }

private:
	void				parseRhythmicPercussionFiles(const fs::path &instrument);
	void				parseInstrumentSamples(const fs::path &instrumentFolder, const std::string &sectionName);

	void				loadStandardSection(const fs::path &section, const std::string &sectionName);
	void				loadPercussionSection(const fs::path &section);

	void				addPercussionSamples(const fs::path &file, const InstrumentID &key, Articulation articulation);
	void				addSample(const fs::path &file, const InstrumentID &key, Articulation articulation);

	int					getIndexOfDynamics(const std::string &dynamicsString);
	int					parseRoundRobin(const std::string &token);


	std::string			mSampleDirectory;	// Folder of the samples folder ( /Assets/Samples)

	InstrumentSampleMap mInstrumentSamples; // Map of the instrument and their assigned 'Sample'
	mutable std::mutex	mCatalogMutex;

	FileManager			mFileManager;
	UserConfig			mUserConfig;

	std::atomic<bool>	mIsLoading{false};
	std::thread			mLoadThread;
};
