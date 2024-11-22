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
	setLookAndFeel(&mCustomLookAndFeel);
	setSize(mWidth, mHeight);

	// Set the Ranges title
	mRangesTitle.setName("RangesTitle");
	mRangesTitle.setText("Ranges", NotificationType::dontSendNotification);
	mRangesTitle.setBounds(mRangesTitleX, mRangesTitleY, mRangesTitleWidth, mRangesTitleHeight);

	// Set the Transposition title
	mTranspositionTitle.setName("TranspositionTitle");
	mTranspositionTitle.setText("Transposition", NotificationType::dontSendNotification);
	mTranspositionTitle.setBounds(mTranspositionTitleX, mTranspositionTitleY, mTranspositionTitleWidth, mTranspositionTitleHeight);

	// Set the images positions
	mLowerRangeNoteImage.setBounds(mLowerNoteImageX, mLowerNoteImageY, mImageBoxWidth, mImageBoxHeight);
	mHigherRangeNoteImage.setBounds(mHigherNoteImageX, mHigherNoteImageY, mImageBoxWidth, mImageBoxHeight);
	mTranspositionNoteImage.setBounds(mTranspositionImageX, mTranspositionImageY, mImageBoxWidth, mImageBoxHeight);

	// Set the note name's positions
	mLowerRangeNoteName.setBounds(mLowerNoteNameX, mLowerNoteNameY, mNoteNameWidth, mNoteNameHeight);
	mHigherRangeNoteName.setBounds(mHigherNoteNameX, mHigherNoteNameY, mNoteNameWidth, mNoteNameHeight);
	mTranspositionNoteName.setBounds(mTranspositionNoteX, mTranspositionNoteY, mTranspositionNoteWidth, mTranspositionNoteHeight);
}


void InstrumentRangesView::deinit()
{
	setLookAndFeel(nullptr);
}
