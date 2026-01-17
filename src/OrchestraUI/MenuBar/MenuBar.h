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


using InstrumentSelectedCallback  = std::function<void(InstrumentID)>;
using SampleFolderChangedCallback = std::function<void(const juce::File &)>;


class MenuBar : public juce::MenuBarModel
{
public:
	MenuBar()  = default;
	~MenuBar() = default;

	juce::StringArray getMenuBarNames() override;
	juce::PopupMenu	  getMenuForIndex(int topLevelMenuIndex, const juce::String &menuName) override;
	void			  menuItemSelected(int menuItemID, int topLevelMenuIndex) override;

	void			  setInstrumentSelectedCallback(InstrumentSelectedCallback callback);
	void			  setSampleFolderChangedCallback(SampleFolderChangedCallback callback);

private:
	void showSampleFolderChooser();

	enum MenuIndices
	{
		WoodwindsMenu  = 0,
		BrassMenu	   = 1,
		StringsMenu	   = 2,
		PercussionMenu = 3,
		SettingsMenu   = 4
	};

	// Settings menu item IDs
	enum class SettingsMenuItems
	{
		SetSamplesFolder = 1
	};

	juce::MenuBarComponent		menuBar; // Menubar instance

	InstrumentSelectedCallback	mInstrumentSelectedCallback;
	SampleFolderChangedCallback mSamplesFolderChangedCallback;
};
