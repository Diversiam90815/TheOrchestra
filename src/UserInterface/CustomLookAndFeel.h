/*
  ==============================================================================

	CustomLookAndFeel.h
	Created: 19 Apr 2024 9:12:16am
	Author:  Jens.Langenberg

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>


// Enum to differentiate each label use
enum labelType
{
	title = 1,
	range,
	qualities,
	playingtechnique,
	usefulinformation,
	famousworks,
	transposition
};


class CustomLookAndFeel : public LookAndFeel_V4
{
public:
	CustomLookAndFeel();
	~CustomLookAndFeel();

private:
    
	void init();

	Font getEditorFont();

	void drawLabel(Graphics &g, Label &label) override;

	void drawTextEditorOutline(Graphics &g, int width, int height, TextEditor &textEditor) override;

	void drawMenuBarBackground(Graphics &g, int width, int height, bool isMouseOverBar, MenuBarComponent &menuBar) override;

	void drawPopupMenuItem(Graphics				&g,
						   const Rectangle<int> &area,
						   const bool			 isSeparator,
						   const bool			 isActive,
						   const bool			 isHighlighted,
						   const bool			 isTicked,
						   const bool			 hasSubMenu,
						   const String			&text,
						   const String			&shortcutKeyText,
						   const Drawable		*icon,
						   const Colour			*textColour) override;

	Font getPopupMenuFont() override;


	Font infoFont;                  // Font used for the information texts displayed
	Font titleFont;                 // Font used for the titles
	Font popupmenuFont;             // Font used for the pop up menu
};
