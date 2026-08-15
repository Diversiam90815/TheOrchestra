/*
  ==============================================================================
	Module			QualitiesPanel
	Description		The "QUALITIES" list from the Overview tab: colored swatches +
					register descriptions
  ==============================================================================
*/

#pragma once

#include "OrchestraPanel.h"
#include "InstrumentInfo.h"

#include <vector>


class QualitiesPanel : public juce::Component, public HasPreferredHeight
{
public:
	QualitiesPanel()		   = default;
	~QualitiesPanel() override = default;

	void setInstrument(const InstrumentProfile &instrument);
	void setPitchMode(PitchMode mode);

	void paint(juce::Graphics &g) override;

	int	 getPreferredHeight(int width) const override;

private:
	std::vector<int>		  rowHeights(int width) const;

	std::vector<juce::String> mDescriptions;
	bool					  mHasTransposition = false;
	PitchMode				  mPitchMode		= PitchMode::Written;

	static constexpr int	  kHeaderHeight		= 24;
	static constexpr int	  kSwatch			= 11;
	static constexpr int	  kTextInset		= Space::xl + Space::xs;
	static constexpr int	  kRowGap			= Space::m;
	static constexpr int	  kMinRowHeight		= 26;
};
