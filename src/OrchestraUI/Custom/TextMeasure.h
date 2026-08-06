/*
  ==============================================================================
	Module			TextMeasure
	Description		Text measurement and wrapped drawing.

					The instrument data is sentence-length - roles run to 83
					characters, work titles to 79, register descriptions to 209
					- so panels must measure real wrapped heights rather than
					assume a fixed row height and ellipsise the overflow.
  ==============================================================================
*/

#pragma once

#include "JuceIncludes.h"


namespace TextMeasure
{
/*
 @brief					Height needed to render text wrapped to a given width.
 @param					[IN] font to measure with.
 @param					[IN] text to measure.
 @param					[IN] width available for wrapping.
 @param					[IN] maxLines to clamp to, or 0 for unlimited.
 @return				Height in pixels, rounded up.
*/
int	 wrappedHeight(const juce::Font &font, const juce::String &text, int width, int maxLines = 0);

/*
 @brief					Width of a single line of text.
*/
int	 lineWidth(const juce::Font &font, const juce::String &text);

/*
 @brief					Draws text wrapped within bounds, top-aligned.
*/
void drawWrapped(juce::Graphics &g, const juce::Font &font, const juce::Colour &colour, const juce::String &text, juce::Rectangle<int> bounds, int maxLines = 0);
} // namespace TextMeasure
