/*
  ==============================================================================
	Module			TechniquesView
	Description		View box containing the various playing techniques of the instrument
  ==============================================================================
*/

#pragma once
#include "CustomComponent.h"


class TechniquesView : public CustomComponent
{
public:
	TechniquesView()  = default;
	~TechniquesView() = default;

	void init() override;
	void displayInstrument(InstrumentProfile &instrument) override;

private:
	juce::Label			mTitle;

	juce::TooltipWindow tooltipWindow{this};

	// PlayingTechniques displays using text buttons with tooltips in 3 rows a 3-3-2
	juce::TextButton	mTech1;
	juce::TextButton	mTech2;
	juce::TextButton	mTech3;

	juce::TextButton	mTech4;
	juce::TextButton	mTech5;
	juce::TextButton	mTech6;

	juce::TextButton	mTech7;
	juce::TextButton	mTech8;

	const int			mTechTitleX			  = 48;
	const int			mTechTitleY			  = 8;
	const int			mTechTitleWidth		  = 172;
	const int			mTechTitleHeight	  = 33;

	const int			mButtonWidth		  = 72;
	const int			mButtonHeight		  = 31;

	const int			mFirstRowY			  = 59;
	const int			mSecondRowY			  = 108;
	const int			mThirdRowY			  = 157;

	const int			mFirstColumnX		  = 10;
	const int			mSecondColumnX		  = 100;
	const int			mThirdColumnX		  = 190;

	const int			mLastRowFirstColumnX  = 46;
	const int			mLastRowSecondColumnX = 154;

	const int			mWidth				  = 272;
	const int			mHeight				  = 204;
};
