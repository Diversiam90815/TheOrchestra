/*
  ==============================================================================
	Module			InstrumentRangesView
	Description		View box containing the range and transposition of the instrument
  ==============================================================================
*/

#include "InstrumentRangesView.h"


void InstrumentRangesView::init()
{
	setSize(mWidth, mHeight);

	addAndConfigureLabel(mRangesTitle, "RangesTitle", "Ranges", mRangesTitleX, mRangesTitleY, mRangesTitleWidth, mRangesTitleHeight);


	addAndConfigureLabel(mLowerRangeNoteName, "RangesLowerNoteName", "", mLowerNoteNameX, mLowerNoteNameY, mNoteNameWidth, mNoteNameHeight);
	addAndConfigureLabel(mHigherRangeNoteName, "RangesHigherNoteName", "", mHigherNoteNameX, mHigherNoteNameY, mNoteNameWidth, mNoteNameHeight);

	mLowerRangeNoteNotation.setBounds(mLowerNoteImageX, mLowerNoteImageY, mImageBoxWidth, mImageBoxHeight);
	addAndMakeVisible(mLowerRangeNoteNotation);

	mHigherRangeNoteNotation.setBounds(mHigherNoteImageX, mHigherNoteImageY, mImageBoxWidth, mImageBoxHeight);
	addAndMakeVisible(mHigherRangeNoteNotation);

	addAndConfigureLabel(mLowerRangeNoteName, "RangesLowerNoteName", "", mLowerNoteNameX, mLowerNoteNameY, mNoteNameWidth, mNoteNameHeight);
	addAndConfigureLabel(mHigherRangeNoteName, "RangesHigherNoteName", "", mHigherNoteNameX, mHigherNoteNameY, mNoteNameWidth, mNoteNameHeight);
}


void InstrumentRangesView::displayInstrument(InstrumentProfile &instrument)
{
	const auto &range	   = instrument.getRange();

	std::string lowerNote  = range.getLowerRange();
	std::string higherNote = range.getHigherRange();

	mLowerRangeNoteName.setText(lowerNote, juce::dontSendNotification);
	mHigherRangeNoteName.setText(higherNote, juce::dontSendNotification);

	mLowerRangeNoteNotation.setNoteFromString(lowerNote);
	mHigherRangeNoteNotation.setNoteFromString(higherNote);
}
