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

	void			  init();

	InstrumentProfile getInstrument(InstrumentID key);


private:
	bool									  loadFromJSON();

	void									  addInstrument(const InstrumentProfile &info);

	std::map<InstrumentID, InstrumentProfile> instruments; // Mapping the instrument's key to the corresponding InstrumentProfile object

	FileManager								  mFileManager;
};
