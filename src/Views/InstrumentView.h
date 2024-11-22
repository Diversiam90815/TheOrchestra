/*
  ==============================================================================

	Module			InstrumentView
	Description		View box containing the name and an image of the instrument

  ==============================================================================
*/

#pragma once
#include "JuceHeader.h"
#include "CustomLookAndFeel.h"


class InstrumentView : public Component
{
public:
	InstrumentView();
	~InstrumentView();

	void init();

	void deinit();

private:
	CustomLookAndFeel mCustomLookNFeel;

	Label			  mName;  // Name of the instrument

	DrawableImage	  mImage; // Image of the instrument

	const int		  mNameX	   = 16;
	const int		  mNameY	   = 22;
	const int		  mNameWidth  = 110;
	const int		  mNameHeight = 33;

	const int		  mImageX	   = 157;
	const int		  mImageY	   = 7;
	const int		  mImageWidth  = 100;
	const int		  mImageHeight = 64;

	const int		  mWidth	   = 314;
	const int		  mHeight	   = 77;
};
