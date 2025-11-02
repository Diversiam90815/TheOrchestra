/*
  ==============================================================================
	Module			FamousWoksView
	Description		View box containing famous works featuring the instrument
  ==============================================================================
*/

#pragma once
#include "CustomComponent.h"


class FamousWorksView : public CustomComponent
{
public:
	FamousWorksView()  = default;
	~FamousWorksView() = default;

	void init() override;
	void displayInstrument(InstrumentInfo &instrument) override;

private:
	juce::Label		 mTitle;

	juce::TextEditor mFirstWork;
	juce::TextEditor mSecondWork;
	juce::TextEditor mThirdWork;

	const int		 mTitleX	  = 19;
	const int		 mTitleY	  = 8;
	const int		 mTitleWidth  = 172;
	const int		 mTitleHeight = 33;

	const int		 mWorkWidth	  = 151;
	const int		 mWorkHeight  = 48;

	const int		 mWorkX		  = 31;

	const int		 mFirstWorkY  = 48;
	const int		 mSecondWorkY = 108;
	const int		 mThirdWorkY  = 168;

	const int		 mWidth		  = 211;
	const int		 mHeight	  = 226;
};
