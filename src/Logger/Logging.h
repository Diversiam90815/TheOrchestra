
#pragma once

#include <string>
#include <Logger.h> // Logger instance from submodule
#include "FileManager.h"

class Logging
{
public:
	Logging();
	~Logging();

	void initLogging();

private:
	std::string mLoggerName	 = "OrchestraLogger";

	const int	mSlowLogTime = 50;

	FileManager mFileManager;
};