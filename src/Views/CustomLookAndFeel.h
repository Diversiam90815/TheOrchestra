/*
  ==============================================================================

	Module			CustomLookAndFeel
	Description		Customizing the LookNFeel class used by the Editor

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
	void   init();

	Font   getEditorFont();

	void   drawLabel(Graphics &g, Label &label) override;

	void   drawTextEditorOutline(Graphics &g, int width, int height, TextEditor &textEditor) override;

	void   drawMenuBarBackground(Graphics &g, int width, int height, bool isMouseOverBar, MenuBarComponent &menuBar) override;

	void   drawPopupMenuItem(Graphics			  &g,
							 const Rectangle<int> &area,
							 const bool			   isSeparator,
							 const bool			   isActive,
							 const bool			   isHighlighted,
							 const bool			   isTicked,
							 const bool			   hasSubMenu,
							 const String		  &text,
							 const String		  &shortcutKeyText,
							 const Drawable		  *icon,
							 const Colour		  *textColour) override;

	Font   getPopupMenuFont() override;


	Font   headerFont		 = Font("Instrument Serif", 24.0f, Font::plain);

	Colour fontColor		 = Colour::fromRGB(238, 233, 218);
	Colour whiteFontColour	 = Colour::fromRGB(255, 255, 255);

	Colour menuBarBackground = Colour::fromRGB(44, 44, 44);	  // Menubar background colour
	Colour background		 = Colour::fromRGB(16, 14, 21);	  // Colour used for the background of the app window
	Colour buttonColor		 = Colour::fromRGB(158, 104, 61); // Colour used for the buttons in "Playing Techniques"
	Colour boxesBackground	 = background.brighter(0.02f);	  // Colours used for the background of the different UI elements

	Font   infoFont;										  // Font used for the information texts displayed
	Font   titleFont;										  // Font used for the titles
	Font   popupmenuFont;									  // Font used for the pop up menu
};
