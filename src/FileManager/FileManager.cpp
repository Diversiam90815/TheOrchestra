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


File FileManager::getInstrumentImage(int instrumentKey)
{
	auto images = getInstrumentsImages(instrumentKey);

	// Find an image within the folder that has the name "instrument"
	auto it		= std::find_if(images.begin(), images.end(), [](const String &imagePath) { return imagePath.containsIgnoreCase("instrument"); });

	// Check if it was found
	if (it != images.end())
	{
		File path = File(*it);
		return path;
	}

	return File();	// return empty file it not found
}


std::filesystem::path FileManager::getProjectDirectory()
{
	std::filesystem::path cwd		 = std::filesystem::current_path();
	std::filesystem::path projectDir = cwd.parent_path();
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
