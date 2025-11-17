/*
  ==============================================================================
	Module			User Config
	Description		Managing the user configuration storing settings
  ==============================================================================
*/

#pragma once

#include <string>
#include <fstream>

#include "FileManager.h"
#include "nlohmann/json.hpp"
#include "Logging.h"

using json = nlohmann::json;


class UserConfig
{
public:
	UserConfig()  = default;
	~UserConfig() = default;

	void		init();

	std::string getSavedSamplesFolder();
	void		saveSamplesFolder(std::string directory);

private:
	template <typename T>
	void saveToConfig(std::string key, T value);

	template <typename T>
	T				  readFromConfig(std::string key);

	bool			  loadConfigFile();
	bool			  saveConfigFile();
	std::string		  getConfigFullPath();


	const std::string SAMPLES_FOLDER_SETTING = "SAMPLER_FOLDER";

	FileManager		  mFileManager;

	json			  mConfigData;
};


template <typename T>
inline void UserConfig::saveToConfig(std::string key, T value)
{
	try
	{
		mConfigData[key] = value;

		if (!saveConfigFile())
		{
			LOG_ERROR("Failed to save config for key: {}", key);
		}
	}
	catch (const json::exception &e)
	{
		LOG_ERROR("JSON error saving key '{}': {}", key, e.what());
	}
	catch (const std::exception &e)
	{
		LOG_ERROR("Error saving config key '{}': {}", key, e.what());
	}
}


template <typename T>
inline T UserConfig::readFromConfig(std::string key)
{
	try
	{
		if (!mConfigData.contains(key))
		{
			LOG_WARNING("Config key '{}' not found, returning default value", key);
			return {};
		}

		return mConfigData[key].get<T>();
	}
	catch (const json::exception &e)
	{
		LOG_ERROR("JSON error reading key '{}': {}", key, e.what());
		return T();
	}
	catch (const std::exception &e)
	{
		LOG_ERROR("Error reading config key '{}': {}", key, e.what());
		return T();
	}
}
