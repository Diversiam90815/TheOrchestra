/*
  ==============================================================================

	Module			FileManager
	Description		Managing files and folders

  ==============================================================================
*/

#pragma once

#include "string"
#include "filesystem"

#include "Parameters.h"
#include "Helper.h"


class FileManager
{
public:
	FileManager();
	~FileManager();

	std::string				 getSamplesFolder();

	std::string				 getInstrumentDataJSONPath();

	std::vector<std::string> getInstrumentsImagesFolder(int instrumentKey);


private:
	// Gets the project's directory
	std::filesystem::path getProjectDirectory();

	std::vector<std::string> getInstrumentImages(const std::string &family, const std::string &instrumentName);


	std::string			  AssetsFolderName		   = "Assets";

	std::string			  SampleFolderName		   = "Samples";

	std::string			  ImageFolderName		   = "Images";

	std::string			  InstrumentDataFolderName = "InstrumentData";

	std::string			  InstrumentsDataFileName  = "Instruments.json";
};
