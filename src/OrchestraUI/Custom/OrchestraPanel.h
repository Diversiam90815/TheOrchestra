/*
  ==============================================================================
	Module			OrchestraPanel
	Description		Base class for all UI panels in the redesigned layout.
					Replaces CustomComponent with a cleaner pattern:
					- No per-component LookAndFeel (inherits from parent)
					- No path accumulation bug (local path in paint)
					- Single setInstrument() replaces init() + displayInstrument()
					- Built-in section title rendering
  ==============================================================================
*/

#pragma once

#include "JuceIncludes.h"
#include "InstrumentInfo.h"


enum class PitchMode
{
	Written,
	Sounding
};


class OrchestraPanel : public juce::Component
{
public:
	explicit OrchestraPanel(const juce::String &title = "");
	~OrchestraPanel() override = default;

	void paint(juce::Graphics &g) override;

	virtual void setInstrument(const InstrumentProfile &instrument) = 0;

protected:
	juce::Rectangle<int> getContentArea() const;

	static constexpr int   kPadding		 = 16;
	static constexpr int   kTitleHeight	 = 24;
	static constexpr float kCornerRadius = 10.f;

private:
	juce::String mTitle;
};
