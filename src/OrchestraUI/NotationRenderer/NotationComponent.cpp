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
	setSize(152, 116);
}


void NotationComponent::paint(juce::Graphics &g)
{
	// Transparent background - inherits panel colour
	g.fillAll(juce::Colours::transparentBlack);

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
}


void NotationComponent::setClef(Clef clef)
{
	mClef = clef;
	repaint();
}


void NotationComponent::autoSelectClef(const int midiNoteNumber)
{
	// Auto-select clef so the note sits comfortably on the staff
	// without excessive ledger lines.
	// B3 (MIDI 59) and below → Bass clef
	// C4 (MIDI 60, middle C) and above → Treble clef
	// This is the standard split point used in grand staff notation.
	if (midiNoteNumber >= 60)
		mClef = Clef::Treble;
	else
		mClef = Clef::Bass;

	repaint();
}
