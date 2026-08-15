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

	juce::Font			getSectionTitleFont() const;

	juce::Font			getSerifFont(float height, bool semiBold = false) const;

private:
	void				init();
	void				setFont();

	void				drawLabel(juce::Graphics &g, juce::Label &label) override;

	void				drawButtonBackground(
					   juce::Graphics &g, juce::Button &button, const juce::Colour &backgroundColour, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown) override;
	void				drawButtonText(juce::Graphics &g, juce::TextButton &button, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown) override;

	// Fonts
	juce::Typeface::Ptr instrumentTypeface;

	juce::Font			instrumentNameFont;
	juce::Font			sectionTitleFont;
	juce::Font			bodyFont;

	// The palette lives in Theme.h; this is the only instance the UI resolves.
	const Theme		   &mTheme = defaultTheme();
};
