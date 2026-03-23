/*
  ==============================================================================
	Module			RangesPanel
	Description		Compact range display with notation, supporting written/sounding toggle
  ==============================================================================
*/

#pragma once

#include "OrchestraPanel.h"
#include "NotationComponent.h"


class RangesPanel : public OrchestraPanel
{
public:
	RangesPanel();
	~RangesPanel() override = default;

	void setInstrument(const InstrumentProfile &instrument) override;
	void resized() override;

	void setClef(Clef clef);
	void setPitchMode(PitchMode mode);

private:
	void updateDisplay();

	NotationComponent mLowNotation;
	NotationComponent mHighNotation;

	juce::Label		  mLowLabel;
	juce::Label		  mHighLabel;
	juce::Label		  mLowNoteName;
	juce::Label		  mHighNoteName;
	juce::Label		  mPitchModeLabel;

	// Stored instrument range data
	std::string		  mWrittenLow;
	std::string		  mWrittenHigh;
	std::string		  mSoundingLow;
	std::string		  mSoundingHigh;
	bool			  mHasTransposition = false;
	PitchMode		  mPitchMode		= PitchMode::Written;
};
