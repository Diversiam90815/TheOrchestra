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


void InstrumentController::addInstrument(const InstrumentProfile &info)
{
	InstrumentID key = info.getKey();
	instruments[key] = info;
	LOG_INFO("Instrument {} loaded!", info.getName().c_str());
}


InstrumentProfile InstrumentController::getInstrument(InstrumentID key)
{
	auto it = instruments.find(key);

	if (it != instruments.end())
		return it->second;

	return InstrumentProfile();
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
			Family			  familyEnum = familyMap[familyName];

			// Read family-level playing techniques
			PlayingTechniques familyTechniques;
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

				InstrumentRange	  range				   = InstrumentRange(instrumentRange, displayedRange, transposition);

				bool			  isRhythmicPercussion = instrumentJson.value("isRhythmicPercussion", false);

				// Parse qualities
				RegisterQualities qualities;
				if (instrumentJson.contains("qualities"))
				{
					for (const auto &qualityStr : instrumentJson["qualities"])
					{
						qualities.push_back(RegisterQuality(qualityStr.get<std::string>()));
					}
				}

				// Parse roles
				OrchestrationRoles roles;
				if (instrumentJson.contains("roles"))
				{
					for (const auto &roleStr : instrumentJson["roles"])
					{
						roles.push_back(OrchestrationRole(roleStr.get<std::string>()));
					}
				}

				// Parse SignatureWorks
				SignatureWorks famousWorks;
				if (instrumentJson.contains("famousWorks"))
				{
					for (const auto &workJson : instrumentJson["famousWorks"])
					{
						famousWorks.push_back(SignatureWork(workJson.get<std::string>())); // current format is just a string
					}
				}

				// Parse playing techniques (instrument-specific or family-level)
				PlayingTechniques techniques;
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
				InstrumentProfile info(name, key, range, qualities, roles, famousWorks, techniques, isRhythmicPercussion);

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
