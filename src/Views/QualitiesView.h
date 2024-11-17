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
	void deinit();


private:
	CustomLookAndFeel mCustomLookAndFeel;

	const int		  mWidth  = 269;
	const int		  mHeight = 305;
};
