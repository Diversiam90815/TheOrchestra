/*
  ==============================================================================
	Module			NotationComponent
	Description		JUCE Component wrapper for NotationRenderer
  ==============================================================================
*/

#pragma once

#include "NotationRenderer.h"
#include "CustomComponent.h"


class NotationComponent : public CustomComponent
{
public:
	NotationComponent();
	~NotationComponent() = default;

	void init() override;

	void displayInstrument(InstrumentProfile &instrument) override;

private:
	void			 setNote(int midiNumber, Accidental accidental = Accidental::None);

	void			 setNoteFromString(const std::string &noteName);

	void			 setClef(Clef clef);

	void			 autoSelectClef();

	NotationRenderer mRenderer;
	NoteDescriptor	 mNote;
	Clef			 mClef = Clef::Treble;
};