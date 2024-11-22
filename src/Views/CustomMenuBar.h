/*
  ==============================================================================

	Module			CustomMenuBar
	Description		Menu bar used for selecting the instruments

  ==============================================================================
*/

#pragma once
#include "JuceHeader.h"
#include "Parameters.h"


class CustomMenuBar : public MenuBarModel
{
public:
	CustomMenuBar();
	~CustomMenuBar();


	StringArray getMenuBarNames() override;

	PopupMenu	getMenuForIndex(int topLevelMenuIndex, const String &menuName) override;

	void		menuItemSelected(int menuItemID, int topLevelMenuIndex) override;

private:
	MenuBarComponent menuBar; // Menubar instance
};
