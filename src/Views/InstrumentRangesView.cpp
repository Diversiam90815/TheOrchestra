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

	addAndConfigureLabel(mRangesTitle, "RangesTitle", "Ranges", mRangesTitleX, mRangesTitleY, mRangesTitleWidth, mRangesTitleHeight);
	addAndConfigureLabel(mTranspositionTitle, "TranspositionTitle", "Transposition", mTranspositionTitleX, mTranspositionTitleY, mTranspositionTitleWidth,
						 mTranspositionTitleHeight);

	addAndConfigureImage(mLowerRangeNoteImage, mLowerNoteImageX, mLowerNoteImageY, mImageBoxWidth, mImageBoxHeight);
	addAndConfigureImage(mHigherRangeNoteImage, mHigherNoteImageX, mHigherNoteImageY, mImageBoxWidth, mImageBoxHeight);
	addAndConfigureImage(mTranspositionHigherNoteImage, mHigherNoteImageX, mTranspositionImageY, mImageBoxWidth, mImageBoxHeight);
	addAndConfigureImage(mTranspositionLowerNoteImage, mLowerNoteImageX, mTranspositionImageY, mImageBoxWidth, mImageBoxHeight);

	addAndConfigureLabel(mLowerRangeNoteName, "RangesLowerNoteName", "", mLowerNoteNameX, mLowerNoteNameY, mNoteNameWidth, mNoteNameHeight);
	addAndConfigureLabel(mHigherRangeNoteName, "RangesHigherNoteName", "", mHigherNoteNameX, mHigherNoteNameY, mNoteNameWidth, mNoteNameHeight);

	addAndConfigureLabel(mTranspositionNoteName, "TranspositonNote", "", mTranspositionNoteX, mTranspositionNoteY, mTranspositionNoteWidth, mTranspositionNoteHeight);
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

	// Set images
	int	 key				 = instrument.getKey();
	File lowerRangeImagePath = mFileManager.getInstrumentImage(TypeOfImage::LowerRangeNotation, key);
	setAndRescaleImage(mLowerRangeNoteImage, lowerRangeImagePath, mLowerNoteImageX, mLowerNoteImageY, mImageBoxWidth, mImageBoxHeight);

	File upperRangeImagePath = mFileManager.getInstrumentImage(TypeOfImage::UpperRangeNotation, key);
	setAndRescaleImage(mHigherRangeNoteImage, upperRangeImagePath, mHigherNoteImageX, mHigherNoteImageY, mImageBoxWidth, mImageBoxHeight);

	File upperTranspositionPath = mFileManager.getInstrumentImage(TypeOfImage::TranspositionHigherNotation, key);
	setAndRescaleImage(mTranspositionHigherNoteImage, upperTranspositionPath, mHigherNoteImageX, mTranspositionImageY, mImageBoxWidth, mImageBoxHeight);

	File lowerTranspositionPath = mFileManager.getInstrumentImage(TypeOfImage::TranspositionLowerNotation, key);
	setAndRescaleImage(mTranspositionLowerNoteImage, lowerTranspositionPath, mLowerNoteImageX, mTranspositionImageY, mImageBoxWidth, mImageBoxHeight);
}
