/*
  ==============================================================================
	Module			RangesPanel
	Description		Two-column range display with notation, vertically centered.
					Left column = lowest note, Right column = highest note.
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
	auto range		  = instrument.getRange();

	mWrittenLow		  = range.getWrittenLowNote();
	mWrittenHigh	  = range.getWrittenHighNote();
	mSoundingLow	  = range.getSoundingLowNote();
	mSoundingHigh	  = range.getSoundingHighNote();

	// Detect transposition: written and sounding ranges differ
	mHasTransposition = (mWrittenLow != mSoundingLow) || (mWrittenHigh != mSoundingHigh);
	mPitchMode		  = PitchMode::Written;

	updateDisplay();
	resized();
}


void RangesPanel::setClef(Clef /*clef*/)
{
	// @TODO:
	//		- Range panel always auto-selects the best clef per note.
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

	// Pitch mode label in the title area (right-aligned)
	if (mHasTransposition)
	{
		auto titleRow = getLocalBounds().reduced(kPadding, 0).withY(kPadding).withHeight(kTitleHeight);
		mPitchModeLabel.setBounds(titleRow.removeFromRight(140));
	}
	else
	{
		mPitchModeLabel.setBounds(0, 0, 0, 0);
	}

	// Two columns side-by-side, each vertically centered:
	//   Section title (top)
	//   Notation (centered, takes most space)
	//   Note name (bottom)

	const int gutter	= Space::xl;
	const int halfW		= (area.getWidth() - gutter) / 2;
	const int notationW = 126;
	const int notationH = 100;
	const int labelH	= 22;
	const int nameH		= 32;
	const int innerGap	= Space::xs;

	// Total content height for centering
	int		  stackH	= labelH + innerGap + notationH + innerGap + nameH;
	int		  topMargin = juce::jmax(0, (area.getHeight() - stackH) / 2);

	auto	  leftCol	= area.removeFromLeft(halfW);
	area.removeFromLeft(gutter);
	auto rightCol = area;

	// --- Left column: low note ---
	auto lc		  = leftCol;
	lc.removeFromTop(topMargin);

	mLowLabel.setBounds(lc.removeFromTop(labelH));
	lc.removeFromTop(innerGap);

	auto lowNotArea = lc.removeFromTop(notationH);
	mLowNotation.setBounds(lowNotArea.withSizeKeepingCentre(notationW, notationH));

	lc.removeFromTop(innerGap);
	mLowNoteName.setBounds(lc.removeFromTop(nameH));

	// --- Right column: high note ---
	auto rc = rightCol;
	rc.removeFromTop(topMargin);

	mHighLabel.setBounds(rc.removeFromTop(labelH));
	rc.removeFromTop(innerGap);

	auto highNotArea = rc.removeFromTop(notationH);
	mHighNotation.setBounds(highNotArea.withSizeKeepingCentre(notationW, notationH));

	rc.removeFromTop(innerGap);
	mHighNoteName.setBounds(rc.removeFromTop(nameH));
}
