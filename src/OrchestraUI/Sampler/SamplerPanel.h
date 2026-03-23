/*
  ==============================================================================
	Module			SamplerPanel
	Description		Articulation toggle button grid for sampler control
  ==============================================================================
*/

#pragma once

#include "OrchestraPanel.h"
#include "OrchestraSampler.h"

#include <functional>
#include <set>


using ArticulationChangedCallback = std::function<void(Articulation)>;


class SamplerPanel : public OrchestraPanel
{
public:
	SamplerPanel();
	~SamplerPanel() override = default;

	void setInstrument(const InstrumentProfile &instrument) override { /* Not used directly */ }

	void setAvailableArticulations(std::set<Articulation> available);
	void setArticulationChangedCallback(ArticulationChangedCallback callback);

	void resized() override;

private:
	void onArticulationClicked(Articulation articulation);

	std::vector<std::unique_ptr<juce::TextButton>> mButtons;
	std::set<Articulation>						   mAvailable;
	Articulation								   mSelected = Articulation::sustain;
	juce::Label									   mStatusLabel;

	ArticulationChangedCallback					   mCallback;
};
