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


class OverviewPanel : public juce::Component
{
public:
	OverviewPanel();
	~OverviewPanel() override = default;

	void setInstrument(const InstrumentProfile &instrument);
	void setPitchMode(PitchMode mode);

	void resized() override;

private:
	RangesPanel	   mRanges;
	QualitiesPanel mQualities;

	static constexpr int kRangeWidth = 330;
	static constexpr int kColumnGap	 = 24;
	static constexpr int kPadX		 = 26;
	static constexpr int kPadY		 = 18;
};
