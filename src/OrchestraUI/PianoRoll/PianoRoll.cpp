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


void PianoRoll::handleIncomingMidiMessage(juce::MidiInput *source, const juce::MidiMessage &message)
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

	mPianoRoll = std::make_unique<CustomPianoRoll>(*mPianoState, juce::MidiKeyboardComponent::horizontalKeyboard);
	showPianoRoll();
}


void PianoRoll::displayInstrument(InstrumentInfo &info)
{
	// Strategy 1: Rhythmic percussion uses displayedRange
	if (info.isRhythmicPercussion())
	{
		mPianoRoll->setMidiRanges(info.getRange());
		repaint();
		return;
	}

	// Strategy 2: Try to use qualities for color-coded ranges
	if (!info.getQualities().empty())
	{
		mPianoRoll->setMidiRanges(info.getQualities());
		repaint();
		return;
	}

	// Strategy 3: Fallback to full range (e.g., for strings)
	mPianoRoll->setMidiRanges(info.getRange());
	repaint();
}


void PianoRoll::setKeyboardState(juce::MidiKeyboardState &state)
{
	mPianoState = &state;
	mPianoState->addListener(this);
}


void PianoRoll::showPianoRoll()
{
	mPianoRoll->setName("Piano Roll");
	addAndMakeVisible(mPianoRoll.get());
}
