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

private:
	const int width	 = 272;
	const int height = 204;
};
