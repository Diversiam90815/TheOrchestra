/*
  ==============================================================================

	PianoRoll.h
	Created: 17 Feb 2024 2:40:46pm
	Author:  jerry

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"
#include "CustomPianoRoll.h"

class PianoRoll : public Component, private MidiKeyboardState::Listener
{
public:

	PianoRoll();
	~PianoRoll();

private:

	void showPianoRoll();

	void resized() override;

	void handleNoteOn(MidiKeyboardState*, int midiChannel, int midiNoteNumber, float velocity) override;

	void handleNoteOff(MidiKeyboardState*, int midiChannel, int midiNoteNumber, float velocity) override;

	int turnNotenameIntoMidinumber(String& notename);

	std::vector<std::pair<int, int>> getMidiRanges(const StringArray& qualities);

	std::unique_ptr<CustomMidiKeyboardComponent> mPianoRoll;
	MidiKeyboardState mPianoState;
};