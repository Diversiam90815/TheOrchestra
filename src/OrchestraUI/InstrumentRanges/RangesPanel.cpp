/*
  ==============================================================================
	Module			RangesPanel
	Description		Compact range display with notation, supporting written/sounding toggle
  ==============================================================================
*/

#include "RangesPanel.h"
#include "Helper.h"


RangesPanel::RangesPanel() : OrchestraPanel("Range")
{
	mLowLabel.setName("SectionTitle");
	mLowLabel.setText("LOWEST NOTE", juce::dontSendNotification);
	addAndMakeVisible(mLowLabel);

	mHighLabel.setName("SectionTitle");
	mHighLabel.setText("HIGHEST NOTE", juce::dontSendNotification);
	addAndMakeVisible(mHighLabel);

	mLowNoteName.setName("NoteName");
	addAndMakeVisible(mLowNoteName);

	mHighNoteName.setName("NoteName");
	addAndMakeVisible(mHighNoteName);

	mPitchModeLabel.setName("SectionTitle");
	addAndMakeVisible(mPitchModeLabel);

	addAndMakeVisible(mLowNotation);
	addAndMakeVisible(mHighNotation);
}


void RangesPanel::setInstrument(const InstrumentProfile &instrument)
{
	auto range = instrument.getRange();

	mWrittenLow	   = range.getLowerRange();
	mWrittenHigh   = range.getHigherRange();
	mSoundingLow   = range.getDisplayedLowerRange();
	mSoundingHigh  = range.getDisplayedHigherRange();

	mHasTransposition = !range.getTransposition().empty();
	mPitchMode		  = PitchMode::Written;

	updateDisplay();
	resized();
}


void RangesPanel::setClef(Clef clef)
{
	mLowNotation.setClef(clef);
	mHighNotation.setClef(clef);
	repaint();
}


void RangesPanel::setPitchMode(PitchMode mode)
{
	mPitchMode = mode;
	updateDisplay();
}


void RangesPanel::updateDisplay()
{
	std::string low, high;

	if (mPitchMode == PitchMode::Sounding)
	{
		low	 = mSoundingLow;
		high = mSoundingHigh;
		mPitchModeLabel.setText("Sounding Pitch", juce::dontSendNotification);
	}
	else
	{
		low	 = mWrittenLow;
		high = mWrittenHigh;
		mPitchModeLabel.setText(mHasTransposition ? "Written Pitch" : "", juce::dontSendNotification);
	}

	mLowNoteName.setText(low, juce::dontSendNotification);
	mHighNoteName.setText(high, juce::dontSendNotification);

	mLowNotation.setNoteFromString(low);
	mHighNotation.setNoteFromString(high);

	repaint();
}


void RangesPanel::resized()
{
	auto area = getContentArea();

	// Pitch mode label on the right of the title area
	if (mHasTransposition)
	{
		auto titleRow = getLocalBounds().reduced(kPadding).removeFromTop(kTitleHeight);
		mPitchModeLabel.setBounds(titleRow.removeFromRight(120));
	}
	else
	{
		mPitchModeLabel.setBounds(0, 0, 0, 0);
	}

	// Two columns with a divider gap
	const int halfW		= (area.getWidth() - 20) / 2;
	const int notationW = 120;
	const int notationH = 70;

	auto leftCol  = area.removeFromLeft(halfW);
	area.removeFromLeft(20); // gap
	auto rightCol = area;

	// Left column: low note
	auto labelArea = leftCol.removeFromTop(16);
	mLowLabel.setBounds(labelArea);

	leftCol.removeFromTop(4);
	auto notArea = leftCol.removeFromTop(notationH);
	mLowNotation.setBounds(notArea.withSizeKeepingCentre(notationW, notationH));

	leftCol.removeFromTop(4);
	mLowNoteName.setBounds(leftCol.removeFromTop(20));

	// Right column: high note
	labelArea = rightCol.removeFromTop(16);
	mHighLabel.setBounds(labelArea);

	rightCol.removeFromTop(4);
	notArea = rightCol.removeFromTop(notationH);
	mHighNotation.setBounds(notArea.withSizeKeepingCentre(notationW, notationH));

	rightCol.removeFromTop(4);
	mHighNoteName.setBounds(rightCol.removeFromTop(20));
}
