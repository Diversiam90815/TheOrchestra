/*
  ==============================================================================
	Module			FileManager
	Description		Managing files and folders
  ==============================================================================
*/

#pragma once

#include <string>
#include <filesystem>
#include <cstdlib>

#include "Parameters.h"
#include "Helper.h"
#include "JuceIncludes.h"

enum class TypeOfImage
{
	InstrumentImage = 1
};


class FileManager
{
public:
	FileManager()  = default;
	~FileManager() = default;

	std::string			  getDefaultSamplesFolderPath();

	juce::File			  getInstrumentImage(TypeOfImage type, InstrumentID instrumentKey);

	std::filesystem::path getProjectsAppDataPath();
	std::filesystem::path getLoggingPath();
	std::filesystem::path getConfigFilePath();

private:
	std::filesystem::path	 getExecutableDirectory(); // Gets the directory containing the executable
	std::filesystem::path	 getAssetsFolder();		   // Gets the assets folder

	std::vector<std::string> getInstrumentsImages(InstrumentID instrumentKey);

	std::vector<std::string> getInstrumentImages(const std::string &family, const std::string &instrumentName);


	std::string				 AssetsFolderName = "Assets";
	std::string				 SampleFolderName = "Samples";
	std::string				 ImageFolderName  = "Images";
};
