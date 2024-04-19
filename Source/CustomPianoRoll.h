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


class CustomPianoRoll : public MidiKeyboardComponent {
public:
    CustomPianoRoll(MidiKeyboardState& state, Orientation orientation);

    void drawWhiteNote(int midiNoteNumber, Graphics& g, Rectangle<float> area,
        bool isDown, bool isOver, Colour lineColour, Colour textColour) override;

    void drawBlackNote(int midiNoteNumber, Graphics& g, Rectangle<float> area,
        bool isDown, bool isOver, Colour noteFillColour) override;

    int turnNotenameIntoMidinumber(String notename);

    bool setMidiRanges(const StringArray& qualities);

    bool setMidiRanges(const String& ranges);

private:
    Colour getNoteColour(int midiNoteNumber);

    std::vector<std::pair<int, int>> mMidiRanges;

    //std::vector<Colour> mQualityColours = 
    //{
    //    Colours::lightblue,   // For the first range
    //    Colours::lightgreen,  // For the second range
    //    Colours::lightcoral,  // For the third range
    //    Colours::gold         // Additional ranges, etc.
    //};

    Atomic<bool> mRangesSet = false;
};
