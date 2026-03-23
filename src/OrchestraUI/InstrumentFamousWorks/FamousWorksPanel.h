/*
  ==============================================================================
	Module			FamousWorksPanel
	Description		Panel displaying famous works featuring the instrument
  ==============================================================================
*/

#pragma once

#include "OrchestraPanel.h"


class FamousWorksPanel : public OrchestraPanel
{
public:
	FamousWorksPanel();
	~FamousWorksPanel() override = default;

	void paint(juce::Graphics &g) override;
	void setInstrument(const InstrumentProfile &instrument) override;

private:
	struct WorkData
	{
		juce::String composer;
		juce::String title;
	};

	std::vector<WorkData> mWorks;

	static constexpr int kEntryHeight = 42;
};
