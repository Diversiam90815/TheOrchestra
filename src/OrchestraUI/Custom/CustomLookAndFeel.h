/*
  ==============================================================================
	Module			CustomLookAndFeel
	Description		Customizing the LookNFeel class used by the Editor
  ==============================================================================
*/

#pragma once

#include "JuceIncludes.h"
#include "Theme.h"
#include <TextFontData>


class CustomLookAndFeel : public juce::LookAndFeel_V4
{
public:
	CustomLookAndFeel();
	~CustomLookAndFeel() = default;

	const Theme		   &getTheme() const { return mTheme; }

	float				getCornerRadius() const;
	juce::Font			getTextEditorFont();
	juce::Font			getSectionTitleFont();
	juce::Font			getBodyFont();
	juce::Font			getSmallFont();
	juce::Font			getInstrumentNameFont();

	juce::Font			getSerifFont(float height, bool semiBold = false) const;
	juce::Typeface::Ptr getInstrumentTypeface() const { return instrumentTypeface; }

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
	void				drawButtonText(juce::Graphics &g, juce::TextButton &button, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown) override;

	void				drawTooltip(juce::Graphics &, const juce::String &text, int width, int height) override;
	juce::TextLayout	layoutTooltipText(const juce::String &text) const noexcept;

	void				drawTextEditorOutline(juce::Graphics &g, int width, int height, juce::TextEditor &textEditor) override;
	void				fillTextEditorBackground(juce::Graphics &g, int width, int height, juce::TextEditor &textEditor) override;

	// Fonts
	juce::Typeface::Ptr instrumentTypeface;

	juce::Font			instrumentNameFont;
	juce::Font			sectionTitleFont;
	juce::Font			bodyFont;
	juce::Font			smallFont;
	juce::Font			textEditorFont;
	juce::Font			tooltipFont;

	// The palette lives in Theme.h; this is the only instance the UI resolves.
	const Theme		   &mTheme		  = defaultTheme();

	const int			tooltipWidth  = 450;
	const int			tooltipHeight = 20;
};
