/*
  ==============================================================================

	Module			CustomMenuBar
	Description		Menu bar used for selecting the instruments

  ==============================================================================
*/

#include "CustomMenuBar.h"


CustomMenuBar::CustomMenuBar()
{
}

CustomMenuBar::~CustomMenuBar()
{
}


StringArray CustomMenuBar::getMenuBarNames()
{
	return {"Woodwinds", "Brass", "Strings", "Percussion"};
}


PopupMenu CustomMenuBar::getMenuForIndex(int topLevelMenuIndex, const String &menuName)
{
	PopupMenu menu;

	if (topLevelMenuIndex == 0) // Woodwinds
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
	else if (topLevelMenuIndex == 1) // Brass
	{
		menu.addItem(static_cast<int>(Brass::FrenchHorn), FrenchHornName);
		menu.addItem(static_cast<int>(Brass::Trumpet), TrumpetName);
		menu.addItem(static_cast<int>(Brass::TenorTrombone), TenorTromboneName);
		menu.addItem(static_cast<int>(Brass::BassTrombone), BassTromboneName);
		menu.addItem(static_cast<int>(Brass::Cimbasso), CimbassoName);
		menu.addItem(static_cast<int>(Brass::Tuba), TubaName);
	}
	else if (topLevelMenuIndex == 2) // Strings
	{
		menu.addItem(static_cast<int>(Strings::Violin), ViolinName);
		menu.addItem(static_cast<int>(Strings::Viola), ViolaName);
		menu.addItem(static_cast<int>(Strings::Violoncello), VioloncelloName);
		menu.addItem(static_cast<int>(Strings::DoubleBass), DoubleBassName);
	}
	else if (topLevelMenuIndex == 3) // Percussion
	{
		menu.addItem(static_cast<int>(Percussion::Celeste), CelesteName);
		menu.addItem(static_cast<int>(Percussion::Harp), HarpName);
		menu.addItem(static_cast<int>(Percussion::Timpani), TimpaniName);
		menu.addItem(static_cast<int>(Percussion::Marimba), MarimbaName);
	}

	return menu;
}


void CustomMenuBar::menuItemSelected(int menuItemID, int topLevelMenuIndex)
{
	int key = (topLevelMenuIndex + 1) * 100 + menuItemID;
	LOG_INFO("Selected instrument with key {}", key);

	if (mInstrumentSelectedCallback)
	{
		mInstrumentSelectedCallback(key);
	}
}


void CustomMenuBar::setInstrumentSelectedCallback(InstrumentSelectedCallback callback)
{
	mInstrumentSelectedCallback = callback;
}
