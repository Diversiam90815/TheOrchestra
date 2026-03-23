/*
  ==============================================================================
	Module			OrchestraPanel
	Description		Base class for all UI panels.
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
	void setTitle(const juce::String &newTitle) { mTitle = newTitle; }

	static constexpr int   kPadding		 = 16;
	static constexpr int   kTitleHeight	 = 24;
	static constexpr float kCornerRadius = 10.f;

private:
	juce::String mTitle;
};
