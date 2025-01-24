/*
  ==============================================================================

	Module			SamplerView
	Description		View box containing sampler information such as articulations & MIDI CC values

  ==============================================================================
*/

#include "SamplerView.h"


SamplerView::SamplerView()
{
}


SamplerView::~SamplerView()
{
}


void SamplerView::init()
{
}


void SamplerView::displayInstrument(std::list<Articulation> availableArticulations)
{
	mArticulations.clear();

	for (auto &articulation : availableArticulations)
	{
		String articulationString = articulationReverseMap.at(articulation);
		mArticulations.addItem(articulationString, static_cast<int>(articulation));
	}
}
