/*
  ==============================================================================

	Module			CustomPianoRoll
	Description		Creating our own custom piano roll, which displays the instrument's individual ranges

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "Parameters.h"
#include "CustomLookAndFeel.h"
#include "Helper.h"


// Enum to identify the key used
enum key
{
	defaultKey = 0,
	blackKey,
	whiteKey
};


/*
 @brief                 Creating our own Piano Roll in order to display the instrument quality ranges with different colours on the Piano Roll
*/
class CustomPianoRoll : public MidiKeyboardComponent
{
public:
	CustomPianoRoll(MidiKeyboardState &state, Orientation orientation);

	~CustomPianoRoll() = default;

	/*
	 @brief                 Fills the vector 'mMidiRanges' with the note ranges information from a StringArray
	 @param                 [IN] qualities as an StringArray.
	 @return                Boolean indicating success/failure
	*/
	bool setMidiRanges(const StringArray &qualities);

	/*
	 @brief                 Fills the vector 'mMidiRanges' with the note ranges information from a String
	 @param                 [IN] ranges as an String.
	 @return                Boolean indicating success/failure
	*/
	bool setMidiRanges(const String &ranges);


private:
	Colour							 getNoteColour(int midiNoteNumber);

	void							 drawWhiteNote(int midiNoteNumber, Graphics &g, Rectangle<float> area, bool isDown, bool isOver, Colour lineColour, Colour textColour) override;

	void							 drawBlackNote(int midiNoteNumber, Graphics &g, Rectangle<float> area, bool isDown, bool isOver, Colour noteFillColour) override;

	std::vector<std::pair<int, int>> mMidiRanges;						// Vector of the ranges (stored as pairs of int). This is used to draw different colours of notes

	Atomic<bool>					 mRangesSet		 = false;			// If true, the custom piano roll is being applied. This is set to true, if mMidiRanges will be filled

	Atomic<int>						 mCurrentKeyType = key::defaultKey; // Indicating the current key type for drawing

	CustomLookAndFeel				 mCustomLookAndFeel;
};
