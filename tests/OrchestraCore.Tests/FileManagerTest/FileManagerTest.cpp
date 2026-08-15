/*
  ==============================================================================
	Module          FileManager Tests
	Description     Testing FileManager path logic & directory management
  ==============================================================================
*/

#include <gtest/gtest.h>
#include <filesystem>
#include "FileManager.h"

namespace FileManagerTests
{

class FileManagerTest : public ::testing::Test
{
protected:
	FileManager fm;
};


TEST_F(FileManagerTest, SamplesFolderPathShape)
{
	std::string path = fm.getDefaultSamplesFolderPath();

	// Expect path to contain Assets/Samples regardless of absolute root
	EXPECT_NE(path.find("Assets"), std::string::npos) << "Path should contain Assets";
	EXPECT_NE(path.find("Samples"), std::string::npos) << "Path should contain Samples";
}


TEST_F(FileManagerTest, ProjectsAppDataPathCreated)
{
	try
	{
		auto path = fm.getProjectsAppDataPath();
		EXPECT_TRUE(std::filesystem::exists(path)) << "AppData path should exist!";
		EXPECT_TRUE(std::filesystem::is_directory(path)) << "AppData path should be a directory!";
	}
	catch (const std::exception &e)
	{
		GTEST_SKIP() << "APPDATA not set or inaccessible: " << e.what();
	}
}


TEST_F(FileManagerTest, LoggingPathCreated)
{
	try
	{
		auto logPath = fm.getLoggingPath();
		EXPECT_TRUE(std::filesystem::exists(logPath)) << "Logging path should exist!";
		EXPECT_TRUE(std::filesystem::is_directory(logPath)) << "Logging path should be a directory!";
	}
	catch (const std::exception &e)
	{
		GTEST_SKIP() << "APPDATA not set or inaccessible (logging path): " << e.what();
	}
}


TEST_F(FileManagerTest, GetInstrumentImageNoCrash)
{
	int instrumentKey = 301; // Violin (used elsewhere in tests)

	EXPECT_NO_THROW({ juce::File a = fm.getInstrumentImage(TypeOfImage::InstrumentImage, instrumentKey); }) << "Getting the instrument image should not throw!";
}


TEST_F(FileManagerTest, GetInstrumentImageForUnknownKeyReturnsEmptyFile)
{
	// 999 is not a valid family/instrument combination.
	EXPECT_NO_THROW({
		juce::File file = fm.getInstrumentImage(TypeOfImage::InstrumentImage, 999);
		EXPECT_EQ(file, juce::File()) << "An unknown instrument key should yield an empty file!";
	}) << "An unknown instrument key should not throw!";
}

} // namespace FileManagerTests
