/*
  ==============================================================================
	Module			Logging
	Description		Logging instance providing logging features for the project
  ==============================================================================
*/

#pragma once

#include <string>
#include <Logger.h>
#include "FileManager.h"


class Logging
{
public:
	Logging()  = default;
	~Logging() = default;

	void initLogging();

private:
	std::string mLoggerName	 = "OrchestraLogger";

	const int	mSlowLogTime = 500;

	FileManager mFileManager;
};
