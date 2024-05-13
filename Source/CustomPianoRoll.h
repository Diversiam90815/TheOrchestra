/*
  ==============================================================================

	CustomPianoRoll.h
	Created: 18 Apr 2024 3:58:09pm
	Author:  Jens.Langenberg

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "Parameters.h"

enum key
{
	default = 0,
	blackKey,
	whiteKey
};


class CustomPianoRoll : public MidiKeyboardComponent
{
public:
	CustomPianoRoll(MidiKeyboardState &state, Orientation orientation);

	void drawWhiteNote(int midiNoteNumber, Graphics &g, Rectangle<float> area, bool isDown, bool isOver, Colour lineColour, Colour textColour) override;

	void drawBlackNote(int midiNoteNumber, Graphics &g, Rectangle<float> area, bool isDown, bool isOver, Colour noteFillColour) override;

	int	 turnNotenameIntoMidinumber(String notename);

	bool setMidiRanges(const StringArray &qualities);

	bool setMidiRanges(const String &ranges);

private:
	Colour							 getNoteColour(int midiNoteNumber);

	std::vector<std::pair<int, int>> mMidiRanges;

	Atomic<bool>					 mRangesSet		 = false;

	Atomic<int>						 mCurrentKeyType = key::default;

	std::vector<Colour>				 qualityColours	 = {
		  Colours::lightblue.darker(), // For the first range
		  Colours::lightgreen,		   // For the second range
		  Colours::lightcoral,		   // For the third range
		  Colours::gold				   // Additional ranges, etc.
	  };
};
