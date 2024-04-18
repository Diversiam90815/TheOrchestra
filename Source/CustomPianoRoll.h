/*
  ==============================================================================

    CustomPianoRoll.h
    Created: 18 Apr 2024 3:58:09pm
    Author:  Jens.Langenberg

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>


class CustomMidiKeyboardComponent : public MidiKeyboardComponent {
public:
    CustomMidiKeyboardComponent(MidiKeyboardState& state, Orientation orientation);

    void drawWhiteNote(int midiNoteNumber, Graphics& g, Rectangle<float> area,
        bool isDown, bool isOver, Colour lineColour, Colour textColour) override;

    void drawBlackNote(int midiNoteNumber, Graphics& g, Rectangle<float> area,
        bool isDown, bool isOver, Colour noteFillColour) override;

private:
    Colour getNoteColour(int midiNoteNumber);
};
