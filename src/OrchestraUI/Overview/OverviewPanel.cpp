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


void OverviewPanel::resized()
{
	auto area = getLocalBounds().reduced(kPadX, kPadY);

	auto left = area.removeFromLeft(kRangeWidth);
	area.removeFromLeft(kColumnGap);

	mRanges.setBounds(left);
	mQualities.setBounds(area);
}
