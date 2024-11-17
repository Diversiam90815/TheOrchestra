/*
  ==============================================================================

	Module			QualitiesView
	Description		View box containing the qualities of the differnt ranges of the instrument

  ==============================================================================
*/

#include "QualitiesView.h"


QualitiesView::QualitiesView()
{
}


QualitiesView::~QualitiesView()
{
}


void QualitiesView::init()
{
	setLookAndFeel(&mCustomLookAndFeel);
	setSize(mWidth, mHeight);
}


void QualitiesView::deinit()
{
	setLookAndFeel(nullptr);
}
