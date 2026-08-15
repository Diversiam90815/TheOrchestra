/*
  ==============================================================================
	Module			QualitiesPanel
	Description		The "QUALITIES" list from the Overview tab: colored swatches +
					register descriptions
  ==============================================================================
*/

#include "QualitiesPanel.h"
#include "CustomLookAndFeel.h"
#include "TextMeasure.h"


void QualitiesPanel::setInstrument(const InstrumentProfile &instrument)
{
	mDescriptions.clear();

	for (const auto &reg : instrument.getRegisters())
		mDescriptions.push_back(juce::String(reg.getDescription()));

	auto range		  = instrument.getRange();
	mHasTransposition = (range.getWrittenLowNote() != range.getSoundingLowNote()) || (range.getWrittenHighNote() != range.getSoundingHighNote());
	mPitchMode		  = PitchMode::Written;

	repaint();
}


void QualitiesPanel::setPitchMode(PitchMode mode)
{
	mPitchMode = mode;
	repaint();
}


std::vector<int> QualitiesPanel::rowHeights(int width) const
{
	std::vector<int> heights;

	auto			*lnf	   = dynamic_cast<CustomLookAndFeel *>(&getLookAndFeel());
	const auto		 font	   = lnf ? lnf->getSerifFont(Type::body) : juce::Font(Type::body);
	const int		 textWidth = juce::jmax(1, width - kTextInset);

	heights.reserve(mDescriptions.size());
	for (const auto &description : mDescriptions)
		heights.push_back(juce::jmax(kMinRowHeight, TextMeasure::wrappedHeight(font, description, textWidth)));

	return heights;
}


int QualitiesPanel::getPreferredHeight(int width) const
{
	if (mDescriptions.empty())
		return kHeaderHeight;

	int total = kHeaderHeight + Space::m;

	for (int h : rowHeights(width))
		total += h + kRowGap;

	return total - kRowGap;
}


void QualitiesPanel::paint(juce::Graphics &g)
{
	auto	   *lnf	 = dynamic_cast<CustomLookAndFeel *>(&getLookAndFeel());
	const auto &t	 = themeFor(*this);

	auto		area = getLocalBounds();

	// Header row: QUALITIES (left) + pitch-mode label (right)
	auto		header = area.removeFromTop(kHeaderHeight);

	g.setColour(t.textTertiary);
	g.setFont(lnf ? lnf->getSerifFont(Type::label, true) : juce::Font(Type::label));
	g.drawText("QUALITIES", header, juce::Justification::centredLeft, false);

	if (mHasTransposition)
	{
		g.setColour(t.accent);
		g.setFont(lnf ? lnf->getSerifFont(Type::bodySmall) : juce::Font(Type::bodySmall));
		g.drawText(mPitchMode == PitchMode::Sounding ? "Sounding Pitch" : "Written Pitch", header, juce::Justification::centredRight, false);
	}

	area.removeFromTop(Space::m);

	const auto font	   = lnf ? lnf->getSerifFont(Type::body) : juce::Font(Type::body);
	const auto heights = rowHeights(getWidth());

	for (size_t i = 0; i < mDescriptions.size(); ++i)
	{
		auto row = area.removeFromTop(heights[i]);

		// Swatch aligned to the first line of the wrapped description.
		const float swatchY = (float)row.getY() + font.getHeight() * 0.5f - kSwatch * 0.5f;
		g.setColour(t.registerSwatch((int)i));
		g.fillRoundedRectangle((float)row.getX(), swatchY, (float)kSwatch, (float)kSwatch, 2.0f);

		TextMeasure::drawWrapped(g, font, t.textSecondary, mDescriptions[i], row.withTrimmedLeft(kTextInset));

		area.removeFromTop(kRowGap);
	}
}
