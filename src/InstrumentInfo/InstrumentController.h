/*
  ==============================================================================

	Module			InstrumentController
	Description		Managing instrument data for the whole orchestra

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include <map>
#include "InstrumentInfo.h"
#include "Helper.h"
#include "FileManager.h"
#include "Logging.h"


class InstrumentController
{
public:
	InstrumentController();
	~InstrumentController();

	void init();

	InstrumentInfo getInstrument(int key);

	bool		   loadFromJSON();


private:
	void						  addInstrument(const InstrumentInfo &info);

	StringArray					  readPlayingTechniquesFromJSON(DynamicObject *obj);

	StringArray					  readQualitiesFromJSON(DynamicObject *obj);

	String						  readNameFromJSON(DynamicObject *obj);

	String						  readRangeFromJSON(DynamicObject *obj);

	String						  readTranspositionFromJSON(DynamicObject *obj);

	StringArray					  readInformationFromJSON(DynamicObject *obj);

	StringArray					  readFamousWorksFromJSON(DynamicObject *obj);


	std::map<int, InstrumentInfo> instruments; // Mapping the instrument's key to the corresponding InstrumentInfo object

	FileManager					  mFileManager;
};
