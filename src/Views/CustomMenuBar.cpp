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
		menu.addItem(Woodwinds::Piccolo, PiccoloName);
		menu.addItem(Woodwinds::Flute, FluteName);
		menu.addItem(Woodwinds::Oboe, OboeName);
		menu.addItem(Woodwinds::CorAnglais, CorAnglaisName);
		menu.addItem(Woodwinds::Clarinet, ClarinetName);
		menu.addItem(Woodwinds::BassClarinet, BassClarinetName);
		menu.addItem(Woodwinds::Bassoon, BassoonName);
		menu.addItem(Woodwinds::Contrabassoon, ContrabassoonName);
	}
	else if (topLevelMenuIndex == 1) // Brass
	{
		menu.addItem(Brass::FrenchHorn, FrenchHornName);
		menu.addItem(Brass::Trumpet, TrumpetName);
		menu.addItem(Brass::TenorTrombone, TenorTromboneName);
		menu.addItem(Brass::BassTrombone, BassTromboneName);
		menu.addItem(Brass::Cimbasso, CimbassoName);
		menu.addItem(Brass::Tuba, TubaName);
	}
	else if (topLevelMenuIndex == 2) // Strings
	{
		menu.addItem(Strings::Violin, ViolinName);
		menu.addItem(Strings::Viola, ViolaName);
		menu.addItem(Strings::Violoncello, VioloncelloName);
		menu.addItem(Strings::DoubleBass, DoubleBassName);
	}
	else if (topLevelMenuIndex == 3) // Percussion
	{
		menu.addItem(Percussion::Celeste, CelesteName);
		menu.addItem(Percussion::Harp, HarpName);
		menu.addItem(Percussion::Timpani, TimpaniName);
		menu.addItem(Percussion::Marimba, MarimbaName);
	}

	return menu;
}


void CustomMenuBar::menuItemSelected(int menuItemID, int topLevelMenuIndex)
{
	int key = (topLevelMenuIndex + 1) * 100 + menuItemID;
}
