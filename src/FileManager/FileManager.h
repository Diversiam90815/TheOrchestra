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
#include <JuceHeader.h>


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
	FileManager();
	~FileManager();

	std::string			  getSamplesFolder();

	std::string			  getInstrumentDataJSONPath();

	File				  getInstrumentImage(TypeOfImage type, int instrumentKey);

	std::filesystem::path getProjectsAppDataPath();

	std::filesystem::path getLoggingPath();

private:
	std::filesystem::path	 getProjectDirectory(); // Gets the project's directory

	std::vector<std::string> getInstrumentsImages(int instrumentKey);

	std::vector<std::string> getInstrumentImages(const std::string &family, const std::string &instrumentName);


	std::string				 AssetsFolderName		  = "Assets";

	std::string				 SampleFolderName		  = "Samples";

	std::string				 ImageFolderName		  = "Images";

	std::string				 InstrumentDataFolderName = "InstrumentData";

	std::string				 InstrumentsDataFileName  = "Instruments.json";

	std::string				 mProjectName			  = ProjectInfo::projectName;

	std::string				 mLogFolderName			  = "Logs";
};
