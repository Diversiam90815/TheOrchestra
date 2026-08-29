/*
  ==============================================================================
	Module			FileManager
	Description		Managing files and folders
  ==============================================================================
*/

#pragma once

#include <string>
#include <filesystem>
#include <vector>
#include <cstdlib>

#include "Parameters.h"
#include "Helper.h"
#include "JuceIncludes.h"


namespace fs = std::filesystem;


class FileManager
{
public:
	FileManager()  = default;
	~FileManager() = default;

	std::string						getDefaultSamplesFolderPath();

	juce::File						getInstrumentImage(InstrumentID instrumentKey);

	fs::path						getProjectsAppDataPath();
	fs::path						getLoggingPath();
	fs::path						getConfigFilePath();

	static std::vector<fs::path>	findChildDirectories(const fs::path &directory);
	static std::vector<fs::path>	findChildFiles(const fs::path &directory);
	static std::vector<std::string> splitTokens(const std::string &text, char delimiter);

private:
	fs::path				 getExecutableDirectory(); // Gets the directory containing the executable
	fs::path				 getAssetsFolder();		   // Gets the assets folder

	// Places the assets may live, in priority order. See getAssetsFolder().
	std::vector<fs::path>	 getAssetsFolderCandidates();

	std::vector<std::string> getInstrumentsImages(InstrumentID instrumentKey);

	std::vector<std::string> getInstrumentImages(const std::string &family, const std::string &instrumentName);

	static constexpr auto	 AssetsFolderName	   = "Assets";
	static constexpr auto	 SampleFolderName	   = "Samples";
	static constexpr auto	 ImageFolderName	   = "Images";
	static constexpr auto	 InstrumentImageFilter = "instrument";
};
