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
#include <optional>
#include <set>


using ArticulationChangedCallback = std::function<bool(Articulation)>;


class SamplerPanel : public OrchestraPanel, public HasPreferredHeight
{
public:
	SamplerPanel();
	~SamplerPanel() override = default;

	void setInstrument(const InstrumentProfile &instrument) override { /* Not used directly */ }

	void setAvailableArticulations(std::set<Articulation> available);
	void setArticulationChangedCallback(ArticulationChangedCallback callback);

	void paint(juce::Graphics &g) override;
	void resized() override;

	int	 getPreferredHeight(int width) const override;

private:
	void										   onArticulationClicked(Articulation articulation);
	void										   updateStatus();

	int											   wrappedRowCount(int width) const;

	std::vector<std::unique_ptr<juce::TextButton>> mButtons;
	std::set<Articulation>						   mAvailable;
	Articulation								   mSelected = Articulation::sustain;
	juce::Label									   mStatusLabel;

	std::optional<Articulation>					   mLoadedArticulation;
	bool										   mSamplesReady = false;

	ArticulationChangedCallback					   mCallback;

	static constexpr int						   kButtonWidth	 = 128;
	static constexpr int						   kButtonHeight = 38;
	static constexpr int						   kGap			 = Space::s;
	static constexpr int						   kStatusHeight = 26;
	static constexpr float						   kDotSize		 = 9.0f;
};
