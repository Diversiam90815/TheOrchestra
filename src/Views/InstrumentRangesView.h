/*
  ==============================================================================

	Module			InstrumentRangesView
	Description		View box containing the range and transposition of the instrument

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "CustomLookAndFeel.h"


class InstrumentRangesView : public Component
{
public:
	InstrumentRangesView();
	~InstrumentRangesView();

	void init();

	void deinit();

private:
	Label			  mRangesTitle;
	Label			  mTranspositionTitle;
	Label			  mLowerRangeNoteName;
	Label			  mHigherRangeNoteName;
	Label			  mTranspositionNoteName;

	DrawableImage	  mLowerRangeNoteImage;
	DrawableImage	  mHigherRangeNoteImage;
	DrawableImage	  mTranspositionNoteImage;

	CustomLookAndFeel mCustomLookAndFeel;

	const int		  mWidth			   = 269;
	const int		  mHeight			   = 328;

	const int		  mLowerNoteImageX	   = 38;
	const int		  mLowerNoteImageY	   = 55;

	const int		  mHigherNoteImageX	   = 146;
	const int		  mHigherNoteImageY	   = 55;

	const int		  mTranspositionImageX = 91;
	const int		  mTranspositionImageY = 206;

	const int		  mImageBoxWidth	   = 87;
	const int		  mImageBoxHeight	   = 64;


	friend class InstrumentRangesViewModel;
};
