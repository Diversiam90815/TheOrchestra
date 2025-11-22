/*
  ==============================================================================
	Module			NotationRenderer
	Description		Renders musical notation
  ==============================================================================
*/

#pragma once

#include "JuceIncludes.h"
#include <NotationFontData>

#include "Logging.h"


enum class Clef
{
	Treble,
	Bass,
	Alto,
	Tenor,
};

enum class Accidental
{
	None,
	Sharp,
	Flat,
	Natural,
	DoubleSharp,
	DoubleFlat,
};


struct NoteDescriptor
{
	int		   midiNoteNumber  = 60; // Middle C = 60
	Accidental accidental	   = Accidental::None;
	bool	   showLedgerLines = false;

	NoteDescriptor()		   = default;
	NoteDescriptor(const int midi, Accidental acc = Accidental::None) : midiNoteNumber(midi), accidental(acc) {}
};


class NotationRenderer
{
public:
	NotationRenderer();
	~NotationRenderer() = default;

	void						renderStaffWithNote(juce::Graphics &g, juce::Rectangle<int> bounds, const NoteDescriptor &note, Clef clef = Clef::Treble);

	void						setStafflineColour(juce::Colour colour);

	void						setNoteColour(juce::Colour colour);

	static juce::Rectangle<int> getRecommendedBounds();

private:
	void				 loadNotationFont();

	void				 drawStaff(juce::Graphics &g, juce::Rectangle<float> staffArea);

	void				 drawClef(juce::Graphics &g, juce::Rectangle<float> staffArea, Clef clef);

	void				 drawNote(juce::Graphics &g, juce::Rectangle<float> staffArea, const NoteDescriptor &note, Clef clef);

	void				 drawLedgerLines(juce::Graphics &g, juce::Rectangle<float> staffArea, int staffPosition, float noteX);

	void				 drawAccidental(juce::Graphics &g, float x, float y, Accidental accidental);

	int					 midiNoteToStaffPosition(const int midiNote, Clef clef);

	float				 staffPositionToY(int staffPosition, juce::Rectangle<float> staffArea) const;

	juce::String		 getSMuFLCharacter(const juce::String &glyphname);


	juce::Font			 mNotationFont;
	juce::Colour		 mStaffLineColor			 = juce::Colour(0xff000000);
	juce::Colour		 mNoteColor					 = juce::Colour(0xff000000);

	const float			 mStaffLineSpacing			 = 10.0f; // Space between staff lines in px
	const float			 mStaffLineThickness		 = 1.5f;

															  // SMuFL codepoints (Bravura font)
	static constexpr int kGlyphNoteheadBlack		 = 0xE0A4;
	static constexpr int kGlyphNoteheadHalf			 = 0xE0A3;
	static constexpr int kGlyphNoteheadWhole		 = 0xE0A2;
	static constexpr int kGlyphClefG				 = 0xE050; // Treble clef
	static constexpr int kGlyphClefF				 = 0xE062; // Bass clef
	static constexpr int kGlyphClefC				 = 0xE05C; // Alto/Tenor clef
	static constexpr int kGlyphAccidentalSharp		 = 0xE262;
	static constexpr int kGlyphAccidentalFlat		 = 0xE260;
	static constexpr int kGlyphAccidentalNatural	 = 0xE261;
	static constexpr int kGlyphAccidentalDoubleSharp = 0xE263;
	static constexpr int kGlyphAccidentalDoubleFlat	 = 0xE264;
};
