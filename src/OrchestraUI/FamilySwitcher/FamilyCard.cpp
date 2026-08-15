/*
  ==============================================================================
	Module			FamilyCard
	Description		One family card on the family-switcher screen.
  ==============================================================================
*/

#include "FamilyCard.h"
#include "CustomLookAndFeel.h"
#include "Theme.h"


FamilyCard::FamilyCard(Family family, const juce::String &name, const juce::String &letter) : mFamily(family), mName(name), mLetter(letter)
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
	auto	   *lf	   = dynamic_cast<CustomLookAndFeel *>(&getLookAndFeel());
	const auto &t	   = themeFor(*this);

	auto		bounds = getLocalBounds().toFloat().reduced(0.5f);

	// Background
	g.setColour(mSelected ? t.surfaceElevated : (mHover ? t.surface.brighter(0.06f) : t.surface));
	g.fillRoundedRectangle(bounds, Radius::lg);

	// Border
	g.setColour(mSelected ? t.accent : t.divider());
	g.drawRoundedRectangle(bounds, Radius::lg, mSelected ? 1.5f : 1.0f);

	auto area  = getLocalBounds().reduced(Space::xl, Space::l);

	// Badge
	auto badge = area.removeFromLeft(kBadgeSize).withSizeKeepingCentre(kBadgeSize, kBadgeSize);
	g.setColour(t.familyBadgeBackground(mFamily));
	g.fillRoundedRectangle(badge.toFloat(), Radius::lg);
	g.setColour(t.familyGlyph(mFamily));
	g.setFont(lf ? lf->getSerifFont(Type::heading) : juce::Font(Type::heading));
	g.drawText(mLetter, badge, juce::Justification::centred, false);

	area.removeFromLeft(Space::l);

	// Name + count stacked
	auto textCol = area;
	auto nameRow = textCol.removeFromTop(textCol.getHeight() / 2);

	g.setColour(t.textPrimary);
	g.setFont(lf ? lf->getSerifFont(Type::body, true) : juce::Font(Type::body));
	g.drawText(mName, nameRow, juce::Justification::bottomLeft, false);

	g.setColour(mSelected ? t.accent : t.textTertiary);
	g.setFont(lf ? lf->getSerifFont(Type::bodySmall) : juce::Font(Type::bodySmall));
	g.drawText(juce::String(mCount) + " instruments", textCol, juce::Justification::topLeft, false);
}
