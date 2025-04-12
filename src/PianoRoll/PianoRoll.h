/*
  ==============================================================================

	Module			PianoRoll
	Description		Creating and managing piano roll and midi input

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"
#include "CustomPianoRoll.h"
#include "Logging.h"


class PianoRoll : public Component, private MidiKeyboardState::Listener, public MidiInputCallback
{
public:
	PianoRoll(MidiKeyboardState *state);
	~PianoRoll();

	std::unique_ptr<CustomPianoRoll> mPianoRoll;

	void							 displayInstrumentRanges(InstrumentInfo &info);

private:
	void			   showPianoRoll();

	void			   resized() override;

	void			   handleIncomingMidiMessage(MidiInput *source, const MidiMessage &message) override;

	void			   handleNoteOn(MidiKeyboardState *, int midiChannel, int midiNoteNumber, float velocity) override;

	void			   handleNoteOff(MidiKeyboardState *, int midiChannel, int midiNoteNumber, float velocity) override;


	MidiKeyboardState *pianoState;
};
