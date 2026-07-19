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


class QualitiesPanel : public juce::Component
{
public:
	QualitiesPanel() = default;
	~QualitiesPanel() override = default;

	void setInstrument(const InstrumentProfile &instrument);
	void setPitchMode(PitchMode mode);

	void paint(juce::Graphics &g) override;

private:
	std::vector<juce::String> mDescriptions;
	bool					  mHasTransposition = false;
	PitchMode				  mPitchMode		= PitchMode::Written;
};
