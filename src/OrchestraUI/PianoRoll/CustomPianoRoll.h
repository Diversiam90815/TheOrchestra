/*
  ==============================================================================
	Module			CustomPianoRoll
	Description		Creating our own custom piano roll, which displays the instrument's individual ranges
  ==============================================================================
*/

#pragma once

#include "JuceIncludes.h"
#include "Parameters.h"
#include "CustomLookAndFeel.h"
#include "Helper.h"
#include "InstrumentInfo.h"


// Enum to identify the key used
enum PianoKey
{
	defaultKey = 0,
	blackKey,
	whiteKey
};


/*
 @brief                 Creating our own Piano Roll in order to display the instrument quality ranges with different colours on the Piano Roll
*/
class CustomPianoRoll : public juce::MidiKeyboardComponent
{
public:
	CustomPianoRoll(juce::MidiKeyboardState &state, juce::KeyboardComponentBase::Orientation orientation);
	~CustomPianoRoll() = default;

	/*
	 @brief                 Fills the vector 'mMidiRanges' with the note ranges information from a StringArray
	 @param                 [IN] qualities as an StringArray.
	 @return                Boolean indicating success/failure
	*/
	bool setMidiRanges(const RegisterQualities &qualities);

	/*
	 @brief                 Fills the vector 'mMidiRanges' with the note ranges information from a String
	 @param                 [IN] ranges as an String.
	 @return                Boolean indicating success/failure
	*/
	bool setMidiRanges(const InstrumentRange &ranges);


private:
	juce::Colour getNoteColour(int midiNoteNumber);

	void drawWhiteNote(int midiNoteNumber, juce::Graphics &g, juce::Rectangle<float> area, bool isDown, bool isOver, juce::Colour lineColour, juce::Colour textColour) override;

	void drawBlackNote(int midiNoteNumber, juce::Graphics &g, juce::Rectangle<float> area, bool isDown, bool isOver, juce::Colour noteFillColour) override;

	std::vector<std::pair<int, int>> mMidiRanges;							 // Vector of the ranges (stored as pairs of int). This is used to draw different colours of notes

	std::atomic<bool>				 mRangesSet		 = false;				 // If true, the custom piano roll is being applied. This is set to true, if mMidiRanges will be filled

	std::atomic<int>				 mCurrentKeyType = PianoKey::defaultKey; // Indicating the current key type for drawing

	CustomLookAndFeel				 mCustomLookAndFeel;
};
