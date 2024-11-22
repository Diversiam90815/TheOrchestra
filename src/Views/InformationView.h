/*
  ==============================================================================

	Module			InformationView
	Description		View box containing the useful additional information of the instrument

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "CustomLookAndFeel.h"


class InformationView : public Component
{
public:
	InformationView();
	~InformationView();

	void init();
	void deinit();


private:
	CustomLookAndFeel mCustomLookAndFeel;

	Label			  mTitle;

	Label			  mFirstInformation;
	Label			  mSecondInformation;
	Label			  mThirdInformation;
	Label			  mFourthInformation;

	const int		  mTitleX		= 172;
	const int		  mTitleY		= 33;
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
