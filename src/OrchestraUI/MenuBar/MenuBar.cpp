/*
  ==============================================================================
	Module			MenuBar
	Description		Menu bar used for selecting the instruments
  ==============================================================================
*/

#include "MenuBar.h"


juce::StringArray MenuBar::getMenuBarNames()
{
	return {"Woodwinds", "Brass", "Strings", "Percussion", "Settings"};
}


juce::PopupMenu MenuBar::getMenuForIndex(int topLevelMenuIndex, const juce::String &menuName)
{
	juce::PopupMenu menu;

	if (topLevelMenuIndex == MenuIndices::WoodwindsMenu)
	{
		menu.addItem(static_cast<int>(Woodwinds::Piccolo), PiccoloName);
		menu.addItem(static_cast<int>(Woodwinds::Flute), FluteName);
		menu.addItem(static_cast<int>(Woodwinds::Oboe), OboeName);
		menu.addItem(static_cast<int>(Woodwinds::CorAnglais), CorAnglaisName);
		menu.addItem(static_cast<int>(Woodwinds::Clarinet), ClarinetName);
		menu.addItem(static_cast<int>(Woodwinds::BassClarinet), BassClarinetName);
		menu.addItem(static_cast<int>(Woodwinds::Bassoon), BassoonName);
		menu.addItem(static_cast<int>(Woodwinds::Contrabassoon), ContrabassoonName);
	}
	else if (topLevelMenuIndex == MenuIndices::BrassMenu)
	{
		menu.addItem(static_cast<int>(Brass::FrenchHorn), FrenchHornName);
		menu.addItem(static_cast<int>(Brass::Trumpet), TrumpetName);
		menu.addItem(static_cast<int>(Brass::TenorTrombone), TenorTromboneName);
		menu.addItem(static_cast<int>(Brass::BassTrombone), BassTromboneName);
		menu.addItem(static_cast<int>(Brass::Cimbasso), CimbassoName);
		menu.addItem(static_cast<int>(Brass::Tuba), TubaName);
	}
	else if (topLevelMenuIndex == MenuIndices::StringsMenu)
	{
		menu.addItem(static_cast<int>(Strings::Violin), ViolinName);
		menu.addItem(static_cast<int>(Strings::Viola), ViolaName);
		menu.addItem(static_cast<int>(Strings::Violoncello), VioloncelloName);
		menu.addItem(static_cast<int>(Strings::DoubleBass), DoubleBassName);
	}
	else if (topLevelMenuIndex == MenuIndices::PercussionMenu)
	{
		menu.addItem(static_cast<int>(Percussion::Celeste), CelesteName);
		menu.addItem(static_cast<int>(Percussion::Harp), HarpName);
		menu.addItem(static_cast<int>(Percussion::Timpani), TimpaniName);
		menu.addItem(static_cast<int>(Percussion::Marimba), MarimbaName);
	}
	else if (topLevelMenuIndex == MenuIndices::SettingsMenu)
	{
		menu.addItem(static_cast<int>(SettingsMenuItems::SetSamplesFolder), "Set samples folder..");
	}

	return menu;
}


void MenuBar::menuItemSelected(int menuItemID, int topLevelMenuIndex)
{
	// Handle settings menu
	if (topLevelMenuIndex == MenuIndices::SettingsMenu)
	{
		if (menuItemID == static_cast<int>(SettingsMenuItems::SetSamplesFolder))
		{
			showSampleFolderChooser();
		}
		return;
	}

	// Handle instrument selection
	InstrumentID key = (topLevelMenuIndex + 1) * 100 + menuItemID;
	LOG_INFO("Selected instrument with key {}", key);

	if (mInstrumentSelectedCallback)
	{
		mInstrumentSelectedCallback(key);
	}
}


void MenuBar::setInstrumentSelectedCallback(InstrumentSelectedCallback callback)
{
	mInstrumentSelectedCallback = callback;
}


void MenuBar::setSampleFolderChangedCallback(SampleFolderChangedCallback callback)
{
	mSamplesFolderChangedCallback = callback;
}


void MenuBar::showSampleFolderChooser()
{
	auto chooser = std::make_shared<juce::FileChooser>("Select Samples Folder", juce::File::getSpecialLocation(juce::File::userDocumentsDirectory), "", true);

	auto flags	 = juce::FileBrowserComponent::openMode | juce::FileBrowserComponent::canSelectDirectories;

	chooser->launchAsync(flags,
						 [this, chooser](const juce::FileChooser &fc)
						 {
							 auto result = fc.getResult();

							 if (result.isDirectory())
							 {
								 LOG_INFO("Samples folder set to: {}", result.getFullPathName().toStdString());

								 if (mSamplesFolderChangedCallback)
									 mSamplesFolderChangedCallback(result);
							 }
						 });
}
