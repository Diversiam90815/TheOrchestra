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


Techniques InstrumentController::readPlayingTechniquesFromJSON(juce::DynamicObject *obj)
{
	Techniques playingTechniques;
	if (obj->hasProperty("playingTechniques"))
	{
		juce::var techniquesVar = obj->getProperty("playingTechniques");
		if (techniquesVar.isArray())
		{
			for (int i = 0; i < techniquesVar.size(); ++i)
			{
				juce::var techniqueVar = techniquesVar[i];
				if (techniqueVar.isString())
					playingTechniques.push_back(PlayingTechnique(techniquesVar.toString().toStdString()));
			}
		}
	}
	return playingTechniques;
}


Qualities InstrumentController::readQualitiesFromJSON(juce::DynamicObject *obj)
{
	juce::StringArray qualities;

	if (obj->hasProperty("qualities"))
	{
		juce::var qualitiesVar = obj->getProperty("qualities");
		if (qualitiesVar.isArray())
		{
			for (int q = 0; q < qualitiesVar.size(); ++q)
			{
				juce::var qualityVar = qualitiesVar[q];
				if (qualityVar.isString())
					qualities.add(qualityVar.toString());
			}
		}
	}
	return qualities;
}


std::string InstrumentController::readNameFromJSON(juce::DynamicObject *obj)
{
	juce::String name = obj->getProperty("name").toString();
	return name;
}


Range InstrumentController::readRangeFromJSON(juce::DynamicObject *obj)
{
	juce::String range		   = obj->getProperty("range").toString();
	juce::String range		   = obj->getProperty("displayedRange").toString();
	juce::String transposition = obj->getProperty("transposition").toString();
	return range;
}


bool InstrumentController::readIsRhythmicPercussionFromJSON(juce::DynamicObject *obj)
{
	bool isRhythmicPercussion = false;
	if (obj->hasProperty("isRhythmicPercussion"))
	{
		juce::var rhythmicPercussionVar = obj->getProperty("isRhythmicPercussion");
		if (rhythmicPercussionVar.isBool())
			isRhythmicPercussion = rhythmicPercussionVar;
	}
	return isRhythmicPercussion;
}


Roles InstrumentController::readInformationFromJSON(juce::DynamicObject *obj)
{
	juce::StringArray roles;
	if (obj->hasProperty("roles"))
	{
		juce::var rolesVar = obj->getProperty("roles");
		if (rolesVar.isArray())
		{
			for (int r = 0; r < rolesVar.size(); ++r)
			{
				juce::var roleVar = rolesVar[r];
				if (roleVar.isString())
					roles.add(roleVar.toString());
			}
		}
	}
	return roles;
}


FamousWorks InstrumentController::readFamousWorksFromJSON(juce::DynamicObject *obj)
{
	StringArray famousWorks;

	if (obj->hasProperty("famousWorks"))
	{
		juce::var worksVar = obj->getProperty("famousWorks");
		if (worksVar.isArray())
		{
			for (int w = 0; w < worksVar.size(); ++w)
			{
				juce::var workVar = worksVar[w];
				if (workVar.isString())
					famousWorks.add(workVar.toString());
			}
		}
	}
	return famousWorks;
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
	std::string jsonFilePath = mFileManager.getInstrumentDataJSONPath();
	File		jsonFile(jsonFilePath);

	if (!jsonFile.existsAsFile())
		return false;

	String jsonContent = jsonFile.loadFileAsString();

	var	   parsedJSON  = JSON::parse(jsonContent);

	if (parsedJSON.isVoid())
		return false;

	if (!parsedJSON.isObject())
		return false;

	auto *rootObj = parsedJSON.getDynamicObject();

	// Iterate through each family
	for (auto it = rootObj->getProperties().begin(); it != rootObj->getProperties().end(); ++it)
	{
		String familyName = it->name.toString();
		var	   familyVar  = it->value;

		// Determine the family enum based on familyName
		Family familyEnum = familyMap[familyName];

		if (!familyVar.isObject())
			continue;

		auto	   *familyObj				= familyVar.getDynamicObject();
		StringArray familyPlayingTechniques = readPlayingTechniquesFromJSON(familyObj);

		// Retrieve instruments array
		if (!familyObj->hasProperty("instruments"))
			continue;

		var instrumentsVar = familyObj->getProperty("instruments");

		if (!instrumentsVar.isArray())
			continue;

		for (int i = 0; i < instrumentsVar.size(); ++i)
		{
			var instrumentVar = instrumentsVar[i];

			if (!instrumentVar.isObject())
				continue;

			String displayedRange{};

			auto  *instrumentObj		= instrumentVar.getDynamicObject();

			String name					= readNameFromJSON(instrumentObj);
			String range				= readRangeFromJSON(instrumentObj);

			bool   isRhythmicPercussion = readIsRhythmicPercussionFromJSON(instrumentObj);
			if (isRhythmicPercussion)
			{
				displayedRange = readDisplayedRangeFromJSON(instrumentObj);
			}

			String		transposition		 = readTranspositionFromJSON(instrumentObj);

			StringArray qualities			 = readQualitiesFromJSON(instrumentObj);
			StringArray information			 = readInformationFromJSON(instrumentObj);
			StringArray famousWorks			 = readFamousWorksFromJSON(instrumentObj);

			// For some instruments, the playing techniques are instrument-specific ( e.g. for the percussion section)
			// So if there are instrument specific techniques available, we override them here
			StringArray instrumentTechniques = readPlayingTechniquesFromJSON(instrumentObj);

			if (instrumentTechniques.isEmpty())
			{
				instrumentTechniques = familyPlayingTechniques;
			}

			int			   instrumentID = instrumentMap[name];

			int			   key			= getInstrumentKey(familyEnum, instrumentID);

			// Create InstrumentInfo object
			InstrumentInfo info(name, range, qualities, information, famousWorks, transposition, instrumentTechniques, key, isRhythmicPercussion, displayedRange);

			// Add instrument to the map
			addInstrument(info);
		}
	}

	return true;
}
