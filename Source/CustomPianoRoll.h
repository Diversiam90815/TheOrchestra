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


//Enum to identify the key used
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
    //==============================================================================
    //                          CONSTRUCTOR - DESTRUCTOR
    //==============================================================================

	CustomPianoRoll(MidiKeyboardState &state, Orientation orientation);

    ~CustomPianoRoll() = default;
    
    
    //==============================================================================
    //                          PUBLIC METHODS
    //==============================================================================

	void	   drawWhiteNote(int midiNoteNumber, Graphics &g, Rectangle<float> area, bool isDown, bool isOver, Colour lineColour, Colour textColour) override;

	void	   drawBlackNote(int midiNoteNumber, Graphics &g, Rectangle<float> area, bool isDown, bool isOver, Colour noteFillColour) override;

    /*
     @brief                 Turns the note name in accordance with the octave in form of E4, C3,.. to the corresponding midi note value.                          Middle C (C4) corresponds to a midi note value of 60.
     @param                 [IN] notename -> The name of the note and the octave -> E4, C6, C#2, Gb3,...
     @return                Midi note value as an int of the note given. If there an error occured, it returns -1.
    */
	static int turnNotenameIntoMidinumber(String notename);

    /*
     @brief                 Fills the vector 'mMidiRanges' with the note ranges information from a StringArray
     @param                 [IN] qualities as an StringArray.
     @return                Boolean indicating success/failure
    */
	bool	   setMidiRanges(const StringArray &qualities);

    /*
     @brief                 Fills the vector 'mMidiRanges' with the note ranges information from a String
     @param                 [IN] ranges as an String.
     @return                Boolean indicating success/failure
    */
	bool	   setMidiRanges(const String &ranges);

    
private:
    //==============================================================================
    //                          PRIVATE METHODS
    //==============================================================================

    /*
     @brief                 Returns the note color depending on the note midi value
     @param                 [IN] midiNoteNumber -> midi note value of the note (C4 = 60)
     @return                Colour of the note that should be used
    */
	Colour							 getNoteColour(int midiNoteNumber);

    
    //==============================================================================
    //                          PRIVATE OBJECTS
    //==============================================================================

	std::vector<std::pair<int, int>> mMidiRanges;           //Vector of the ranges (stored as pairs of int). This is used to draw different                                                          colours of notes

	Atomic<bool>					 mRangesSet		 = false;       //If true, the custom piano roll is being applied. This is set to true, if                                                               mMidiRanges will be filled

	Atomic<int>						 mCurrentKeyType = key::defaultKey;     //Indicating the current key type for drawing
    
	std::vector<Colour>				 qualityColours	 =
    {
		  Colours::lightblue.darker(), // For the first range
		  Colours::lightgreen,		   // For the second range
		  Colours::lightcoral,		   // For the third range
		  Colours::gold				   // Additional ranges, etc.
    };                                                              //Different colours used for the ranges of the different qualities
};
