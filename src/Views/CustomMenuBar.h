/*
  ==============================================================================

	Module			CustomMenuBar
	Description		Menu bar used for selecting the instruments

  ==============================================================================
*/

#pragma once
#include "JuceHeader.h"
#include "Parameters.h"
#include "CustomLogger.h"

using InstrumentSelectedCallback = std::function<void(int)>;


class CustomMenuBar : public MenuBarModel
{
public:
	CustomMenuBar();
	~CustomMenuBar();


	StringArray getMenuBarNames() override;

	PopupMenu	getMenuForIndex(int topLevelMenuIndex, const String &menuName) override;

	void		menuItemSelected(int menuItemID, int topLevelMenuIndex) override;

	void		setInstrumentSelectedCallback(InstrumentSelectedCallback callback);

private:
	MenuBarComponent		   menuBar; // Menubar instance

	InstrumentSelectedCallback mInstrumentSelectedCallback;
};
