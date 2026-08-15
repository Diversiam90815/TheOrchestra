/*
  ==============================================================================
	Module			TextMeasure
	Description		Text measurement and wrapped drawing
  ==============================================================================
*/

#pragma once

#include "JuceIncludes.h"


namespace TextMeasure
{

int	 wrappedHeight(const juce::Font &font, const juce::String &text, int width, int maxLines = 0);

int	 lineWidth(const juce::Font &font, const juce::String &text);

void drawWrapped(juce::Graphics &g, const juce::Font &font, const juce::Colour &colour, const juce::String &text, juce::Rectangle<int> bounds, int maxLines = 0);

} // namespace TextMeasure
