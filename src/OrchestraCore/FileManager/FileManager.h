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

enum TypeOfImage
{
	InstrumentImage = 1,
	LowerRangeNotation,
	UpperRangeNotation,
	TranspositionLowerNotation,
	TranspositionHigherNotation
};


class FileManager
{
public:
	FileManager()  = default;
	~FileManager() = default;

	std::string			  getSamplesFolder();

	std::string			  getInstrumentDataJSONPath();

	juce::File			  getInstrumentImage(TypeOfImage type, InstrumentID instrumentKey);

	std::filesystem::path getProjectsAppDataPath();

	std::filesystem::path getLoggingPath();

	void				  setAssetsFolder(const std::filesystem::path &path);

private:
	std::filesystem::path				 getProjectDirectory();	   // Gets the project's directory
	std::filesystem::path				 getExecutableDirectory(); // Gets the directory containing the executable
	std::filesystem::path				 findAssetsFolder();	   // Searches for Assets folder intelligently


	std::vector<std::string>			 getInstrumentsImages(InstrumentID instrumentKey);

	std::vector<std::string>			 getInstrumentImages(const std::string &family, const std::string &instrumentName);


	std::string							 AssetsFolderName		  = "Assets";
	std::string							 SampleFolderName		  = "Samples";
	std::string							 ImageFolderName		  = "Images";
	std::string							 InstrumentDataFolderName = "InstrumentData";
	std::string							 InstrumentsDataFileName  = "Instruments.json";

	std::optional<std::filesystem::path> mAssetsFolderOverride;
};
