/*
  ==============================================================================
	Module			OverviewPanel
	Description		Overview tab body: range staves & qualities.
  ==============================================================================
*/

#pragma once

#include "JuceIncludes.h"

#include "RangesPanel.h"
#include "QualitiesPanel.h"
#include "InstrumentInfo.h"


class OverviewPanel : public juce::Component, public HasPreferredHeight
{
public:
	OverviewPanel();
	~OverviewPanel() override = default;

	void setInstrument(const InstrumentProfile &instrument);
	void setPitchMode(PitchMode mode);
	void setClef(Clef clef);

	void resized() override;

	int	 getPreferredHeight(int width) const override;

private:
	int					 rangeColumnWidth(int width) const;

	RangesPanel			 mRanges;
	QualitiesPanel		 mQualities;

	static constexpr int kMinRangeWidth	 = 350;
	static constexpr int kMaxRangeWidth	 = 460;
	static constexpr int kColumnGap		 = Space::xl;
	static constexpr int kPadX			 = Space::xl;
	static constexpr int kPadY			 = Space::l;
	static constexpr int kMinRangeHeight = 210;
};
