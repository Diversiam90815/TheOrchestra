/*
  ==============================================================================

	Module			InstrumentRangesView
	Description		View box containing the range and transposition of the instrument

  ==============================================================================
*/

#include "InstrumentRangesView.h"


InstrumentRangesView::InstrumentRangesView()
{
}


InstrumentRangesView::~InstrumentRangesView()
{
}


void InstrumentRangesView::init()
{
	setSize(mWidth, mHeight);

	// Set the Ranges title
	addAndMakeVisible(&mRangesTitle);
	mRangesTitle.setName("RangesTitle");
	mRangesTitle.setText("Ranges", NotificationType::dontSendNotification);
	mRangesTitle.setBounds(mRangesTitleX, mRangesTitleY, mRangesTitleWidth, mRangesTitleHeight);

	// Set the Transposition title
	addAndMakeVisible(&mTranspositionTitle);
	mTranspositionTitle.setName("TranspositionTitle");
	mTranspositionTitle.setText("Transposition", NotificationType::dontSendNotification);
	mTranspositionTitle.setBounds(mTranspositionTitleX, mTranspositionTitleY, mTranspositionTitleWidth, mTranspositionTitleHeight);

	// Set the images positions
	addAndMakeVisible(&mLowerRangeNoteImage);
	mLowerRangeNoteImage.setBounds(mLowerNoteImageX, mLowerNoteImageY, mImageBoxWidth, mImageBoxHeight);

	addAndMakeVisible(&mHigherRangeNoteImage);
	mHigherRangeNoteImage.setBounds(mHigherNoteImageX, mHigherNoteImageY, mImageBoxWidth, mImageBoxHeight);

	addAndMakeVisible(&mTranspositionNoteImage);
	mTranspositionNoteImage.setBounds(mTranspositionImageX, mTranspositionImageY, mImageBoxWidth, mImageBoxHeight);

	// Set the note name's positions
	addAndMakeVisible(&mLowerRangeNoteName);
	mLowerRangeNoteName.setName("RangesLowerNoteName");
	mLowerRangeNoteName.setBounds(mLowerNoteNameX, mLowerNoteNameY, mNoteNameWidth, mNoteNameHeight);

	addAndMakeVisible(&mHigherRangeNoteName);
	mHigherRangeNoteName.setName("RangesHigherNoteName");
	mHigherRangeNoteName.setBounds(mHigherNoteNameX, mHigherNoteNameY, mNoteNameWidth, mNoteNameHeight);

	addAndMakeVisible(&mTranspositionNoteName);
	mTranspositionNoteName.setBounds(mTranspositionNoteX, mTranspositionNoteY, mTranspositionNoteWidth, mTranspositionNoteHeight);
}


void InstrumentRangesView::displayInstrument(InstrumentInfo &instrument)
{
	const String &range		 = instrument.getRange();

	String		  lowerNote	 = getLowerOrHigherNote(range, true);
	String		  higherNote = getLowerOrHigherNote(range, false);

	mLowerRangeNoteName.setText(lowerNote, dontSendNotification);
	mHigherRangeNoteName.setText(higherNote, dontSendNotification);

	const String &transposition = instrument.getTransposition();

	mTranspositionNoteName.setText(transposition, dontSendNotification);
}
