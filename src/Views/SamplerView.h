/*
  ==============================================================================

	Module			SamplerView
	Description		View box containing sampler information such as articulations & MIDI CC values

  ==============================================================================
*/

#pragma once

#include "CustomComponent.h"
#include "Sampler.h"
#include "Helper.h"


class SamplerView : public CustomComponent
{
public:
	SamplerView();
	~SamplerView();

	void init();

	void displayInstrument(InstrumentInfo &instrument) override
	{
	}

	void displayInstrument(std::set<Articulation> availableArticulations);

	void articulationChanged(Articulation newArticulation);

private:
	Label	  mTitle;
	ComboBox  mArticulations;

	const int mWidth			   = 269;
	const int mHeight			   = 107;

	const int mTitleWidth		   = 110;
	const int mTitleHeight		   = 33;

	const int mTitleX			   = 79;
	const int mTitleY			   = 10;

	const int mArticulationsWidth  = 239;
	const int mArticulationsHeight = 40;

	const int mArticulationsX	   = 15;
	const int mArticulationsY	   = 54;
};