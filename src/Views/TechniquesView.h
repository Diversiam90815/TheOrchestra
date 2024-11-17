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

	const int		  mWidth  = 272;
	const int		  mHeight = 204;
};
