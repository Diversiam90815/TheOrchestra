/*
  ==============================================================================

	Module			PianoRoll
	Description		Creating and managing piano roll and midi input

  ==============================================================================
*/

#include "PianoRoll.h"


PianoRoll::PianoRoll(MidiKeyboardState &state)
{
	mPianoState = &state;

	mPianoState->addListener(this);

	mPianoRoll = std::make_unique<CustomPianoRoll>(*mPianoState, MidiKeyboardComponent::horizontalKeyboard);

	showPianoRoll();
}


PianoRoll::~PianoRoll()
{
	mPianoRoll->removeAllChangeListeners();
	mPianoState->removeListener(this);
	mPianoRoll.reset();
}


void PianoRoll::resized()
{
	mPianoRoll->setBoundsRelative(0.0f, 0.0f, 1.0f, 1.0f);
}


void PianoRoll::handleIncomingMidiMessage(MidiInput *source, const MidiMessage &message)
{
	mPianoState->processNextMidiEvent(message);

	if (message.isNoteOn())
	{
		mPianoState->noteOn(message.getChannel(), message.getNoteNumber(), message.getFloatVelocity());
	}

	else if (message.isNoteOff())
	{
		mPianoState->noteOff(message.getChannel(), message.getNoteNumber(), message.getFloatVelocity());
	}
}


void PianoRoll::displayInstrumentRanges(InstrumentInfo &info)
{
	if (info.isRhythmicPercussion())
	{
		mPianoRoll->setMidiRanges(info.getDisplayedRange());
	}
	else
	{
		bool result = mPianoRoll->setMidiRanges(info.getQualities());
		if (!result)
		{
			mPianoRoll->setMidiRanges(info.getRange());
		}
	}

	repaint();
}


void PianoRoll::showPianoRoll()
{
	mPianoRoll->setName("Piano Roll");
	addAndMakeVisible(mPianoRoll.get());
}


void PianoRoll::handleNoteOn(MidiKeyboardState *, int midiChannel, int midiNoteNumber, float velocity) {}


void PianoRoll::handleNoteOff(MidiKeyboardState *, int midiChannel, int midiNoteNumber, float velocity) {}
