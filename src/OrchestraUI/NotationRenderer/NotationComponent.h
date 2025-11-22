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

	/**
	 * @brief Sets the note to display.
	 */
	void setNote(int midiNumber, Accidental accidental = Accidental::None);

	/**
	 * @brief Sets the note from a note name string (e.g., "C4", "F#5", "Bb3").
	 */
	void setNoteFromString(const std::string &noteName);

	/**
	 * @brief Sets the clef to use.
	 */
	void setClef(Clef clef);

	/**
	 * @brief Determines clef based on note. Currently just determines between Treble & Bass
	 */
	void autoSelectClef(const int midiNoteNumber);

private:
	NotationRenderer mRenderer;
	NoteDescriptor	 mNote;
	Clef			 mClef = Clef::Treble;
};