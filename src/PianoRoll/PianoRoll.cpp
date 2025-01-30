/*
  ==============================================================================

	Module			PianoRoll
	Description		Creating and managing piano roll and midi input

  ==============================================================================
*/

#include "PianoRoll.h"


PianoRoll::PianoRoll(MidiKeyboardState* state)
{
	pianoState = state;

	pianoState->addListener(this);

	mPianoRoll = std::make_unique<CustomPianoRoll>(*pianoState, MidiKeyboardComponent::horizontalKeyboard);

	showPianoRoll();
}


PianoRoll::~PianoRoll()
{
	mPianoRoll->removeAllChangeListeners();
	pianoState->removeListener(this);
	mPianoRoll.reset();
}


void PianoRoll::resized()
{
	mPianoRoll->setBoundsRelative(0.0f, 0.0f, 1.0f, 1.0f);
}


void PianoRoll::handleIncomingMidiMessage(MidiInput *source, const MidiMessage &message)
{

	pianoState->processNextMidiEvent(message);

	if (message.isNoteOn())
	{
		pianoState->noteOn(message.getChannel(), message.getNoteNumber(), message.getFloatVelocity());
	}

	else if (message.isNoteOff())
	{
		pianoState->noteOff(message.getChannel(), message.getNoteNumber(), message.getFloatVelocity());
	}
}


void PianoRoll::showPianoRoll()
{
	mPianoRoll->setName("Piano Roll");
	addAndMakeVisible(mPianoRoll.get());
}


void PianoRoll::handleNoteOn(MidiKeyboardState *, int midiChannel, int midiNoteNumber, float velocity) {}


void PianoRoll::handleNoteOff(MidiKeyboardState *, int midiChannel, int midiNoteNumber, float velocity) {}
