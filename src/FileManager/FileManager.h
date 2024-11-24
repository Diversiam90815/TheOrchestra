/*
  ==============================================================================

	Module			FileManager
	Description		Managing files and folders

  ==============================================================================
*/

#pragma once

#include "string"
#include "filesystem"


class FileManager
{
public:
	FileManager();
	~FileManager();

	std::string getSamplesFolder();

	std::string getInstrumentDataJSONPath();

private:

	// Gets the project's directory
	std::filesystem::path getProjectDirectory();

	std::string			  AssetsFolderName		   = "Assets";

	std::string			  SampleFolderName		   = "Samples";

	std::string			  InstrumentDataFolderName = "InstrumentData";
};
