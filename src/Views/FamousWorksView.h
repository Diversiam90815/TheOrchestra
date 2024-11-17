/*
  ==============================================================================

	Module			FamousWoksView
	Description		View box containing famous works featuring the instrument

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "CustomLookAndFeel.h"

class FamousWorksView : public Component
{
public:
	FamousWorksView();
	~FamousWorksView();

	void init();
	void deinit();


private:
	CustomLookAndFeel mCustomLookAndFeel;

	const int		  mWidth  = 211;
	const int		  mHeight = 226;
};
