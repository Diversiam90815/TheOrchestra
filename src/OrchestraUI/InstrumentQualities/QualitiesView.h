/*
  ==============================================================================
	Module			QualitiesView
	Description		View box containing the qualities of the different ranges of the instrument
  ==============================================================================
*/

#pragma once
#include "CustomComponent.h"


class QualitiesView : public CustomComponent
{
public:
	QualitiesView()	 = default;
	~QualitiesView() = default;

	void init() override;
	void displayInstrument(InstrumentInfo &instrument) override;

private:
	Label	   mTitle;

	TextButton mFirstLowerNote;
	TextButton mFirstHigherNote;
	TextEditor mFirstQuality;

	TextButton mSecondLowerNote;
	TextButton mSecondHigherNote;
	TextEditor mSecondQuality;

	TextButton mThirdLowerNote;
	TextButton mThirdHigherNote;
	TextEditor mThirdQuality;

	TextButton mFourthLowerNote;
	TextButton mFourthHigherNote;
	TextEditor mFourthQuality;

	const int  mQualitiesTitleX			 = 79;
	const int  mQualitiesTitleY			 = 15;
	const int  mQualitiesTitleWidth		 = 110;
	const int  mQualitiesTitleHeight	 = 33;

	const int  mNoteButtonWidth			 = 36;
	const int  mNoteButtonHeight		 = 31;

	const int  mQualityWidth			 = 151;
	const int  mQualityHeight			 = 48;

	const int  mFirstRowY				 = 67;
	const int  mSecondRowY				 = 126;
	const int  mThirdRowY				 = 185;
	const int  mFourthRowY				 = 244;

	const int  mQualityX				 = 100;
	const int  mLowerNoteX				 = 13;
	const int  mHigherNoteX				 = 49;

	const int  mNotesBackgroundBoxWidth	 = 72;
	const int  mNotesBackgroundBoxHeight = 31;

	const int  mWidth					 = 269;
	const int  mHeight					 = 305;
};
