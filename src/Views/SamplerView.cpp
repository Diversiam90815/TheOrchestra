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
	setSize(mWidth, mHeight);

	addAndConfigureLabel(mTitle, "SamplerViewTitle", "Articulations", mTitleX, mTitleY, mTitleWidth, mTitleHeight);

	addAndConfigureComboBox(mArticulations, mArticulationsX, mArticulationsY, mArticulationsWidth, mArticulationsHeight);
	mArticulations.onChange = [this]()
	{
		const int		   selectedID	   = mArticulations.getSelectedId();
		const Articulation newArticulation = static_cast<Articulation>(selectedID);
		articulationChanged(newArticulation);
	};
}


void SamplerView::displayInstrument(std::set<Articulation> availableArticulations)
{
	mArticulations.clear();

	for (auto &articulation : availableArticulations)
	{
		String articulationString = articulationReverseMap.at(articulation);
		mArticulations.addItem(articulationString, static_cast<int>(articulation));
	}
}


void SamplerView::articulationChanged(Articulation newArticulation)
{
}
