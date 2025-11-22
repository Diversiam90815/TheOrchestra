/*
  ==============================================================================
	Module			InstrumentRangesView
	Description		View box containing the range and transposition of the instrument
  ==============================================================================
*/

#pragma once

#include "CustomComponent.h"
#include "NotationComponent.h"


class InstrumentRangesView : public CustomComponent
{
public:
	InstrumentRangesView()	= default;
	~InstrumentRangesView() = default;

	void init() override;
	void displayInstrument(InstrumentProfile &instrument) override;

private:
	juce::Label		  mRangesTitle;

	juce::Label		  mLowerRangeNoteName;
	juce::Label		  mHigherRangeNoteName;
	juce::Label		  mTranspositionNoteName;

	NotationComponent mLowerRangeNoteNotation;
	NotationComponent mHigherRangeNoteNotation;


	const int		  mWidth			 = 269;
	const int		  mHeight			 = 328;

	const int		  mRangesTitleX		 = 79;
	const int		  mRangesTitleY		 = 15;
	const int		  mRangesTitleWidth	 = 110;
	const int		  mRangesTitleHeight = 19;


	const int		  mNoteNameWidth	 = 30;
	const int		  mNoteNameHeight	 = 17;

	const int		  mLowerNoteImageX	 = 38;
	const int		  mLowerNoteImageY	 = 55;
	const int		  mLowerNoteNameX	 = 66;
	const int		  mLowerNoteNameY	 = 124;

	const int		  mHigherNoteImageX	 = 146;
	const int		  mHigherNoteImageY	 = 55;
	const int		  mHigherNoteNameX	 = 178;
	const int		  mHigherNoteNameY	 = 124;

	const int		  mImageBoxWidth	 = 100;
	const int		  mImageBoxHeight	 = 80;
};
