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
	QualitiesView();
	~QualitiesView();

	void init();
	void deinit();

private:

	Label			  mTitle;

	Label			  mFirstLowerNote;
	Label			  mFirstHigherNote;
	Label			  mFirstQuality;

	Label			  mSecondLowerNote;
	Label			  mSecondHigherNote;
	Label			  mSecondQuality;

	Label			  mThirdLowerNote;
	Label			  mThirdHigherNote;
	Label			  mThirdQuality;

	Label			  mFourthLowerNote;
	Label			  mFourthHigherNote;
	Label			  mFourthQuality;

	const int		  mQualitiesTitleX			= 79;
	const int		  mQualitiesTitleY			= 15;
	const int		  mQualitiesTitleWidth		= 110;
	const int		  mQualitiesTitleHeight		= 33;

	const int		  mNoteLabelWidth			= 17;
	const int		  mNoteLabelHeight			= 17;

	const int		  mQualityWidth				= 151;
	const int		  mQualityHeight			= 48;

	const int		  mFirstRowY				= 67;
	const int		  mSecondRowY				= 126;
	const int		  mThirdRowY				= 185;
	const int		  mFourthRowY				= 244;

	const int		  mQualityX					= 100;
	const int		  mLowerNoteX				= 20;
	const int		  mHigherNoteX				= 59;

	const int		  mNotesBackgroundBoxWidth	= 72;
	const int		  mNotesBackgroundBoxHeight = 31;

	const int		  mWidth					= 269;
	const int		  mHeight					= 305;
};
