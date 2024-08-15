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

	mPianoRoll = std::make_unique<CustomPianoRoll>(mPianoState, MidiKeyboardComponent::horizontalKeyboard);

	showPianoRoll();
	setMidiInput(7);
	
	mDeviceManager.initialise(2, 2, nullptr, true, "", &mAudioSetup);
}


PianoRoll::~PianoRoll()
{
	mPianoRoll->removeAllChangeListeners();
	mPianoState.removeListener(this);
	mPianoRoll.reset();
}


void PianoRoll::resized()
{
	mPianoRoll->setBoundsRelative(0.0f, 0.0f, 1.0f, 1.0f);
}


void PianoRoll::handleIncomingMidiMessage(MidiInput *source, const MidiMessage &message)
{
	if (message.isNoteOn())
	{
		mPianoState.noteOn(message.getChannel(), message.getNoteNumber(), message.getFloatVelocity());
	}

	else if (message.isNoteOff())
	{
		mPianoState.noteOff(message.getChannel(), message.getNoteNumber(), message.getFloatVelocity());
	}
}


void PianoRoll::setMidiInput(int index)
{
	auto list = juce::MidiInput::getAvailableDevices();

	auto newInput = list[index];

	if (!mDeviceManager.isMidiInputDeviceEnabled(newInput.identifier))
	{
		mDeviceManager.setMidiInputDeviceEnabled(newInput.identifier, true);
	}

	mDeviceManager.addMidiInputDeviceCallback(newInput.identifier, this);
}


void PianoRoll::showPianoRoll()
{
	mPianoRoll->setName("Piano Roll");
	addAndMakeVisible(mPianoRoll.get());
}


void PianoRoll::handleNoteOn(MidiKeyboardState *, int midiChannel, int midiNoteNumber, float velocity)
{
	int i = 0;
}


void PianoRoll::handleNoteOff(MidiKeyboardState *, int midiChannel, int midiNoteNumber, float velocity)
{
	int i = 0;
}
