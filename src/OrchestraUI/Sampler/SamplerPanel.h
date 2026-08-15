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


class SamplerPanel : public OrchestraPanel, public HasPreferredHeight
{
public:
	SamplerPanel();
	~SamplerPanel() override = default;

	void				 setInstrument(const InstrumentProfile &instrument) override { /* Not used directly */ }

	void				 setAvailableArticulations(std::set<Articulation> available);
	void				 setArticulationChangedCallback(ArticulationChangedCallback callback);

	void				 resized() override;

	int					 getPreferredHeight(int width) const override;

private:
	void				 onArticulationClicked(Articulation articulation);

	/*
	 @brief					Rows the articulation buttons wrap into at a width.
							The panel used to be a fixed 96px, which left 40px of
							content for a 32px button row plus an 18px status
							label - they overlapped, and a second row was
							impossible. Height now follows the wrap.
	*/
	int					 wrappedRowCount(int width) const;

	std::vector<std::unique_ptr<juce::TextButton>> mButtons;
	std::set<Articulation>						   mAvailable;
	Articulation								   mSelected = Articulation::sustain;
	juce::Label									   mStatusLabel;

	ArticulationChangedCallback					   mCallback;

	static constexpr int						   kButtonWidth	 = 116;
	static constexpr int						   kButtonHeight = 36;
	static constexpr int						   kGap			 = Space::s;
	static constexpr int						   kStatusHeight = 22;
};
