/*
  ==============================================================================

	Module			TechniquesView
	Description		View box containing the various playing techniques of the instrument

  ==============================================================================
*/

#include "TechniquesView.h"


TechniquesView::TechniquesView()
{
}


TechniquesView::~TechniquesView()
{
}


void TechniquesView::init()
{
	setLookAndFeel(&mCustomLookAndFeel);
	setSize(mWidth, mHeight);
}


void TechniquesView::deinit()
{
	setLookAndFeel(nullptr);
}
