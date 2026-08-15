/*
  ==============================================================================
	Module			PianoRoll
	Description		Creating and managing piano roll and midi input
  ==============================================================================
*/

#pragma once
#include <assert.h>

#include "CustomPianoRoll.h"


// Derives from juce::Component directly: the old CustomComponent base called
// setLookAndFeel() with its own CustomLookAndFeel instance, which hijacked the
// LookAndFeel for this whole subtree and stopped themeFor() resolving the
// editor's theme.
class PianoRoll : public juce::Component, private juce::MidiKeyboardState::Listener, public juce::MidiInputCallback
{
public:
	PianoRoll() = default;
	~PianoRoll();

	void init();
	void displayInstrument(InstrumentProfile &info);

	void setKeyboardState(juce::MidiKeyboardState &state);

private:
	void							 showPianoRoll();

	void							 resized() override;

	void							 handleIncomingMidiMessage(juce::MidiInput *source, const juce::MidiMessage &message) override;

	void							 handleNoteOn(juce::MidiKeyboardState *, int midiChannel, int midiNoteNumber, float velocity) override {}

	void							 handleNoteOff(juce::MidiKeyboardState *, int midiChannel, int midiNoteNumber, float velocity) override {}


	std::unique_ptr<CustomPianoRoll> mPianoRoll;
	juce::MidiKeyboardState			*mPianoState = nullptr;
};
