/*
  ==============================================================================
	Module			SamplerView
	Description		View box containing sampler information
  ==============================================================================
*/

#include "SamplerView.h"


void SamplerView::init()
{
	setSize(mWidth, mHeight);

	addAndConfigureLabel(mTitle, "SamplerViewTitle", "Articulations", mTitleX, mTitleY, mTitleWidth, mTitleHeight);

	addAndConfigureComboBox(mArticulations, mArticulationsX, mArticulationsY, mArticulationsWidth, mArticulationsHeight);
	mArticulations.setTextWhenNoChoicesAvailable(textIfNoSamplesAvailable);
	mArticulations.onChange = [this]()
	{
		const int		   selectedID	   = mArticulations.getSelectedId();
		const Articulation newArticulation = static_cast<Articulation>(selectedID);
		if (mArticulationChangedCallback)
		{
			mArticulationChangedCallback(newArticulation);
		}
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


void SamplerView::setArticulationChangedCallback(ArticulationChangedCallback callback)
{
	mArticulationChangedCallback = callback;
}
