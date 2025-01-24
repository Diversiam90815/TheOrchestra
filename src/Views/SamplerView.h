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

private:
	ComboBox mArticulations;
};