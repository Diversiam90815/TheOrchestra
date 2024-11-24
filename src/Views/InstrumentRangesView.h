/*
  ==============================================================================

	Module			InstrumentRangesView
	Description		View box containing the range and transposition of the instrument

  ==============================================================================
*/

#pragma once

#include "CustomComponent.h"


class InstrumentRangesView : public CustomComponent
{
public:
	InstrumentRangesView();
	~InstrumentRangesView();

	void init();

	void displayInstrument(InstrumentInfo &instrument) override;

private:
	Label		  mRangesTitle;
	Label		  mTranspositionTitle;

	Label		  mLowerRangeNoteName;
	Label		  mHigherRangeNoteName;
	Label		  mTranspositionNoteName;

	DrawableImage mLowerRangeNoteImage;
	DrawableImage mHigherRangeNoteImage;
	DrawableImage mTranspositionNoteImage;

	const int	  mWidth					= 269;
	const int	  mHeight					= 328;

	const int	  mRangesTitleX				= 79;
	const int	  mRangesTitleY				= 15;
	const int	  mRangesTitleWidth			= 110;
	const int	  mRangesTitleHeight		= 19;

	const int	  mTranspositionTitleX		= 69;
	const int	  mTranspositionTitleY		= 176;
	const int	  mTranspositionTitleWidth	= 130;
	const int	  mTranspositionTitleHeight = 19;

	const int	  mNoteNameWidth			= 26;
	const int	  mNoteNameHeight			= 17;

	const int	  mLowerNoteImageX			= 38;
	const int	  mLowerNoteImageY			= 55;
	const int	  mLowerNoteNameX			= 66;
	const int	  mLowerNoteNameY			= 124;

	const int	  mHigherNoteImageX			= 146;
	const int	  mHigherNoteImageY			= 55;
	const int	  mHigherNoteNameX			= 178;
	const int	  mHigherNoteNameY			= 124;

	const int	  mTranspositionImageX		= 91;
	const int	  mTranspositionImageY		= 206;
	const int	  mTranspositionNoteX		= 75;
	const int	  mTranspositionNoteY		= 281;
	const int	  mTranspositionNoteWidth	= 119;
	const int	  mTranspositionNoteHeight	= 17;

	const int	  mImageBoxWidth			= 87;
	const int	  mImageBoxHeight			= 64;
};
