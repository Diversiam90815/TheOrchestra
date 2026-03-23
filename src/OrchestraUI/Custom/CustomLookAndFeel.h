/*
  ==============================================================================
	Module			CustomLookAndFeel
	Description		Customizing the LookNFeel class used by the Editor
  ==============================================================================
*/

#pragma once

#include "JuceIncludes.h"
#include <TextFontData>


class CustomLookAndFeel : public juce::LookAndFeel_V4
{
public:
	CustomLookAndFeel();
	~CustomLookAndFeel() = default;

	// Legacy getter for CustomComponent backward compat
	juce::Colour			  getBoxBackgroundColour() const { return surface; }

	// Color getters
	juce::Colour			  getBackgroundColour() const { return background; }
	juce::Colour			  getSurfaceColour() const { return surface; }
	juce::Colour			  getSurfaceElevatedColour() const { return surfaceElevated; }
	juce::Colour			  getAccentColour() const { return accentGold; }
	juce::Colour			  getTextPrimaryColour() const { return textPrimary; }
	juce::Colour			  getTextSecondaryColour() const { return textSecondary; }
	juce::Colour			  getTextTertiaryColour() const { return textTertiary; }
	juce::Colour			  getHeaderBarColour() const { return headerBar; }
	juce::Colour			  getActiveTabColour() const { return accentGold; }
	juce::Colour			  getInactiveTabColour() const { return tabInactive; }
	juce::Colour			  getSidebarSelectedColour() const { return sidebarSelected; }
	juce::Colour			  getSidebarHoverColour() const { return sidebarHover; }

	float					  getCornerRadius() const;
	juce::Font				  getTextEditorFont();
	juce::Font				  getSectionTitleFont();
	juce::Font				  getBodyFont();
	juce::Font				  getSmallFont();
	juce::Font				  getInstrumentNameFont();
	juce::Typeface::Ptr		  getInstrumentTypeface() const { return instrumentTypeface; }
	std::vector<juce::Colour> getQualityColours();
	std::vector<juce::Colour> getQualityColoursBase();

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

	void			 drawTooltip(juce::Graphics &, const juce::String &text, int width, int height) override;
	juce::TextLayout layoutTooltipText(const juce::String &text) const noexcept;

	void			 drawTextEditorOutline(juce::Graphics &g, int width, int height, juce::TextEditor &textEditor) override;
	void			 fillTextEditorBackground(juce::Graphics &g, int width, int height, juce::TextEditor &textEditor) override;

	// Fonts
	juce::Typeface::Ptr instrumentTypeface;

	juce::Font			instrumentNameFont;
	juce::Font			sectionTitleFont;
	juce::Font			bodyFont;
	juce::Font			smallFont;
	juce::Font			textEditorFont;
	juce::Font			tooltipFont;

	// ==============================
	// Color Palette (redesigned)
	// ==============================

	// Backgrounds
	const juce::Colour	background		 = juce::Colour::fromRGB(18, 16, 26);	 // #12101A - Main background
	const juce::Colour	surface			 = juce::Colour::fromRGB(30, 27, 42);	 // #1E1B2A - Panel backgrounds
	const juce::Colour	surfaceElevated	 = juce::Colour::fromRGB(40, 36, 64);	 // #282440 - Cards, hover states
	const juce::Colour	headerBar		 = juce::Colour::fromRGB(24, 21, 32);	 // #181520 - Header bar

	// Accent
	const juce::Colour	accentGold		 = juce::Colour::fromRGB(196, 148, 58);	 // #C4943A - Primary accent
	const juce::Colour	accentGoldDim	 = juce::Colour::fromRGB(138, 104, 40);	 // #8A6828 - Dimmed accent

	// Text
	const juce::Colour	textPrimary		 = juce::Colour::fromRGB(238, 233, 218);  // #EEE9DA - Primary text
	const juce::Colour	textSecondary	 = juce::Colour::fromRGB(158, 154, 142);  // #9E9A8E - Secondary text
	const juce::Colour	textTertiary	 = juce::Colour::fromRGB(107, 103, 96);	  // #6B6760 - Tertiary text

	// Interactive
	const juce::Colour	tabInactive		 = juce::Colour::fromRGB(58, 54, 80);	 // #3A3650
	const juce::Colour	sidebarHover	 = juce::Colour::fromRGB(35, 32, 64);	 // #232040
	const juce::Colour	sidebarSelected	 = juce::Colour::fromRGB(42, 36, 69);	 // #2A2445

	// Register / Quality colors (softened)
	const juce::Colour	firstQualityColour	= juce::Colour::fromRGB(42, 75, 140);	// #2A4B8C - Blue
	const juce::Colour	secondQualityColour = juce::Colour::fromRGB(176, 120, 24);	// #B07818 - Gold
	const juce::Colour	thirdQualityColour	= juce::Colour::fromRGB(42, 107, 30);	// #2A6B1E - Green
	const juce::Colour	fourthQualityColour = juce::Colour::fromRGB(140, 42, 43);	// #8C2A2B - Red

	const float			mCornerRadius	 = 10.f;

	const int			tooltipWidth	 = 450;
	const int			tooltipHeight	 = 20;
};
