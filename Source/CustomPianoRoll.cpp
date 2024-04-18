/*
  ==============================================================================

    CustomPianoRoll.cpp
    Created: 18 Apr 2024 3:58:09pm
    Author:  Jens.Langenberg

  ==============================================================================
*/

#include "CustomPianoRoll.h"

CustomMidiKeyboardComponent::CustomMidiKeyboardComponent(MidiKeyboardState& state, Orientation orientation)
    : MidiKeyboardComponent(state, orientation)
{
}


void CustomMidiKeyboardComponent::drawWhiteNote(int midiNoteNumber, Graphics& g, Rectangle<float> area,
    bool isDown, bool isOver, Colour lineColour, Colour textColour)
{
    // Set the custom color based on the MIDI note number
    Colour noteColour = getNoteColour(midiNoteNumber);
    g.setColour(isDown ? noteColour.brighter() : noteColour);
    g.setColour(isOver ? noteColour.brighter() : noteColour);
    g.fillRect(area);

    // Draw the outline for the white note to maintain the separators
    g.setColour(lineColour);
    g.drawRect(area);

    // Optionally, you can also draw the note number or other markers
}


void CustomMidiKeyboardComponent::drawBlackNote(int midiNoteNumber, Graphics& g, Rectangle<float> area,
    bool isDown, bool isOver, Colour noteFillColour) 
{
    // Call the base class method to retain the default drawing of black notes
    MidiKeyboardComponent::drawBlackNote(midiNoteNumber, g, area, isDown,
        isOver, noteFillColour);
}


Colour CustomMidiKeyboardComponent::getNoteColour(int midiNoteNumber)
{
    if (midiNoteNumber < 60) // C4 and below
        return Colours::lightblue;
    else if (midiNoteNumber < 72) // C4 to B4
        return Colours::lightgreen;
    else // C5 and above
        return Colours::lightcoral;
}

