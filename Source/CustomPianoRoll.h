/*
  ==============================================================================

    CustomPianoRoll.h
    Created: 18 Apr 2024 3:58:09pm
    Author:  Jens.Langenberg

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
class CustomMidiKeyboardComponent : public juce::MidiKeyboardComponent {
public:
    CustomMidiKeyboardComponent(juce::MidiKeyboardState& state, Orientation orientation)
        : juce::MidiKeyboardComponent(state, orientation) {}

    void drawWhiteNote(int midiNoteNumber, juce::Graphics& g, juce::Rectangle<float> area,
        bool isDown, bool isOver, juce::Colour lineColour, juce::Colour textColour) override {
        // Set the custom color based on the MIDI note number
        juce::Colour noteColour = getNoteColour(midiNoteNumber);
        g.setColour(isDown ? noteColour.brighter() : noteColour);
        g.setColour(isOver ? noteColour.brighter() : noteColour);
        g.fillRect(area);

        // Draw the outline for the white note to maintain the separators
        g.setColour(lineColour);
        g.drawRect(area);

        // Optionally, you can also draw the note number or other markers
    }

    void drawBlackNote(int midiNoteNumber, juce::Graphics& g, juce::Rectangle<float> area,
        bool isDown, bool isOver, juce::Colour noteFillColour) override {
        // Call the base class method to retain the default drawing of black notes
        juce::MidiKeyboardComponent::drawBlackNote(midiNoteNumber, g, area, isDown,
            isOver, noteFillColour);
    }

private:
    juce::Colour getNoteColour(int midiNoteNumber) {
        if (midiNoteNumber < 60) // C4 and below
            return juce::Colours::lightblue;
        else if (midiNoteNumber < 72) // C4 to B4
            return juce::Colours::lightgreen;
        else // C5 and above
            return juce::Colours::lightcoral;
    }
};
