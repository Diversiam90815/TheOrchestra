/*
  ==============================================================================

	Module			InstrumentController
	Description		Managing instrument data for the whole orchestra

  ==============================================================================
*/

#pragma once

#include <map>
#include <fstream>

#include "JuceIncludes.h"
#include "InstrumentInfo.h"
#include "FileManager.h"
#include "Logging.h"

using json = nlohmann::json;


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

	std::map<InstrumentID, InstrumentInfo> instruments; // Mapping the instrument's key to the corresponding InstrumentInfo object

	FileManager							   mFileManager;
};
