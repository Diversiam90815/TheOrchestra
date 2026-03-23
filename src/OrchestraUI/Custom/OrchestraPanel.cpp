/*
  ==============================================================================
	Module			OrchestraPanel
	Description		Base class for all UI panels.
  ==============================================================================
*/

#include "OrchestraPanel.h"
#include "CustomLookAndFeel.h"


OrchestraPanel::OrchestraPanel(const juce::String &title) : mTitle(title)
{
}


void OrchestraPanel::paint(juce::Graphics &g)
{
	auto bounds = getLocalBounds().toFloat();

	// Draw rounded rectangle background
	juce::Path path;
	path.addRoundedRectangle(bounds, kCornerRadius);

	auto *lnf = dynamic_cast<CustomLookAndFeel *>(&getLookAndFeel());
	if (lnf)
		g.setColour(lnf->getSurfaceColour());
	else
		g.setColour(juce::Colour(30, 27, 42));

	g.fillPath(path);

	// Draw section title if present
	if (mTitle.isNotEmpty())
	{
		auto titleArea = bounds.removeFromTop(static_cast<float>(kTitleHeight + kPadding))
							 .reduced(static_cast<float>(kPadding), 0.0f)
							 .withTrimmedTop(static_cast<float>(kPadding));

		if (lnf)
			g.setColour(lnf->getTextTertiaryColour());
		else
			g.setColour(juce::Colour(107, 103, 96));

		auto titleFont = lnf ? lnf->getSectionTitleFont()
						   : juce::Font(12.0f);
		g.setFont(titleFont);
		g.drawText(mTitle.toUpperCase(), titleArea, juce::Justification::centredLeft, false);
	}
}


juce::Rectangle<int> OrchestraPanel::getContentArea() const
{
	auto area = getLocalBounds().reduced(kPadding);

	if (mTitle.isNotEmpty())
		area.removeFromTop(kTitleHeight);

	return area;
}
