/*
  ==============================================================================

	Module			QualitiesView
	Description		View box containing the qualities of the differnt ranges of the instrument

  ==============================================================================
*/

#include "QualitiesView.h"


QualitiesView::QualitiesView()
{
}


QualitiesView::~QualitiesView()
{
}


void QualitiesView::init()
{
	setLookAndFeel(&mCustomLookAndFeel);
	setSize(mWidth, mHeight);

	// Set the title
	mTitle.setName("QualitiesTitle");
	mTitle.setText("Qualities", dontSendNotification);
	mTitle.setBounds(mQualitiesTitleX, mQualitiesTitleY, mQualitiesTitleWidth, mQualitiesTitleHeight);

	// Settings the note names positions
	mFirstLowerNote.setBounds(mLowerNoteX, mFirstRowY, mNoteLabelWidth, mNoteLabelHeight);
	mFirstHigherNote.setBounds(mHigherNoteX, mFirstRowY, mNoteLabelWidth, mNoteLabelHeight);

	mSecondLowerNote.setBounds(mLowerNoteX, mSecondRowY, mNoteLabelWidth, mNoteLabelHeight);
	mSecondLowerNote.setBounds(mHigherNoteX, mSecondRowY, mNoteLabelWidth, mNoteLabelHeight);

	mThirdLowerNote.setBounds(mLowerNoteX, mThirdRowY, mNoteLabelWidth, mNoteLabelHeight);
	mThirdHigherNote.setBounds(mHigherNoteX, mThirdRowY, mNoteLabelWidth, mNoteLabelHeight);

	mFourthLowerNote.setBounds(mLowerNoteX, mFourthRowY, mNoteLabelWidth, mNoteLabelHeight);
	mFourthLowerNote.setBounds(mHigherNoteX, mFourthRowY, mNoteLabelWidth, mNoteLabelHeight);

	// Setting the qualities positions
	mFirstQuality.setBounds(mQualityX, mFirstRowY, mQualityWidth, mQualityHeight);
	mSecondQuality.setBounds(mQualityX, mSecondRowY, mQualityWidth, mQualityHeight);
	mThirdQuality.setBounds(mQualityX, mThirdRowY, mQualityWidth, mQualityHeight);
	mFourthQuality.setBounds(mQualityX, mFourthRowY, mQualityWidth, mQualityHeight);
}


void QualitiesView::deinit()
{
	setLookAndFeel(nullptr);
}
