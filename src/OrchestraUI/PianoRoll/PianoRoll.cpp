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
	if (!mPianoRoll)
		return;

	mPianoRoll->setBounds(getLocalBounds());
	mPianoRoll->fitKeysToWidth();
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


void PianoRoll::displayInstrument(InstrumentProfile &info)
{
	// Strategy 1: Rhythmic percussion uses displayedRange
	if (info.isRhythmicPercussion())
	{
		mPianoRoll->setMidiRanges(info.getRange());
		resized();
		repaint();
		return;
	}

	// Strategy 2: Try to use registers for color-coded ranges.
	// Registers hold written-pitch values, so the playable span is taken from
	// the written range to match. They do not always partition it - a violin's
	// registers are its four open strings inside a much wider range.
	if (!info.getRegisters().empty())
	{
		auto range = info.getRange();
		mPianoRoll->setPlayableRange(range.getWrittenLowNoteAsMidiValue(), range.getWrittenHighNoteAsMidiValue());
		mPianoRoll->setMidiRanges(info.getRegisters());
		resized();
		repaint();
		return;
	}

	// Strategy 3: Fallback to full range (e.g., for strings)
	mPianoRoll->setMidiRanges(info.getRange());
	resized();
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
