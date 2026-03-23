/*
  ==============================================================================
	Module			RangesPanel
	Description		Compact range display with notation, supporting written/sounding toggle.
					Horizontal layout: label | notation | note name  for each note
  ==============================================================================
*/

#include "RangesPanel.h"
#include "Helper.h"


RangesPanel::RangesPanel() : OrchestraPanel("Range")
{
	mLowLabel.setName("SectionTitle");
	mLowLabel.setText("LOWEST", juce::dontSendNotification);
	addAndMakeVisible(mLowLabel);

	mHighLabel.setName("SectionTitle");
	mHighLabel.setText("HIGHEST", juce::dontSendNotification);
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

	// Detect transposition: written and sounding ranges differ
	mHasTransposition = (mWrittenLow != mSoundingLow) || (mWrittenHigh != mSoundingHigh);
	mPitchMode		  = PitchMode::Written;

	updateDisplay();
	resized();
}


void RangesPanel::setClef(Clef /*clef*/)
{
	// Range panel always auto-selects the best clef per note.
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

	// setNoteFromString auto-selects the best clef for each note independently
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
		auto titleRow = getLocalBounds().reduced(kPadding).removeFromTop(kTitleHeight);
		mPitchModeLabel.setBounds(titleRow.removeFromRight(120));
	}
	else
	{
		mPitchModeLabel.setBounds(0, 0, 0, 0);
	}

	// Horizontal layout for each note:
	// [ Label (60px) | Notation (centered, 100x80) | NoteName (50px) ]
	// Two rows stacked vertically

	const int labelW	= 60;
	const int noteNameW = 50;
	const int notationW = 100;
	const int rowH		= (area.getHeight() - 4) / 2; // Two rows with small gap
	const int notationH = juce::jmin(rowH, 80);

	// Row 1: Lowest note
	auto lowRow = area.removeFromTop(rowH);
	area.removeFromTop(4); // gap

	auto lowLabelArea = lowRow.removeFromLeft(labelW);
	mLowLabel.setBounds(lowLabelArea.withSizeKeepingCentre(labelW, 16));

	auto lowNoteNameArea = lowRow.removeFromRight(noteNameW);
	mLowNoteName.setBounds(lowNoteNameArea.withSizeKeepingCentre(noteNameW, 20));

	mLowNotation.setBounds(lowRow.withSizeKeepingCentre(notationW, notationH));

	// Row 2: Highest note
	auto highRow = area;

	auto highLabelArea = highRow.removeFromLeft(labelW);
	mHighLabel.setBounds(highLabelArea.withSizeKeepingCentre(labelW, 16));

	auto highNoteNameArea = highRow.removeFromRight(noteNameW);
	mHighNoteName.setBounds(highNoteNameArea.withSizeKeepingCentre(noteNameW, 20));

	mHighNotation.setBounds(highRow.withSizeKeepingCentre(notationW, notationH));
}
