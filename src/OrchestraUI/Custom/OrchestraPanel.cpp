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
	auto	   *lnf	   = dynamic_cast<CustomLookAndFeel *>(&getLookAndFeel());
	const auto &t	   = themeFor(*this);

	auto		bounds = getLocalBounds().toFloat();

	g.setColour(t.surface);
	g.fillRoundedRectangle(bounds, Radius::xl);

	if (mTitle.isNotEmpty())
	{
		auto titleArea = getLocalBounds().reduced(kPadding, 0).withY(kPadding).withHeight(kTitleHeight);

		g.setColour(t.textTertiary);
		g.setFont(lnf ? lnf->getSectionTitleFont() : juce::Font(Type::label));
		g.drawText(mTitle.toUpperCase(), titleArea, juce::Justification::centredLeft, false);
	}
}


int OrchestraPanel::getChromeHeight() const
{
	return kPadding * 2 + (mTitle.isNotEmpty() ? kTitleHeight + kTitleGap : 0);
}


juce::Rectangle<int> OrchestraPanel::getContentArea() const
{
	auto area = getLocalBounds().reduced(kPadding);

	if (mTitle.isNotEmpty())
		area.removeFromTop(kTitleHeight + kTitleGap);

	return area;
}
