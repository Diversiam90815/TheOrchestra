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
	const char			 *projectName		 = exeName.containsIgnoreCase("Tests") ? Files::TestProjectName : Files::ProjectName;

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

	std::filesystem::path logFolder			 = projectAppDataPath / Files::LogFolderName;

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


std::vector<std::filesystem::path> FileManager::getAssetsFolderCandidates()
{
	const auto						   toPath = [](const juce::File &file) { return std::filesystem::path(file.getFullPathName().toStdString()); };

	std::vector<std::filesystem::path> candidates;
	candidates.reserve(3);

	// The standalone app and the test runner: copied next to the binary at build time.
	candidates.push_back(getExecutableDirectory() / AssetsFolderName);

	// An installed plugin: shared first, then per-user.
	candidates.push_back(toPath(juce::File::getSpecialLocation(juce::File::commonApplicationDataDirectory)) / Files::ProjectName / AssetsFolderName);
	candidates.push_back(toPath(juce::File::getSpecialLocation(juce::File::userApplicationDataDirectory)) / Files::ProjectName / AssetsFolderName);

	return candidates;
}


std::filesystem::path FileManager::getAssetsFolder()
{
	// Resolved rather than assumed, because the same core library gets loaded two very different
	// ways. In the standalone app the assets sit next to the executable, copied there at build
	// time. In a plugin the host owns the process, and the sample pack is far too large to bundle
	// inside a .vst3 - so an installed plugin reads it from a shared location instead.
	for (const auto &candidate : getAssetsFolderCandidates())
	{
		std::error_code ec;

		if (std::filesystem::is_directory(candidate, ec))
			return candidate;
	}

	// Nothing on disk yet: fall back to the build-time layout so diagnostics point somewhere sane.
	return getExecutableDirectory() / AssetsFolderName;
}


std::filesystem::path FileManager::getConfigFilePath()
{
	std::filesystem::path projectAppDataPath = getProjectsAppDataPath();

	std::filesystem::path configFolder		 = projectAppDataPath / Files::ConfigFolderName;

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
