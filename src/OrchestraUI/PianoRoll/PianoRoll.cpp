/*
  ==============================================================================
	Module			PianoRoll
	Description		Creating and managing piano roll and midi input
  ==============================================================================
*/

#include "PianoRoll.h"


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


void PianoRoll::init()
{
	if (!mPianoState)
		assert(false); // PianoState should be set before call init!

	mPianoRoll = std::make_unique<CustomPianoRoll>(*mPianoState, MidiKeyboardComponent::horizontalKeyboard);
	showPianoRoll();
}


void PianoRoll::displayInstrument(InstrumentInfo &info)
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


void PianoRoll::setKeyboardState(MidiKeyboardState &state)
{
	mPianoState = &state;
	mPianoState->addListener(this);
}


void PianoRoll::showPianoRoll()
{
	mPianoRoll->setName("Piano Roll");
	addAndMakeVisible(mPianoRoll.get());
}
