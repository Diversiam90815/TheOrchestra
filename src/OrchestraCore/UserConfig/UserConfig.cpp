/*
  ==============================================================================
	Module			User Config
	Description		Managing the user configuration storing settings
  ==============================================================================
*/

#include "UserConfig.h"


void UserConfig::init()
{
	loadConfigFile();
	LOG_INFO("UserConfig initialized..");
}


std::string UserConfig::getSavedSamplesFolder()
{
	return readFromConfig<std::string>(SAMPLES_FOLDER_SETTING);
}


void UserConfig::saveSamplesFolder(std::string directory)
{
	saveToConfig(SAMPLES_FOLDER_SETTING, directory);
}


bool UserConfig::loadConfigFile()
{
	try
	{
		std::string configPath = getConfigFullPath();

		if (!std::filesystem::exists(configPath))
		{
			LOG_INFO("Config file not found, creating new one: {}", configPath);
			mConfigData = json::object();
			return saveConfigFile();
		}

		std::ifstream file(configPath);

		if (!file.is_open())
		{
			LOG_ERROR("Failed to open config file: {}", configPath);
			return false;
		}

		file >> mConfigData;
		file.close();

		LOG_INFO("Config loaded from {}", configPath);
		return true;
	}
	catch (const json::exception &e)
	{
		LOG_ERROR("JSON parsing error: {}", e.what());
		mConfigData = json::object();
		return false;
	}
	catch (const std::exception &e)
	{
		LOG_ERROR("Error loading config file: {}", e.what());
		return false;
	}
}


bool UserConfig::saveConfigFile()
{
	try
	{
		std::string	  configPath = getConfigFullPath();

		std::ofstream file(configPath);

		if (!file.is_open())
		{
			LOG_ERROR("Failed to open config file for writing: {}", configPath);
			return false;
		}

		file << mConfigData.dump(4);
		file.close();

		LOG_INFO("Config saved to {}", configPath);
		return true;
	}
	catch (const json::exception &e)
	{
		LOG_ERROR("JSON serialization error: {}", e.what());
		return false;
	}
	catch (const std::exception &e)
	{
		LOG_ERROR("Error saving config file: {}", e.what());
		return false;
	}
}


std::string UserConfig::getConfigFullPath()
{
	std::filesystem::path configDir = mFileManager.getConfigFilePath();
	std::filesystem::path fullPath	= configDir / ConfigFile;
	return fullPath.string();
}
