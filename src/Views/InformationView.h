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
	InformationView();
	~InformationView();

	void init();

	void displayInstrument(InstrumentInfo &instrument) override;


private:

	Label			  mTitle;

	Label			  mFirstInformation;
	Label			  mSecondInformation;
	Label			  mThirdInformation;
	Label			  mFourthInformation;

	const int		  mTitleX		= 102;
	const int		  mTitleY		= 7;
	const int		  mTitleWidth	= 172;
	const int		  mTitleHeight	= 33;

	const int		  mInfoWidth	= 151;
	const int		  mInfoHeight	= 48;

	const int		  mFirstRowY	= 50;
	const int		  mSecondRowY	= 104;

	const int		  mFirstColumX	= 8;
	const int		  mSecondColumx = 199;

	const int		  mWidth		= 377;
	const int		  mHeight		= 170;
};
