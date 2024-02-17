/*
  ==============================================================================

    PianoRoll.cpp
    Created: 17 Feb 2024 2:40:46pm
    Author:  jerry

  ==============================================================================
*/

#include "PianoRoll.h"

PianoRoll::PianoRoll()
{
    mPianoState.addListener(this);

    mPianoRoll = std::make_unique<MidiKeyboardComponent>(mPianoState, MidiKeyboardComponent::horizontalKeyboard);

    showPianoRoll();
}


PianoRoll::~PianoRoll()
{
    mPianoState.removeListener(this);
}


void PianoRoll::resized()
{
    mPianoRoll->setBoundsRelative(0.0f, 0.0f, 1.0f, 1.0f);
}


void PianoRoll::showPianoRoll()
{
    mPianoRoll->setName("Piano Roll");
    addAndMakeVisible(mPianoRoll.get());
}


void PianoRoll::handleNoteOn(MidiKeyboardState*, int midiChannel, int midiNoteNumber, float velocity)
{

}


void PianoRoll::handleNoteOff(MidiKeyboardState*, int midiChannel, int midiNoteNumber, float velocity)
{

}