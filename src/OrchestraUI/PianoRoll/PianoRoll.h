/*
  ==============================================================================
	Module			PianoRoll
	Description		Creating and managing piano roll and midi input
  ==============================================================================
*/

#pragma once
#include <assert.h>

#include "CustomPianoRoll.h"
#include "CustomComponent.h"


class PianoRoll : public CustomComponent, private juce::MidiKeyboardState::Listener, public juce::MidiInputCallback
{
public:
	PianoRoll() = default;
	~PianoRoll();

	void init() override;
	void displayInstrument(InstrumentInfo &info) override;

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
