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

	mRangesTitle.setName("RangesTitle");
	mRangesTitle.setText("Ranges", NotificationType::dontSendNotification);

	mTranspositionTitle.setName("TranspositionTitle");
	mTranspositionTitle.setText("Transposition", NotificationType::dontSendNotification);

	mLowerRangeNoteImage.setBounds(mLowerNoteImageX, mLowerNoteImageY, mImageBoxWidth, mImageBoxHeight);
	mHigherRangeNoteImage.setBounds(mHigherNoteImageX, mHigherNoteImageY, mImageBoxWidth, mImageBoxHeight);
	mTranspositionNoteImage.setBounds(mTranspositionImageX, mTranspositionImageY, mImageBoxWidth, mImageBoxHeight);
}


void InstrumentRangesView::deinit()
{
	setLookAndFeel(nullptr);
}
