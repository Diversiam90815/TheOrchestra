/*
  ==============================================================================

	Module			InstrumentRangesView
	Description		View box containing the range and transposition of the instrument

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "CustomLookAndFeel.h"


class InstrumentRangesView : public Component
{
public:
	InstrumentRangesView();
	~InstrumentRangesView();

	void init();


private:
	const int width	 = 269;
	const int height = 328;
};
