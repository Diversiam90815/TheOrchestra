/*
  ==============================================================================
	Module			FamousWorksPanel
	Description		Panel displaying famous works featuring the instrument, as a
					wrapped multi-column card grid.
  ==============================================================================
*/

#pragma once

#include "OrchestraPanel.h"


class FamousWorksPanel : public OrchestraPanel, public HasPreferredHeight
{
public:
	FamousWorksPanel();
	~FamousWorksPanel() override = default;

	void paint(juce::Graphics &g) override;
	void setInstrument(const InstrumentProfile &instrument) override;

	int	 getPreferredHeight(int width) const override;

private:
	struct WorkData
	{
		juce::String composer;
		juce::String title;
	};

	std::vector<int>	  cellHeights(int width) const;

	std::vector<WorkData> mWorks;

	static constexpr int  kMinColumnWidth = 340;
	static constexpr int  kMaxColumns	  = 3;
	static constexpr int  kGap			  = Space::l;
	static constexpr int  kComposerHeight = 22;
	static constexpr int  kMinCellHeight  = 68;
};
