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
	InstrumentID key = info.getInstrumentID();
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

		// Skip metadata section
		if (!j.contains("families"))
		{
			LOG_ERROR("JSON file missing 'families' section");
			return false;
		}

		const auto &families = j["families"];

		// Iterate through families
		for (auto &[familyName, familyData] : families.items())
		{
			Family			  familyEnum = familyMap[familyName];

			// Read family-level playing techniques
			PlayingTechniques familyTechniques;
			if (familyData.contains("techniques"))
			{
				for (const auto &t : familyData["techniques"])
				{
					familyTechniques.push_back(t.get<PlayingTechnique>());
				}
			}

			// Process instruments
			if (!familyData.contains("instruments"))
			{
				LOG_WARNING("Family {} has no instruments!", familyName);
				continue;
			}

			for (const auto &instrumentJson : familyData["instruments"])
			{
				// Parse basic fields
				std::string		  name				   = instrumentJson["name"];
				int				  instrumentID		   = instrumentMap[name];
				InstrumentID	  key				   = getInstrumentKey(familyEnum, instrumentID);

				// Parse range
				InstrumentRange	  range				   = instrumentJson["range"].get<InstrumentRange>();

				// isRhythmicPercussion, defaults to false
				bool			  isRhythmicPercussion = instrumentJson.value("isRhythmicPercussion", false);

				// Parse qualities
				RegisterQualities qualities;
				if (instrumentJson.contains("qualities"))
				{
					for (const auto &q : instrumentJson["qualities"])
					{
						qualities.push_back(q.get<RegisterQuality>());
					}
				}

				// Parse roles
				OrchestrationRoles roles;
				if (instrumentJson.contains("roles"))
				{
					for (const auto &r : instrumentJson["roles"])
					{
						roles.push_back(r.get<OrchestrationRole>());
					}
				}

				// Parse SignatureWorks
				SignatureWorks famousWorks;
				if (instrumentJson.contains("famousWorks"))
				{
					for (const auto &s : instrumentJson["famousWorks"])
					{
						famousWorks.push_back(s.get<SignatureWork>());
					}
				}

				// Parse playing techniques (instrument-specific or family-level)
				PlayingTechniques techniques;
				if (instrumentJson.contains("techniques"))
				{
					for (const auto &t : instrumentJson["techniques"])
					{
						techniques.push_back(t.get<PlayingTechnique>());
					}
				}
				else
				{
					techniques = familyTechniques; // Use family techniques
				}

				// Create and add instrument
				InstrumentProfile info(name, key, range, qualities, roles, famousWorks, techniques, isRhythmicPercussion);

				if (!info.isValid())
				{
					LOG_ERROR("Invalid instrument profile for {}!", name);
					continue;
				}

				addInstrument(info);
			}
		}

		LOG_INFO("Successfully loaded {} instruments!", instruments.size());
		return true;
	}
	catch (const json::exception &e)
	{
		LOG_ERROR("JSON parsing error: {}", e.what());
		return false;
	}
	catch (const std::exception &e)
	{
		LOG_ERROR("Error loading instruments: {}", e.what());
		return false;
	}
}
