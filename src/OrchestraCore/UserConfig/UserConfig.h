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


enum class SettingsType
{
	SamplesFolder = 1,
};


class UserConfig
{
public:
	UserConfig()  = default;
	~UserConfig() = default;

	void		init();

	std::string getSavedSamplesFolder();
	void		saveSamplesFolder();

private:
	template <typename T>
	void saveToConfig(std::string key, T value);

	template <typename T>
	T			   readFromConfig(std::string key);

	bool		   loadConfigFile();
	bool		   saveConfigFile();
	std::string	   getConfigFullPath();


	constexpr auto SAMPLES_FOLDER_SETTING = "SAMPLER_FOLDER";

	FileManager	   mFileManager;

	json		   mConfigData;
};


template <typename T>
inline void UserConfig::saveToConfig(std::string key, T value)
{
}


template <typename T>
inline T UserConfig::readFromConfig(std::string key)
{
	return T();
}
