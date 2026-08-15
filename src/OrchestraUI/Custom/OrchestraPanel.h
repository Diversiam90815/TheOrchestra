/*
  ==============================================================================
	Module			OrchestraPanel
	Description		Base class for all UI panels.
  ==============================================================================
*/

#pragma once

#include "JuceIncludes.h"
#include "InstrumentInfo.h"
#include "Theme.h"


enum class PitchMode
{
	Written,
	Sounding
};


struct HasPreferredHeight
{
	virtual ~HasPreferredHeight()					= default;

	virtual int getPreferredHeight(int width) const = 0;
};


class OrchestraPanel : public juce::Component
{
public:
	explicit OrchestraPanel(const juce::String &title = "");
	~OrchestraPanel() override = default;

	void		 paint(juce::Graphics &g) override;

	virtual void setInstrument(const InstrumentProfile &instrument) = 0;

protected:
	juce::Rectangle<int> getContentArea() const;

	int					 getChromeHeight() const;

	static constexpr int kPadding	  = Space::l + Space::xs;
	static constexpr int kTitleHeight = 22;
	static constexpr int kTitleGap	  = Space::m;

private:
	juce::String mTitle;
};
