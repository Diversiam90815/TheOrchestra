/*
  ==============================================================================

	Module			InstrumentView
	Description		View box containing the name and an image of the instrument

  ==============================================================================
*/

#include "InstrumentView.h"


InstrumentView::InstrumentView()
{
}


InstrumentView::~InstrumentView()
{
}


void InstrumentView::init()
{
	setSize(mWidth, mHeight);
	addAndConfigureLabel(mName, "InstrumentTitle", "", mNameX, mNameY, mNameWidth, mNameHeight);
	addAndConfigureImage(mImage, mImageX, mImageY, mImageWidth, mImageHeight);
}


void InstrumentView::displayInstrument(InstrumentInfo &instrument)
{
	const String &name = instrument.getName();
	mName.setText(name, dontSendNotification);
}
