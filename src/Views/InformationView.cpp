/*
  ==============================================================================

	Module			InformationView
	Description		View box containing the useful additional information of the instrument

  ==============================================================================
*/

#include "InformationView.h"


InformationView::InformationView()
{
}


InformationView::~InformationView()
{
}


void InformationView::init()
{
	setLookAndFeel(&mCustomLookAndFeel);
	setSize(mWidth, mHeight);
}


void InformationView::deinit()
{
	setLookAndFeel(nullptr);
}
