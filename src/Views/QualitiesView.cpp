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
	setSize(mWidth, mHeight);

	// Set the title
	addAndMakeVisible(&mTitle);
	mTitle.setName("QualitiesTitle");
	mTitle.setText("Qualities", dontSendNotification);
	mTitle.setBounds(mQualitiesTitleX, mQualitiesTitleY, mQualitiesTitleWidth, mQualitiesTitleHeight);

	// Settings the note names positions
	addAndMakeVisible(&mFirstLowerNote);
	mFirstLowerNote.setBounds(mLowerNoteX, mFirstRowY, mNoteLabelWidth, mNoteLabelHeight);
	addAndMakeVisible(&mFirstHigherNote);
	mFirstHigherNote.setBounds(mHigherNoteX, mFirstRowY, mNoteLabelWidth, mNoteLabelHeight);

	addAndMakeVisible(&mSecondLowerNote);
	mSecondLowerNote.setBounds(mLowerNoteX, mSecondRowY, mNoteLabelWidth, mNoteLabelHeight);
	addAndMakeVisible(&mSecondHigherNote);
	mSecondHigherNote.setBounds(mHigherNoteX, mSecondRowY, mNoteLabelWidth, mNoteLabelHeight);

	addAndMakeVisible(&mThirdLowerNote);
	mThirdLowerNote.setBounds(mLowerNoteX, mThirdRowY, mNoteLabelWidth, mNoteLabelHeight);
	addAndMakeVisible(&mThirdHigherNote);
	mThirdHigherNote.setBounds(mHigherNoteX, mThirdRowY, mNoteLabelWidth, mNoteLabelHeight);

	addAndMakeVisible(&mFourthLowerNote);
	mFourthLowerNote.setBounds(mLowerNoteX, mFourthRowY, mNoteLabelWidth, mNoteLabelHeight);
	addAndMakeVisible(&mFourthLowerNote);
	mFourthLowerNote.setBounds(mHigherNoteX, mFourthRowY, mNoteLabelWidth, mNoteLabelHeight);

	// Setting the qualities positions
	addAndMakeVisible(&mFirstQuality);
	mFirstQuality.setBounds(mQualityX, mFirstRowY, mQualityWidth, mQualityHeight);
	addAndMakeVisible(&mSecondQuality);
	mSecondQuality.setBounds(mQualityX, mSecondRowY, mQualityWidth, mQualityHeight);
	addAndMakeVisible(&mThirdQuality);
	mThirdQuality.setBounds(mQualityX, mThirdRowY, mQualityWidth, mQualityHeight);
	addAndMakeVisible(&mFourthQuality);
	mFourthQuality.setBounds(mQualityX, mFourthRowY, mQualityWidth, mQualityHeight);
}


void QualitiesView::deinit()
{
}
