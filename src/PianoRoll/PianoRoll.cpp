/*
  ==============================================================================

	Module			PianoRoll
	Description		Creating and managing piano roll and midi input

  ==============================================================================
*/

#include "PianoRoll.h"


PianoRoll::PianoRoll()
{
	mPianoState.addListener(this);

	mPianoRoll = std::make_unique<CustomPianoRoll>(mPianoState, MidiKeyboardComponent::horizontalKeyboard);

	showPianoRoll();
	setMidiInput();

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


void PianoRoll::setMidiInput()
{
	auto list = juce::MidiInput::getAvailableDevices();

	for (const auto &midiInput : list)
	{
		if (!mDeviceManager.isMidiInputDeviceEnabled(midiInput.identifier))
		{
			mDeviceManager.setMidiInputDeviceEnabled(midiInput.identifier, true);
		}

		mDeviceManager.addMidiInputDeviceCallback(midiInput.identifier, this);
	}
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
