/*
  ==============================================================================

	Module			Logging
	Description		Logging instance providing logging features for the project

  ==============================================================================
*/

#include "Logging.h"


Logging::Logging()
{
}


Logging::~Logging()
{
}


void Logging::initLogging()
{
	auto logfolder = mFileManager.getLoggingPath();
	auto logfile   = logfolder / LogFile;

	logging::setLoggerName(mLoggerName);

	logging::addMSVCOutput().checkForPresentDebugger(true).setLevel(LogLevel::Debug).setMaxSkipDuration(std::chrono::microseconds(mSlowLogTime));

	using namespace filesize;
	logging::addFileOutput()
		.setFilename(logfile.string())
		.setLevel(LogLevel::Info)
		.setMaxFiles(10)
		.setMaxFileSize(10_MB)
		.setMaxSkipDuration(std::chrono::microseconds(mSlowLogTime))
		.setRotateOnSession(true);
}
