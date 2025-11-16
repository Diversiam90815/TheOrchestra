/*
  ==============================================================================
	Module			FileManager
	Description		Managing files and folders
  ==============================================================================
*/

#include "FileManager.h"


std::string FileManager::getSamplesFolder()
{
	std::filesystem::path projectDir = findAssetsFolder();

	std::filesystem::path samplesDir = projectDir / SampleFolderName;

	return samplesDir.string();
}


std::string FileManager::getInstrumentDataJSONPath()
{
	std::filesystem::path projectDir = findAssetsFolder();

	std::filesystem::path dataDir	 = projectDir / InstrumentDataFolderName / InstrumentsDataFileName;

	return dataDir.string();
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

	std::string filter = "";
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
	default: return juce::File();
	}

	// Find an image within the folder that has the name "instrument"
	auto it = std::find_if(images.begin(), images.end(), [&filter](const juce::String &imagePath) { return imagePath.containsIgnoreCase(filter); });

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


void FileManager::setAssetsFolder(const std::filesystem::path &path)
{
	if (std::filesystem::exists(path) && std::filesystem::is_directory(path))
	{
		mAssetsFolderOverride = path;
	}
}


std::filesystem::path FileManager::getProjectDirectory()
{
	std::filesystem::path cwd		 = std::filesystem::current_path();
	std::filesystem::path projectDir = cwd.parent_path().parent_path().parent_path().parent_path(); // TODO: Use built folder instead of project folder for assets
	return projectDir;
}


std::filesystem::path FileManager::getExecutableDirectory()
{
	auto exePath = juce::File::getSpecialLocation(juce::File::currentExecutableFile);
	return std::filesystem::path(exePath.getParentDirectory().getFullPathName().toStdString());
}


std::filesystem::path FileManager::findAssetsFolder()
{
	// 1. Check if assets folder was set explicitly
	if (mAssetsFolderOverride.has_value())
		return mAssetsFolderOverride.value();

	// 2. check next to executable (installed version)
	std::filesystem::path exeDir		= getExecutableDirectory();
	std::filesystem::path assetsNearExe = exeDir / AssetsFolderName;

	if (std::filesystem::exists(assetsNearExe))
		return exeDir;

	// 3. Check in parent directory (development builds)
	std::filesystem::path parentAssets = exeDir.parent_path() / AssetsFolderName;
	if (std::filesystem::exists(parentAssets))
		return exeDir.parent_path();

	// 4. Walk up the directory tree looking for Assets folder
	std::filesystem::path searchPath = exeDir;
	for (int i = 0; i < 6; ++i) // Search up to 6 levels
	{
		std::filesystem::path candidate = searchPath / AssetsFolderName;
		if (std::filesystem::exists(candidate))
			return searchPath;

		if (!searchPath.has_parent_path())
			break;

		searchPath = searchPath.parent_path();
	}

	// 5. Fallback to old behavior 
	return getProjectDirectory() / AssetsFolderName;
}


std::vector<std::string> FileManager::getInstrumentImages(const std::string &family, const std::string &instrumentName)
{
	std::filesystem::path	 projectDir = findAssetsFolder();
	std::filesystem::path	 imagesDir	= projectDir / ImageFolderName / family / instrumentName;

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
