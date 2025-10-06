/*
  ==============================================================================
	Module			Logging
	Description		Logging instance providing logging features for the project
  ==============================================================================
*/

#include "Logging.h"


void Logging::initLogging()
{
	auto		logfolder = mFileManager.getLoggingPath();
	auto		logfile	  = logfolder / LogFile;
	std::string logStr	  = logfile.string();

	logging::addMSVCOutput().checkForPresentDebugger(true).setLevel(LogLevel::Debug).setMaxSkipDuration(std::chrono::microseconds(mSlowLogTime));

	using namespace filesize;
	logging::addFileOutput()
		.setFilename(logStr)
		.setLevel(LogLevel::Info)
		.setMaxFiles(10)
		.setMaxFileSize(10_MB)
		.setMaxSkipDuration(std::chrono::microseconds(mSlowLogTime))
		.setRotateOnSession(true);
}
