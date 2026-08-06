/*
  ==============================================================================
	Module			TextMeasure
	Description		Text measurement and wrapped drawing.
  ==============================================================================
*/

#include "TextMeasure.h"


namespace
{
juce::TextLayout buildLayout(const juce::Font &font, const juce::String &text, int width, const juce::Colour &colour)
{
	juce::AttributedString attributed;
	attributed.setText(text);
	attributed.setFont(font);
	attributed.setColour(colour);
	attributed.setJustification(juce::Justification::topLeft);
	attributed.setWordWrap(juce::AttributedString::byWord);

	juce::TextLayout layout;
	layout.createLayout(attributed, (float)juce::jmax(1, width));

	return layout;
}
} // namespace


int TextMeasure::wrappedHeight(const juce::Font &font, const juce::String &text, int width, int maxLines)
{
	if (text.isEmpty() || width <= 0)
		return 0;

	const auto layout	 = buildLayout(font, text, width, juce::Colours::white);
	const int  height	 = (int)std::ceil(layout.getHeight());

	if (maxLines <= 0)
		return height;

	const int  lineHeight = (int)std::ceil(font.getHeight() * 1.35f);
	return juce::jmin(height, lineHeight * maxLines);
}


int TextMeasure::lineWidth(const juce::Font &font, const juce::String &text)
{
	return juce::GlyphArrangement::getStringWidthInt(font, text);
}


void TextMeasure::drawWrapped(
	juce::Graphics &g, const juce::Font &font, const juce::Colour &colour, const juce::String &text, juce::Rectangle<int> bounds, int maxLines)
{
	if (text.isEmpty() || bounds.isEmpty())
		return;

	auto layout = buildLayout(font, text, bounds.getWidth(), colour);

	if (maxLines > 0)
	{
		const int lineHeight = (int)std::ceil(font.getHeight() * 1.35f);
		bounds				 = bounds.withHeight(juce::jmin(bounds.getHeight(), lineHeight * maxLines));
	}

	juce::Graphics::ScopedSaveState clip(g);
	g.reduceClipRegion(bounds);

	layout.draw(g, bounds.toFloat());
}
