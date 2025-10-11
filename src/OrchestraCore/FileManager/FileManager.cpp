/*
  ==============================================================================
	Module			FileManager
	Description		Managing files and folders
  ==============================================================================
*/

#include "FileManager.h"


std::string FileManager::getSamplesFolder()
{
	std::filesystem::path projectDir = getProjectDirectory();

	std::filesystem::path samplesDir = projectDir / AssetsFolderName / SampleFolderName;

	return samplesDir.string();
}


std::string FileManager::getInstrumentDataJSONPath()
{
	std::filesystem::path projectDir = getProjectDirectory();

	std::filesystem::path dataDir	 = projectDir / AssetsFolderName / InstrumentDataFolderName / InstrumentsDataFileName;

	return dataDir.string();
}


std::vector<std::string> FileManager::getInstrumentsImages(int instrumentKey)
{
	std::string familyName	   = getFamilyNameFromKey(instrumentKey);
	std::string instrumentName = getInstrumentNameFromKey(instrumentKey);

	return getInstrumentImages(familyName, instrumentName);
}


File FileManager::getInstrumentImage(TypeOfImage type, int instrumentKey)
{
	auto   images = getInstrumentsImages(instrumentKey);

	String filter = "";
	switch (type)
	{
	case (TypeOfImage::InstrumentImage):
	{
		filter = "instrument";
		break;
	}
	case (TypeOfImage::LowerRangeNotation):
	{
		filter = "range_low";
		break;
	}
	case (TypeOfImage::UpperRangeNotation):
	{
		filter = "range_high";
		break;
	}
	case (TypeOfImage::TranspositionLowerNotation):
	{
		filter = "transposition_low";
		break;
	}
	case (TypeOfImage::TranspositionHigherNotation):
	{
		filter = "transposition_high";
		break;
	}
	default: return File();
	}

	// Find an image within the folder that has the name "instrument"
	auto it = std::find_if(images.begin(), images.end(), [&filter](const String &imagePath) { return imagePath.containsIgnoreCase(filter); });

	// Check if it was found
	if (it != images.end())
	{
		File path = File(*it);
		return path;
	}

	return File(); // return empty file it not found
}


std::filesystem::path FileManager::getProjectsAppDataPath()
{
	// Get the APPDATA environment variable
	const char *appDataEnv = std::getenv("APPDATA");
	if (appDataEnv == nullptr)
	{
		throw std::runtime_error("APPDATA environment variable is not set");
	}

	std::filesystem::path appDataPath(appDataEnv);

	std::filesystem::path projectAppDataPath = appDataPath / ProjectName;

	if (!std::filesystem::exists(projectAppDataPath))
	{
		std::filesystem::create_directories(projectAppDataPath);
	}

	return projectAppDataPath;
}


std::filesystem::path FileManager::getLoggingPath()
{
	std::filesystem::path projectAppDataPath = getProjectsAppDataPath();

	std::filesystem::path logFolder			 = projectAppDataPath / LogFolderName;

	if (!std::filesystem::exists(logFolder))
	{
		std::filesystem::create_directories(logFolder);
	}

	return logFolder;
}


std::filesystem::path FileManager::getProjectDirectory()
{
	std::filesystem::path cwd		 = std::filesystem::current_path();
	std::filesystem::path projectDir = cwd.parent_path().parent_path().parent_path(); // TODO: Use built folder instead of project folder for assets
	return projectDir;
}


std::vector<std::string> FileManager::getInstrumentImages(const std::string &family, const std::string &instrumentName)
{
	std::filesystem::path	 projectDir = getProjectDirectory();
	std::filesystem::path	 imagesDir	= projectDir / AssetsFolderName / ImageFolderName / family / instrumentName;

	std::vector<std::string> images;
	images.reserve(4); // there should be 3-4 images in the folder

	if (std::filesystem::exists(imagesDir) && std::filesystem::is_directory(imagesDir))
	{
		for (const auto &entry : std::filesystem::directory_iterator(imagesDir))
		{
			if (entry.is_regular_file())
			{
				auto ext = entry.path().extension().string();
				std::transform(ext.begin(), ext.end(), ext.begin(), ::tolower);
				if (ext == ".png" || ext == ".jpg" || ext == ".jpeg")
				{
					images.push_back(entry.path().string());
				}
			}
		}
	}

	return images;
}
