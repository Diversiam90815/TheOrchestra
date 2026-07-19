/*
  ==============================================================================
	Module			FamilyCard
	Description		One family card on the family-switcher screen.
  ==============================================================================
*/

#include "FamilyCard.h"
#include "CustomLookAndFeel.h"


FamilyCard::FamilyCard(Family family, const juce::String &name, const juce::String &letter, juce::Colour badgeBg, juce::Colour glyphColour)
	: mFamily(family), mName(name), mLetter(letter), mBadgeBg(badgeBg), mGlyphColour(glyphColour)
{
}


void FamilyCard::setCount(int count)
{
	mCount = count;
	repaint();
}


void FamilyCard::setSelected(bool selected)
{
	if (selected != mSelected)
	{
		mSelected = selected;
		repaint();
	}
}


void FamilyCard::mouseEnter(const juce::MouseEvent &)
{
	mHover = true;
	repaint();
}


void FamilyCard::mouseExit(const juce::MouseEvent &)
{
	mHover = false;
	repaint();
}


void FamilyCard::mouseUp(const juce::MouseEvent &e)
{
	if (getLocalBounds().contains(e.getPosition()) && onClicked)
		onClicked(mFamily);
}


void FamilyCard::paint(juce::Graphics &g)
{
	auto *lf = dynamic_cast<CustomLookAndFeel *>(&getLookAndFeel());

	const juce::Colour cardBg	 = lf ? lf->getCardColour() : juce::Colour::fromRGB(27, 23, 38);
	const juce::Colour selBg	 = lf ? lf->getSelectedCardColour() : juce::Colour::fromRGB(36, 31, 51);
	const juce::Colour gold		 = lf ? lf->getAccentColour() : juce::Colour::fromRGB(196, 148, 58);
	const juce::Colour primary	 = lf ? lf->getTextPrimaryColour() : juce::Colour::fromRGB(238, 233, 218);
	const juce::Colour muted	 = lf ? lf->getTextTertiaryColour() : juce::Colour::fromRGB(107, 103, 96);
	const juce::Colour border	 = lf ? lf->getDividerColour(0.14f) : gold.withAlpha(0.14f);

	auto bounds = getLocalBounds().toFloat().reduced(0.5f);

	// Background
	g.setColour(mSelected ? selBg : (mHover ? cardBg.brighter(0.06f) : cardBg));
	g.fillRoundedRectangle(bounds, 8.0f);

	// Border
	g.setColour(mSelected ? gold : border);
	g.drawRoundedRectangle(bounds, 8.0f, mSelected ? 1.5f : 1.0f);

	auto area = getLocalBounds().reduced(18, 16);

	// Badge
	auto badge = area.removeFromLeft(40);
	badge = badge.withSizeKeepingCentre(40, 40);
	g.setColour(mBadgeBg);
	g.fillRoundedRectangle(badge.toFloat(), 6.0f);
	g.setColour(mGlyphColour);
	g.setFont(lf ? lf->getSerifFont(17.0f) : juce::Font(17.0f));
	g.drawText(mLetter, badge, juce::Justification::centred, false);

	area.removeFromLeft(14);

	// Name + count stacked
	auto textCol = area;
	auto nameRow = textCol.removeFromTop(textCol.getHeight() / 2);

	g.setColour(primary);
	g.setFont(lf ? lf->getSerifFont(13.0f, true) : juce::Font(13.0f));
	g.drawText(mName, nameRow, juce::Justification::bottomLeft, false);

	g.setColour(mSelected ? gold : muted);
	g.setFont(lf ? lf->getSerifFont(11.0f) : juce::Font(11.0f));
	g.drawText(juce::String(mCount) + " instruments", textCol, juce::Justification::topLeft, false);
}
