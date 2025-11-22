/*
  ==============================================================================
	Module			NotationComponent
	Description		JUCE Component wrapper for NotationRenderer
  ==============================================================================
*/

#include "NotationComponent.h"


NotationComponent::NotationComponent()
{
	mNote.midiNoteNumber = 60; // Middle C
	mNote.accidental	 = Accidental::None;
	setSize(100, 80);
}


void NotationComponent::paint(juce::Graphics &g)
{
	// Fill background
	g.fillAll(juce::Colours::white);

	// Render the notation
	mRenderer.renderStaffWithNote(g, getLocalBounds(), mNote, mClef);
}


void NotationComponent::setNote(int midiNumber, Accidental accidental)
{
	mNote.midiNoteNumber = midiNumber;
	mNote.accidental	 = accidental;
	repaint();
}


void NotationComponent::setNoteFromString(const std::string &noteName)
{
	int midiNote = turnNotenameIntoMidinumber(noteName);

	if (midiNote == -1)
	{
		LOG_WARNING("Invalid note name: {}", noteName);
		return;
	}

	Accidental acc = Accidental::None;
	if (noteName.find("#") != std::string::npos)
		acc = Accidental::Sharp;

	else if (noteName.find("b") != std::string::npos)
		acc = Accidental::Flat;

	setNote(midiNote, acc);
	autoSelectClef(midiNote);
}


void NotationComponent::setClef(Clef clef)
{
	mClef = clef;
	repaint();
}


void NotationComponent::autoSelectClef(const int midiNoteNumber)
{
	// TOOD: REFINE CLEF HANDLING!

	// Heuristic for clef selection based on pitch range
	if (midiNoteNumber >= 55) // G3 and above
	{
		mClef = Clef::Treble;
	}
	else // Below G3
	{
		mClef = Clef::Bass;
	}
	repaint();
}
