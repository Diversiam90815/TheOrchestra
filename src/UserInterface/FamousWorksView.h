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

private:
	const int width	 = 211;
	const int height = 226;
};
