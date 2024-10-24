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
	std::filesystem::path cwd = std::filesystem::current_path();
	std::filesystem::path newdir = cwd / ".." / "Assets" / "Samples";

	return newdir.string();
}
