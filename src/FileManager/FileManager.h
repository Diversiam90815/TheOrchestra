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

};
