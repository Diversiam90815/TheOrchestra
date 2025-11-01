/*
  ==============================================================================

	Module			InstrumentController
	Description		Managing instrument data for the whole orchestra

  ==============================================================================
*/

#pragma once

#include "JuceIncludes.h"
#include <map>
#include "InstrumentInfo.h"
#include "Helper.h"
#include "FileManager.h"
#include "Logging.h"


class InstrumentController
{
public:
	InstrumentController()	= default;
	~InstrumentController() = default;

	void		   init();

	InstrumentInfo getInstrument(InstrumentID key);

	bool		   loadFromJSON();


private:
	void								   addInstrument(const InstrumentInfo &info);

	Techniques							   readPlayingTechniquesFromJSON(juce::DynamicObject *obj);
	Qualities							   readQualitiesFromJSON(juce::DynamicObject *obj);
	std::string							   readNameFromJSON(juce::DynamicObject *obj);
	Range								   readRangeFromJSON(juce::DynamicObject *obj);
	bool								   readIsRhythmicPercussionFromJSON(juce::DynamicObject *obj);
	Roles								   readInformationFromJSON(juce::DynamicObject *obj);
	FamousWorks							   readFamousWorksFromJSON(juce::DynamicObject *obj);

	std::map<InstrumentID, InstrumentInfo> instruments; // Mapping the instrument's key to the corresponding InstrumentInfo object

	FileManager							   mFileManager;
};
