/*
  ==============================================================================
	Module			PianoRoll
	Description		Creating and managing piano roll and midi input
  ==============================================================================
*/

#include "PianoRoll.h"
#include "Logging.h"


PianoRoll::~PianoRoll()
{
	if (mPianoRoll)
		mPianoRoll->removeAllChangeListeners();

	if (mPianoState)
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
	if (!mPianoState)
		return;

	mPianoState->processNextMidiEvent(message);
}


void PianoRoll::init()
{
	jassert(mPianoState != nullptr); // PianoState should be set before calling init!

	if (!mPianoState)
	{
		LOG_ERROR("PianoRoll::init called before setKeyboardState - piano roll will not be created.");
		return;
	}

	mPianoRoll = std::make_unique<CustomPianoRoll>(*mPianoState, juce::MidiKeyboardComponent::horizontalKeyboard);
	showPianoRoll();
}


void PianoRoll::displayInstrument(const InstrumentProfile &info)
{
	if (!mPianoRoll)
		return;

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
		const auto &range = info.getRange();
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
