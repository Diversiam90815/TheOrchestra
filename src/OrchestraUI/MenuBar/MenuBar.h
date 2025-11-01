/*
  ==============================================================================
	Module			MenuBar
	Description		Menu bar used for selecting the instruments
  ==============================================================================
*/

#pragma once

#include "JuceIncludes.h"
#include "Parameters.h"
#include "Logging.h"


using InstrumentSelectedCallback = std::function<void(InstrumentID)>;


class MenuBar : public MenuBarModel
{
public:
	MenuBar()  = default;
	~MenuBar() = default;

	StringArray getMenuBarNames() override;
	PopupMenu	getMenuForIndex(int topLevelMenuIndex, const String &menuName) override;
	void		menuItemSelected(int menuItemID, int topLevelMenuIndex) override;

	void		setInstrumentSelectedCallback(InstrumentSelectedCallback callback);

private:
	MenuBarComponent		   menuBar; // Menubar instance

	InstrumentSelectedCallback mInstrumentSelectedCallback;
};
