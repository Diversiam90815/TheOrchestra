/*
  ==============================================================================
	Module			InformationView
	Description		View box containing the useful additional information of the instrument
  ==============================================================================
*/

#pragma once
#include "CustomComponent.h"


class InformationView : public CustomComponent
{
public:
	InformationView()  = default;
	~InformationView() = default;

	void init() override;
	void displayInstrument(InstrumentInfo &instrument) override;

private:
	juce::Label		 mTitle;

	juce::TextEditor mFirstInformation;
	juce::TextEditor mSecondInformation;
	juce::TextEditor mThirdInformation;
	juce::TextEditor mFourthInformation;

	const int		 mTitleX	   = 102;
	const int		 mTitleY	   = 7;
	const int		 mTitleWidth   = 172;
	const int		 mTitleHeight  = 33;

	const int		 mInfoWidth	   = 151;
	const int		 mInfoHeight   = 48;

	const int		 mFirstRowY	   = 50;
	const int		 mSecondRowY   = 104;

	const int		 mFirstColumX  = 8;
	const int		 mSecondColumx = 199;

	const int		 mWidth		   = 377;
	const int		 mHeight	   = 170;
};
