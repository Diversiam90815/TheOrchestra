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


class InstrumentController
{
public:
	InstrumentController();
	~InstrumentController();

	/*
	 @brief                 Returns the InstrumentInfo object of an instrument identified by a key
	 @param                 [IN] key -> key of the instrument (see 'getInstrumentKey()')
	 @return                InstrumentInfo object holding various information of the instrument
	*/
	InstrumentInfo getInstrument(int key);


	bool		   loadFromJSON();

private:
	/*
	 @brief                 Adding an instrument to the instruments map
	 @param                 [IN] family -> enum: Family::Woodwinds (1), Family::Brass (2), Family::Strings (3), Family::Percussion (4)
	 @param                 [IN] instrument -> enum values of the different instruments found in 'InstrumentInfo.h'
	 @param                 [IN] InstrumentInfo object holding various information of the instrument
	*/
	void						  addInstrument(Family family, int instrumentId, const InstrumentInfo &info);


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
