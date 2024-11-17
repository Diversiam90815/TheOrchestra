/*
  ==============================================================================

	Module			InstrumentRangesView
	Description		View box containing the range and transposition of the instrument

  ==============================================================================
*/

#include "InstrumentRangesView.h"


InstrumentRangesView::InstrumentRangesView()
{
}


InstrumentRangesView::~InstrumentRangesView()
{
}


void InstrumentRangesView::init()
{
	setLookAndFeel(&mCustomLookAndFeel);
	setSize(mWidth, mHeight);
}


void InstrumentRangesView::deinit()
{
	setLookAndFeel(nullptr);
}


void InstrumentRangesView::setInstrument(InstrumentInfo &info)
{
}
