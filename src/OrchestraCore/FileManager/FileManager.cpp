/*
  ==============================================================================
	Module			FileManager
	Description		Managing files and folders
  ==============================================================================
*/

#include "FileManager.h"


std::string FileManager::getDefaultSamplesFolderPath()
{
	std::filesystem::path projectDir = getAssetsFolder();

	std::filesystem::path samplesDir = projectDir / SampleFolderName;

	return samplesDir.string();
}


std::vector<std::string> FileManager::getInstrumentsImages(InstrumentID instrumentKey)
{
	std::string familyName	   = getFamilyNameFromKey(instrumentKey);
	std::string instrumentName = getInstrumentNameFromKey(instrumentKey);

	return getInstrumentImages(familyName, instrumentName);
}


juce::File FileManager::getInstrumentImage(TypeOfImage type, InstrumentID instrumentKey)
{
	auto		images = getInstrumentsImages(instrumentKey);

	std::string filter;
	switch (type)
	{
	case TypeOfImage::InstrumentImage: filter = "instrument"; break;
	default: return juce::File();
	}

	// Find an image within the folder whose name matches the filter
	auto it = std::find_if(images.begin(), images.end(), [&filter](const std::string &imagePath) { return juce::String(imagePath).containsIgnoreCase(filter); });

	// Check if it was found
	if (it != images.end())
	{
		juce::File path = juce::File(*it);
		return path;
	}

	return juce::File(); // return empty file it not found
}


std::filesystem::path FileManager::getProjectsAppDataPath()
{
	const auto appDataDir = juce::File::getSpecialLocation(juce::File::userApplicationDataDirectory);

	if (appDataDir == juce::File())
	{
		throw std::runtime_error("Could not resolve the user application data directory");
	}

	std::filesystem::path appDataPath(appDataDir.getFullPathName().toStdString());

	// Test binaries get their own AppData namespace so running them never reads or overwrites a real user's saved settings.
	auto				  exeName			 = juce::File::getSpecialLocation(juce::File::currentExecutableFile).getFileNameWithoutExtension();
	const char			 *projectName		 = exeName.containsIgnoreCase("Tests") ? TestProjectName : ProjectName;

	std::filesystem::path projectAppDataPath = appDataPath / projectName;

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


std::filesystem::path FileManager::getExecutableDirectory()
{
	auto exePath = juce::File::getSpecialLocation(juce::File::currentExecutableFile);
	return std::filesystem::path(exePath.getParentDirectory().getFullPathName().toStdString());
}


std::filesystem::path FileManager::getAssetsFolder()
{
	// Assets are copied next to the executable at build time (see cmake/Assets.cmake), so resolve relative to it
	// rather than the current working directory, which varies depending on how the process is launched.
	return getExecutableDirectory() / AssetsFolderName;
}


std::filesystem::path FileManager::getConfigFilePath()
{
	std::filesystem::path projectAppDataPath = getProjectsAppDataPath();

	std::filesystem::path configFolder		 = projectAppDataPath / ConfigFolderName;

	if (!std::filesystem::exists(configFolder))
	{
		std::filesystem::create_directories(configFolder);
	}

	return configFolder;
}


std::vector<std::string> FileManager::getInstrumentImages(const std::string &family, const std::string &instrumentName)
{
	std::filesystem::path	 projectDir = getAssetsFolder();
	std::filesystem::path	 imagesDir	= projectDir / ImageFolderName / family / instrumentName;

	std::vector<std::string> images;
	images.reserve(2); // currently just the instrument photo

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
