/*
  ==============================================================================

	Module			QualitiesView
	Description		View box containing the qualities of the different ranges of the instrument

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "CustomLookAndFeel.h"


class QualitiesView : public Component
{
public:
	QualitiesView();
	~QualitiesView();

	void init();

private:
	const int width	 = 269;
	const int height = 305;
};
