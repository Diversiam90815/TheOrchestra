/*
  ==============================================================================
	Module			InstrumentImageView
	Description		Draws an instrument photo at its natural aspect ratio
  ==============================================================================
*/

#include "InstrumentImageView.h"


InstrumentImageView::InstrumentImageView()
{
	setInterceptsMouseClicks(false, false);
	setOpaque(false);
}


void InstrumentImageView::setImageFile(const juce::File &file)
{
	mImage = file.existsAsFile() ? juce::ImageCache::getFromFile(file) : juce::Image();
	repaint();
}


void InstrumentImageView::clear()
{
	mImage = juce::Image();
	repaint();
}


void InstrumentImageView::paint(juce::Graphics &g)
{
	if (!mImage.isValid())
		return;

	g.setOpacity(1.0f);

	// centred keeps the aspect ratio; onlyReduceInSize avoids upscaling a small source into a blur.
	g.drawImageWithin(mImage, 0, 0, getWidth(), getHeight(), juce::RectanglePlacement::centred | juce::RectanglePlacement::onlyReduceInSize, false);
}
