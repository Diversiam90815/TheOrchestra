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

	void				 setInstrument(const InstrumentProfile &instrument);
	void				 setPitchMode(PitchMode mode);

	void				 resized() override;

	int					 getPreferredHeight(int width) const override;

private:
	/*
	 @brief					Width of the fixed-ish range column at a given total
							width. Flexes so the qualities column keeps a usable
							measure on wide windows.
	*/
	int					 rangeColumnWidth(int width) const;

	RangesPanel			 mRanges;
	QualitiesPanel		 mQualities;

	static constexpr int kMinRangeWidth = 330;
	static constexpr int kMaxRangeWidth = 440;
	static constexpr int kColumnGap		= Space::xl;
	static constexpr int kPadX			= Space::xl;
	static constexpr int kPadY			= Space::l;
	static constexpr int kMinRangeHeight = 190;
};
