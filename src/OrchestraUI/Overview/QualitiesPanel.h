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

	void					  setInstrument(const InstrumentProfile &instrument);
	void					  setPitchMode(PitchMode mode);

	void					  paint(juce::Graphics &g) override;

	int						  getPreferredHeight(int width) const override;

private:
	// Register descriptions run to 209 characters; each row wraps and the row
	// height follows the measured text rather than a fixed 20px line.
	std::vector<int>		  rowHeights(int width) const;

	std::vector<juce::String> mDescriptions;
	bool					  mHasTransposition = false;
	PitchMode				  mPitchMode		= PitchMode::Written;

	static constexpr int	  kHeaderHeight	 = 22;
	static constexpr int	  kSwatch		 = 10;
	static constexpr int	  kTextInset	 = Space::xl;
	static constexpr int	  kRowGap		 = Space::m;
	static constexpr int	  kMinRowHeight	 = 24;
};
