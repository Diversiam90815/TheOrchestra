/*
  ==============================================================================
	Module			FileManager
	Description		Managing files and folders
  ==============================================================================
*/

#include "FileManager.h"


std::string FileManager::getDefaultSamplesFolderPath()
{
	const auto			  toPath = [](const juce::File &file) { return std::filesystem::path(file.getFullPathName().toStdString()); };

	fs::path shared = toPath(juce::File::getSpecialLocation(juce::File::commonApplicationDataDirectory)) / Files::ProjectName / AssetsFolderName / SampleFolderName;

	if (std::filesystem::is_directory(shared))
		return shared.string();

	fs::path perUser = toPath(juce::File::getSpecialLocation(juce::File::userApplicationDataDirectory)) / Files::ProjectName / AssetsFolderName / SampleFolderName;

	return perUser.string();
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


fs::path FileManager::getProjectsAppDataPath()
{
	const auto appDataDir = juce::File::getSpecialLocation(juce::File::userApplicationDataDirectory);

	if (appDataDir == juce::File())
	{
		throw std::runtime_error("Could not resolve the user application data directory");
	}

	fs::path	appDataPath(appDataDir.getFullPathName().toStdString());

	// Test binaries get their own AppData namespace so running them never reads or overwrites a real user's saved settings.
	auto		exeName			   = juce::File::getSpecialLocation(juce::File::currentExecutableFile).getFileNameWithoutExtension();
	const char *projectName		   = exeName.containsIgnoreCase("Tests") ? Files::TestProjectName : Files::ProjectName;

	fs::path	projectAppDataPath = appDataPath / projectName;

	if (!fs::exists(projectAppDataPath))
		fs::create_directories(projectAppDataPath);

	return projectAppDataPath;
}


fs::path FileManager::getLoggingPath()
{
	fs::path projectAppDataPath = getProjectsAppDataPath();

	fs::path logFolder			= projectAppDataPath / Files::LogFolderName;

	if (!fs::exists(logFolder))
		fs::create_directories(logFolder);

	return logFolder;
}


fs::path FileManager::getExecutableDirectory()
{
	auto exePath = juce::File::getSpecialLocation(juce::File::currentExecutableFile);
	return fs::path(exePath.getParentDirectory().getFullPathName().toStdString());
}


std::vector<fs::path> FileManager::getAssetsFolderCandidates()
{
	const auto			  toPath = [](const juce::File &file) { return fs::path(file.getFullPathName().toStdString()); };

	std::vector<fs::path> candidates;
	candidates.reserve(3);

	// The standalone app and the test runner: copied next to the binary at build time.
	candidates.push_back(getExecutableDirectory() / AssetsFolderName);

	// An installed plugin: shared first, then per-user.
	candidates.push_back(toPath(juce::File::getSpecialLocation(juce::File::commonApplicationDataDirectory)) / Files::ProjectName / AssetsFolderName);
	candidates.push_back(toPath(juce::File::getSpecialLocation(juce::File::userApplicationDataDirectory)) / Files::ProjectName / AssetsFolderName);

	return candidates;
}


fs::path FileManager::getAssetsFolder()
{
	for (const auto &candidate : getAssetsFolderCandidates())
	{
		std::error_code ec;

		if (std::filesystem::is_directory(candidate, ec))
			return candidate;
	}

	return getExecutableDirectory() / AssetsFolderName;
}


fs::path FileManager::getConfigFilePath()
{
	fs::path projectAppDataPath = getProjectsAppDataPath();

	fs::path configFolder		= projectAppDataPath / Files::ConfigFolderName;

	if (!fs::exists(configFolder))
		fs::create_directories(configFolder);

	return configFolder;
}


std::vector<std::string> FileManager::getInstrumentImages(const std::string &family, const std::string &instrumentName)
{
	fs::path				 projectDir = getAssetsFolder();
	fs::path				 imagesDir	= projectDir / ImageFolderName / family / instrumentName;

	std::vector<std::string> images;
	images.reserve(2); // currently just the instrument photo

	if (fs::exists(imagesDir) && fs::is_directory(imagesDir))
	{
		for (const auto &entry : fs::directory_iterator(imagesDir))
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


std::vector<fs::path> FileManager::findChildDirectories(const fs::path &directory)
{
	std::vector<fs::path> result;

	std::error_code		  ec;

	if (!fs::exists(directory, ec) || !fs::is_directory(directory, ec))
		return result;

	for (const auto &entry : fs::directory_iterator(directory, ec))
		result.push_back(entry.path());

	return result;
}


std::vector<fs::path> FileManager::findChildFiles(const fs::path &directory)
{
	std::vector<fs::path> result;

	std::error_code		  ec;
	if (!fs::exists(directory, ec) || !fs::is_directory(directory, ec))
		return result;

	for (const auto &entry : fs::directory_iterator(directory, ec))
	{
		if (entry.is_regular_file())
			result.push_back(entry.path());
	}

	return result;
}


std::vector<std::string> FileManager::splitTokens(const std::string &text, char delimiter)
{
	std::vector<std::string> tokens;
	std::string				 current;

	for (char c : text)
	{
		if (c == delimiter)
		{
			tokens.push_back(current);
			current.clear();
		}
		else
		{
			current += c;
		}
	}
	tokens.push_back(current);

	return tokens;
}
