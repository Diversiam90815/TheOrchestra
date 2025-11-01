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


class MenuBar : public juce::MenuBarModel
{
public:
	MenuBar()  = default;
	~MenuBar() = default;

	juce::StringArray getMenuBarNames() override;
	juce::PopupMenu	  getMenuForIndex(int topLevelMenuIndex, const juce::String &menuName) override;
	void		menuItemSelected(int menuItemID, int topLevelMenuIndex) override;

	void		setInstrumentSelectedCallback(InstrumentSelectedCallback callback);

private:
	juce::MenuBarComponent	   menuBar; // Menubar instance

	InstrumentSelectedCallback mInstrumentSelectedCallback;
};
