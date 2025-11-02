/*
  ==============================================================================
	Module			InstrumentController
	Description		Managing instrument data for the whole orchestra
  ==============================================================================
*/


#include "InstrumentController.h"
#include <cassert>


void InstrumentController::init()
{
	loadFromJSON();
	LOG_INFO("Instruments loaded from JSON");
}


void InstrumentController::addInstrument(const InstrumentInfo &info)
{
	InstrumentID key = info.getKey();
	instruments[key] = info;
	LOG_INFO("Instrument {} loaded!", info.getName().c_str());
}


InstrumentInfo InstrumentController::getInstrument(InstrumentID key)
{
	auto it = instruments.find(key);

	if (it != instruments.end())
		return it->second;

	return InstrumentInfo();
}


bool InstrumentController::loadFromJSON()
{
	std::string	  jsonFilePath = mFileManager.getInstrumentDataJSONPath();
	std::ifstream file(jsonFilePath);

	if (!file.is_open())
	{
		LOG_ERROR("Failed to open JSON file: {}", jsonFilePath);
		return false;
	}

	try
	{
		json j;
		file >> j;

		// Iterate through families
		for (auto &[familyName, familyData] : j.items())
		{
			Family	   familyEnum = familyMap[familyName];

			// Read family-level playing techniques
			Techniques familyTechniques;
			if (familyData.contains("playingTechniques"))
			{
				for (const auto &techStr : familyData["playingTechniques"])
				{
					familyTechniques.push_back(PlayingTechnique(techStr.get<std::string>()));
				}
			}

			// Process instruments
			if (!familyData.contains("instruments"))
				continue;

			for (const auto &instrumentJson : familyData["instruments"])
			{
				// Parse basic fields
				std::string	 name			 = instrumentJson["name"];
				int			 instrumentID	 = instrumentMap[name];
				InstrumentID key			 = getInstrumentKey(familyEnum, instrumentID);

				// Parse range
				std::string	 instrumentRange = instrumentJson["range"];
				std::string	 transposition	 = "";
				std::string	 displayedRange	 = "";

				if (instrumentJson.contains("transposition"))
					transposition = instrumentJson["transposition"];

				if (instrumentJson.contains("displayedRange"))
					displayedRange = instrumentJson["displayedRange"];

				Range	  range				   = Range(instrumentRange, displayedRange, transposition);

				bool	  isRhythmicPercussion = instrumentJson.value("isRhythmicPercussion", false);

				// Parse qualities
				Qualities qualities;
				if (instrumentJson.contains("qualities"))
				{
					for (const auto &qualityStr : instrumentJson["qualities"])
					{
						qualities.push_back(Quality(qualityStr.get<std::string>()));
					}
				}

				// Parse roles
				Roles roles;
				if (instrumentJson.contains("roles"))
				{
					roles = instrumentJson["roles"].get<std::vector<Role>>();
				}

				// Parse FamousWorks
				FamousWorks famousWorks;
				if (instrumentJson.contains("famousWorks"))
				{
					for (const auto &workJson : instrumentJson["famousWorks"])
					{
						famousWorks.push_back(FamousWork(workJson.get<std::string>())); // current format is just a string
					}
				}

				// Parse playing techniques (instrument-specific or family-level)
				Techniques techniques;
				if (instrumentJson.contains("playingTechniques"))
				{
					for (const auto &techStr : instrumentJson["playingTechniques"])
					{
						techniques.push_back(PlayingTechnique(techStr.get<std::string>()));
					}
				}
				else
				{
					techniques = familyTechniques; // Use family techniques
				}

				// Create and add instrument
				InstrumentInfo info(name, key, range, qualities, roles, famousWorks, techniques, isRhythmicPercussion);

				addInstrument(info);
			}
		}

		return true;
	}
	catch (const json::exception &e)
	{
		LOG_ERROR("JSON parsing error: {}", e.what());
		return false;
	}
}
