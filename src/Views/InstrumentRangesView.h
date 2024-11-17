/*
  ==============================================================================

	Module			InstrumentRangesView
	Description		View box containing the range and transposition of the instrument

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "CustomLookAndFeel.h"

#include "InstrumentInfo.h"


class InstrumentRangesView : public Component
{
public:
	InstrumentRangesView();
	~InstrumentRangesView();

	void init();
	void deinit();

	void setInstrument(InstrumentInfo& info);

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

	const int		  mWidth  = 269;
	const int		  mHeight = 328;


	friend class InstrumentRangesViewModel;
};
