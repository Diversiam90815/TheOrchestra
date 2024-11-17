/*
  ==============================================================================

	Module			InformationView
	Description		View box containing the useful additional information of the instrument

  ==============================================================================
*/

#include "FamousWorksView.h"


FamousWorksView::FamousWorksView()
{
}


FamousWorksView::~FamousWorksView()
{
}


void FamousWorksView::init()
{
	setLookAndFeel(&mCustomLookAndFeel);
	setSize(mWidth, mHeight);
}


void FamousWorksView::deinit()
{
	setLookAndFeel(nullptr);
}
