/*
  ==============================================================================

	Module			TechniquesView
	Description		View box containing the various playing techniques of the instrument

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "CustomLookAndFeel.h"


class TechniquesView : public Component
{
public:
	TechniquesView();
	~TechniquesView();

	void init();

	void deinit();

private:
	CustomLookAndFeel mCustomLookAndFeel;

	Label			  mTitle;

	// Techniques displays using text buttons with tooltips in 3 rows á 3-3-2
	TextButton		  mTech1;
	TextButton		  mTech2;
	TextButton		  mTech3;

	TextButton		  mTech4;
	TextButton		  mTech5;
	TextButton		  mTech6;

	TextButton		  mTech7;
	TextButton		  mTech8;

	const int		  mTechTitleX			= 48;
	const int		  mTechTitleY			= 8;
	const int		  mTechTitleWidth		= 172;
	const int		  mTechTitleHeight		= 33;

	const int		  mButtonWidth			= 72;
	const int		  mButtonHeight			= 31;

	const int		  mFirstRowY			= 59;
	const int		  mSecondRowY			= 108;
	const int		  mThirdRowY			= 157;

	const int		  mFirstColumnX			= 10;
	const int		  mSecondColumnX		= 100;
	const int		  mThirdColumnX			= 190;

	const int		  mLastRowFirstColumnX	= 46;
	const int		  mLastRowSecondColumnX = 154;

	const int		  mWidth				= 272;
	const int		  mHeight				= 204;
};
