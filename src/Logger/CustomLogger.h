
#pragma once

#include <string>
#include <Logger.h> // Logger instance from submodule
#include "FileManager.h"

class CustomLogger
{
public:
	CustomLogger();
	~CustomLogger();

	void initLogging();

private:
	std::string mLoggerName;

	std::string mLogFile = "Orchestra.log";

	const int	mSlowLogTime;

	FileManager mFileManager;
};