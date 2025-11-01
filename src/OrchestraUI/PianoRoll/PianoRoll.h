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


class PianoRoll : public CustomComponent, private MidiKeyboardState::Listener, public MidiInputCallback
{
public:
	PianoRoll() = default;
	~PianoRoll();

	void init() override;
	void displayInstrument(InstrumentInfo &info) override;

	void setKeyboardState(MidiKeyboardState &state);

private:
	void							 showPianoRoll();

	void							 resized() override;

	void							 handleIncomingMidiMessage(MidiInput *source, const MidiMessage &message) override;

	void							 handleNoteOn(MidiKeyboardState *, int midiChannel, int midiNoteNumber, float velocity) override {}

	void							 handleNoteOff(MidiKeyboardState *, int midiChannel, int midiNoteNumber, float velocity) override {}


	std::unique_ptr<CustomPianoRoll> mPianoRoll;
	MidiKeyboardState				*mPianoState = nullptr;
};
