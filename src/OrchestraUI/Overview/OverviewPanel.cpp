/*
  ==============================================================================
	Module			OverviewPanel
	Description		Overview tab body: range staves & qualities.
  ==============================================================================
*/

#include "OverviewPanel.h"


OverviewPanel::OverviewPanel()
{
	addAndMakeVisible(mRanges);
	addAndMakeVisible(mQualities);
}


void OverviewPanel::setInstrument(const InstrumentProfile &instrument)
{
	mRanges.setInstrument(instrument);
	mQualities.setInstrument(instrument);
}


void OverviewPanel::setPitchMode(PitchMode mode)
{
	mRanges.setPitchMode(mode);
	mQualities.setPitchMode(mode);
}


int OverviewPanel::rangeColumnWidth(int width) const
{
	return juce::jlimit(kMinRangeWidth, kMaxRangeWidth, juce::roundToInt((width - kPadX * 2) * 0.32f));
}


int OverviewPanel::getPreferredHeight(int width) const
{
	const int qualitiesWidth = juce::jmax(1, width - kPadX * 2 - rangeColumnWidth(width) - kColumnGap);

	return kPadY * 2 + juce::jmax(kMinRangeHeight, mQualities.getPreferredHeight(qualitiesWidth));
}


void OverviewPanel::resized()
{
	auto area = getLocalBounds().reduced(kPadX, kPadY);

	auto left = area.removeFromLeft(rangeColumnWidth(getWidth()));
	area.removeFromLeft(kColumnGap);

	mRanges.setBounds(left);
	mQualities.setBounds(area);
}
