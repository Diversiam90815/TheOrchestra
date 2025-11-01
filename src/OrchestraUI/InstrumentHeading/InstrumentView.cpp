/*
  ==============================================================================
	Module			InstrumentView
	Description		View box containing the name and an image of the instrument
  ==============================================================================
*/

#include "InstrumentView.h"


void InstrumentView::init()
{
	setSize(mWidth, mHeight);
	addAndConfigureLabel(mName, "InstrumentTitle", "", mNameX, mNameY, mNameWidth, mNameHeight);
	addAndConfigureImage(mImage, mImageX, mImageY, mImageWidth, mImageHeight);
}


void InstrumentView::displayInstrument(InstrumentInfo &instrument)
{
	const auto &name = instrument.getName();
	mName.setText(name, juce::dontSendNotification);

	InstrumentID key	   = instrument.getKey();
	juce::File	 imagePath = mFileManager.getInstrumentImage(TypeOfImage::InstrumentImage, key);
	setAndRescaleImage(mImage, imagePath, mImageX, mImageY, mImageWidth, mImageHeight);
}
