/*
  ==============================================================================

	Module			FileManager
	Description		Managing files and folders

  ==============================================================================
*/

#include "FileManager.h"


FileManager::FileManager()
{
}


FileManager::~FileManager()
{
}


std::string FileManager::getSamplesFolder()
{
	std::filesystem::path projectDir = getProjectDirectory();

	std::filesystem::path samplesDir = projectDir / AssetsFolderName / SampleFolderName;

	return samplesDir.string();
}


std::string FileManager::getInstrumentDataJSONPath()
{
	std::filesystem::path projectDir = getProjectDirectory();

	std::filesystem::path dataDir = projectDir / AssetsFolderName / InstrumentDataFolderName;

	return dataDir.string();
}


std::filesystem::path FileManager::getProjectDirectory()
{
	std::filesystem::path cwd		 = std::filesystem::current_path();
	std::filesystem::path projectDir = cwd / "..";
	return projectDir;
}
