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


void InstrumentRangesView::displayInstrument(InstrumentProfile &instrument)
{
	const auto &range	   = instrument.getRange();

	std::string lowerNote  = range.getLowerRange();
	std::string higherNote = range.getHigherRange();

	mLowerRangeNoteName.setText(lowerNote, juce::dontSendNotification);
	mHigherRangeNoteName.setText(higherNote, juce::dontSendNotification);

	const auto &transposition = range.getTransposition();

	mTranspositionNoteName.setText(transposition, juce::dontSendNotification);

	// Set images
	InstrumentID key				 = instrument.getInstrumentID();
	juce::File	 lowerRangeImagePath = mFileManager.getInstrumentImage(TypeOfImage::LowerRangeNotation, key);
	setAndRescaleImage(mLowerRangeNoteImage, lowerRangeImagePath, mLowerNoteImageX, mLowerNoteImageY, mImageBoxWidth, mImageBoxHeight);

	juce::File upperRangeImagePath = mFileManager.getInstrumentImage(TypeOfImage::UpperRangeNotation, key);
	setAndRescaleImage(mHigherRangeNoteImage, upperRangeImagePath, mHigherNoteImageX, mHigherNoteImageY, mImageBoxWidth, mImageBoxHeight);

	juce::File upperTranspositionPath = mFileManager.getInstrumentImage(TypeOfImage::TranspositionHigherNotation, key);
	setAndRescaleImage(mTranspositionHigherNoteImage, upperTranspositionPath, mHigherNoteImageX, mTranspositionImageY, mImageBoxWidth, mImageBoxHeight);

	juce::File lowerTranspositionPath = mFileManager.getInstrumentImage(TypeOfImage::TranspositionLowerNotation, key);
	setAndRescaleImage(mTranspositionLowerNoteImage, lowerTranspositionPath, mLowerNoteImageX, mTranspositionImageY, mImageBoxWidth, mImageBoxHeight);
}
