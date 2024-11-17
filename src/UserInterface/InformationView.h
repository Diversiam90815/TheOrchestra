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

private:
	const int width	 = 377;
	const int height = 170;
};
