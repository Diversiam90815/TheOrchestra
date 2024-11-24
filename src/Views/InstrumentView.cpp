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

	// Set the instrument's name
	addAndMakeVisible(&mName);
	mName.setName("InstrumentTitle");
	mName.setBounds(mNameX, mNameY, mNameWidth, mNameHeight);

	// Set the instrument's image
	addAndMakeVisible(&mImage);
	mImage.setBounds(mImageX, mImageY, mImageWidth, mImageHeight);
}


void InstrumentView::displayInstrument(InstrumentInfo &instrument)
{
	const String &name = instrument.getName();
	mName.setText(name, dontSendNotification);
}
