/*
  ==============================================================================
	Module			PianoRollWithCc
	Description		Layout container that places the PianoRoll next to a MIDI-CC gutter
  ==============================================================================
*/

#pragma once

#include <functional>
#include <vector>

#include "JuceIncludes.h"
#include "PianoRoll.h"
#include "MidiCcGutter.h"
#include "InstrumentInfo.h"


class PianoRollWithCc : public juce::Component
{
public:
	PianoRollWithCc();
	~PianoRollWithCc() override = default;

	void	   setKeyboardState(juce::MidiKeyboardState &state);
	void	   initPianoRoll();
	void	   displayInstrument(const InstrumentProfile &instrument);

	// Wire the CC gutter to the engine (send + reflect).
	void	   setCcCallbacks(std::function<void(int, int)> onSend, std::function<int(int)> provider);

	// The underlying PianoRoll implements juce::MidiInputCallback (used by the app for MIDI-in).
	PianoRoll &getPianoRoll() { return mPianoRoll; }

	void	   paint(juce::Graphics &g) override;
	void	   resized() override;

private:
	struct LegendEntry
	{
		juce::Colour colour;
		juce::String note;
	};

	MidiCcGutter			 mCcGutter;
	PianoRoll				 mPianoRoll;
	std::vector<LegendEntry> mLegend;

	static constexpr int	 kHeaderH	= 24;
	static constexpr int	 kGutterGap = 14;
};
