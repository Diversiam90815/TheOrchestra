/*
  ==============================================================================
	Module			CustomLookAndFeel
	Description		Customizing the LookNFeel class used by the Editor
  ==============================================================================
*/

#pragma once

#include "JuceIncludes.h"
#include "BinaryData.h"


class CustomLookAndFeel : public juce::LookAndFeel_V4
{
public:
	CustomLookAndFeel();
	~CustomLookAndFeel() = default;

	juce::Colour			  getBoxBackgroundColour() const;
	float					  getCornerRadius() const;
	juce::Font				  getTextEditorFont();
	std::vector<juce::Colour> getQualityColours();

private:
	void init();

	void setFont();

	void drawLabel(juce::Graphics &g, juce::Label &label) override;
	void drawMenuBarBackground(juce::Graphics &g, int width, int height, bool isMouseOverBar, juce::MenuBarComponent &menuBar) override;
	void drawPopupMenuItem(juce::Graphics			  &g,
						   const juce::Rectangle<int> &area,
						   const bool				   isSeparator,
						   const bool				   isActive,
						   const bool				   isHighlighted,
						   const bool				   isTicked,
						   const bool				   hasSubMenu,
						   const juce::String		  &text,
						   const juce::String		  &shortcutKeyText,
						   const juce::Drawable		  *icon,
						   const juce::Colour		  *textColour) override;
	void drawButtonBackground(
		juce::Graphics &g, juce::Button &button, const juce::Colour &backgroundColour, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown) override;

	void				drawTooltip(juce::Graphics &, const juce::String &text, int width, int height) override;
	juce::TextLayout	layoutTooltipText(const juce::String &text) const noexcept;

	void				drawTextEditorOutline(juce::Graphics &g, int width, int height, juce::TextEditor &textEditor) override;
	void				fillTextEditorBackground(juce::Graphics &g, int width, int height, juce::TextEditor &textEditor) override;

	// Fonts
	juce::Typeface::Ptr instrumentTypeface;

	juce::Font			headerFont;
	juce::Font			noteNameFonts;
	juce::Font			menuFont;
	juce::Font			infoTextFont;
	juce::Font			textEditorFont;
	juce::Font			tooltipFont;

	// Font Colours
	const juce::Colour	fontColor				= juce::Colour::fromRGB(238, 233, 218);
	const juce::Colour	whiteFontColour			= juce::Colour::fromRGB(255, 255, 255);
	const juce::Colour	tooltipFontColour		= juce::Colour::fromRGB(0, 0, 0);


	const juce::Colour	techniqueButtonColour	= juce::Colour::fromRGB(158, 104, 61);

	const juce::Colour	menuBarBackground		= juce::Colour::fromRGB(44, 44, 44);   // Menubar background colour
	const juce::Colour	background				= juce::Colour::fromRGB(16, 14, 21);   // Colour used for the background of the app window
	const juce::Colour	buttonColor				= juce::Colour::fromRGB(158, 104, 61); // Colour used for the buttons in "Playing PlayingTechniques"
	const juce::Colour	boxesBackground			= background.brighter(0.02f);		   // Colours used for the background of the different UI elements
	const juce::Colour	tooltipWindowBackground = juce::Colour::fromRGB(81, 133, 246);
	const juce::Colour	comboBoxBackground		= juce::Colour::fromRGB(17, 19, 31);

	const float			mCornerRadius			= 8;

	const int			tooltipWidth			= 450;
	const int			tooltipHeight			= 20;

	const juce::Colour	firstQualityColour		= juce::Colour::fromRGB(8, 28, 128); // Blue
	const juce::Colour	secondQualityColour		= juce::Colour::fromRGB(130, 84, 0); // Gold
	const juce::Colour	thirdQualityColour		= juce::Colour::fromRGB(24, 82, 10); // Green
	const juce::Colour	fourthQualityColour		= juce::Colour::fromRGB(84, 18, 19); // Red
};
