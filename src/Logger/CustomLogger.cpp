
#include "CustomLogger.h"


CustomLogger::CustomLogger()
{
}

CustomLogger::~CustomLogger()
{
}

void CustomLogger::initLogging()
{
	auto logfolder = mFileManager.getLoggingPath();
	auto logfile = logfolder / mLogFile;

	logging::addConsoleOutput().setLevel(LogLevel::Debug).setMaxSkipDuration(std::chrono::microseconds(mSlowLogTime));

	using namespace filesize;
	logging::addFileOutput()
		.setFilename(logfile.string())
		.setLevel(LogLevel::Info)
		.setMaxFiles(10)
		.setMaxFileSize(10_MB)
		.setMaxSkipDuration(std::chrono::microseconds(mSlowLogTime))
		.setRotateOnSession(true);
}
