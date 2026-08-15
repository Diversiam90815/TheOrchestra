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


void NotationComponent::selectBestClef(Clef preferredClef)
{
	static constexpr Clef kAllClefs[] = { Clef::Treble, Clef::Bass, Clef::Alto, Clef::Tenor };

	constexpr int kPreferenceTolerance = 4;

	Clef		  best			= kAllClefs[0];
	int			  bestOverflow	= mRenderer.getLedgerOverflow(mNote.midiNoteNumber, best);

	for (Clef clef : kAllClefs)
	{
		const int overflow = mRenderer.getLedgerOverflow(mNote.midiNoteNumber, clef);
		if (overflow < bestOverflow)
		{
			best		 = clef;
			bestOverflow = overflow;
		}
	}

	const int preferredOverflow = mRenderer.getLedgerOverflow(mNote.midiNoteNumber, preferredClef);
	if (preferredOverflow <= bestOverflow + kPreferenceTolerance)
		best = preferredClef;

	mClef = best;
	repaint();
}
