/*
  ==============================================================================

	Module			CustomLookAndFeel
	Description		Customizing the LookNFeel class used by the Editor

  ==============================================================================
*/


#pragma once

#include "JuceIncludes.h"
#include "BinaryData.h"


class CustomLookAndFeel : public LookAndFeel_V4
{
public:
	CustomLookAndFeel();
	~CustomLookAndFeel();

	Colour				getBoxBackgroundColour() const;

	float				getCornerRadius() const;

	Font				getTextEditorFont();

	std::vector<Colour> getQualityColours();

private:
	void		  init();

	void		  setFont();

	void		  drawLabel(Graphics &g, Label &label) override;

	void		  drawMenuBarBackground(Graphics &g, int width, int height, bool isMouseOverBar, MenuBarComponent &menuBar) override;

	void		  drawPopupMenuItem(Graphics				   &g,
									const juce::Rectangle<int> &area,
									const bool					isSeparator,
									const bool					isActive,
									const bool					isHighlighted,
									const bool					isTicked,
									const bool					hasSubMenu,
									const String			   &text,
									const String			   &shortcutKeyText,
									const Drawable			   *icon,
									const Colour			   *textColour) override;


	void		  drawButtonBackground(Graphics &g, Button &button, const Colour &backgroundColour, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown) override;


	void		  drawTooltip(Graphics &, const String &text, int width, int height) override;

	TextLayout	  layoutTooltipText(const String &text) const noexcept;


	void		  drawTextEditorOutline(Graphics &g, int width, int height, TextEditor &textEditor) override;

	void		  fillTextEditorBackground(Graphics &g, int width, int height, TextEditor &textEditor) override;



	// Fonts
	Typeface::Ptr instrumentTypeface;

	Font		  headerFont;
	Font		  noteNameFonts;
	Font		  menuFont;
	Font		  infoTextFont;
	Font		  qualityTextFont;
	Font		  tooltipFont;

	// Font Colours
	const Colour  fontColor				  = Colour::fromRGB(238, 233, 218);
	const Colour  whiteFontColour		  = Colour::fromRGB(255, 255, 255);
	const Colour  tooltipFontColour		  = Colour::fromRGB(0, 0, 0);

	// Button Colours
	const Colour  techniqueButtonColour	  = Colour::fromRGB(158, 104, 61);

	// Background Colours
	const Colour  menuBarBackground		  = Colour::fromRGB(44, 44, 44);   // Menubar background colour
	const Colour  background			  = Colour::fromRGB(16, 14, 21);   // Colour used for the background of the app window
	const Colour  buttonColor			  = Colour::fromRGB(158, 104, 61); // Colour used for the buttons in "Playing Techniques"
	const Colour  boxesBackground		  = background.brighter(0.02f);	   // Colours used for the background of the different UI elements
	const Colour  tooltipWindowBackground = Colour::fromRGB(81, 133, 246);
	const Colour  comboBoxBackground	  = Colour::fromRGB(17, 19, 31);

	const float	  mCornerRadius			  = 8;

	const int	  tooltipWidth			  = 450;
	const int	  tooltipHeight			  = 20;

	const Colour  firstQualityColour	  = Colour::fromRGB(8, 28, 128); // Blue
	const Colour  secondQualityColour	  = Colour::fromRGB(130, 84, 0); // Gold
	const Colour  thirdQualityColour	  = Colour::fromRGB(24, 82, 10); // Green
	const Colour  fourthQualityColour	  = Colour::fromRGB(84, 18, 19); // Red
};
