/*
  ==============================================================================
	Module			NotationComponent
	Description		JUCE Component wrapper for NotationRenderer
  ==============================================================================
*/

#pragma once

#include "NotationRenderer.h"


class NotationComponent : public juce::Component
{
public:
	NotationComponent();
	~NotationComponent() = default;

	void paint(juce::Graphics &g) override;

	void setNote(int midiNumber, Accidental accidental = Accidental::None);
	void setNoteFromString(const std::string &noteName);
	void setClef(Clef clef);
	void selectBestClef(Clef preferredClef);

private:
	NotationRenderer mRenderer;
	NoteDescriptor	 mNote;
	Clef			 mClef = Clef::Treble;
};
