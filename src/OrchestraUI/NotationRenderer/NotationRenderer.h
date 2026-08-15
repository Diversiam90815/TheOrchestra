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

Clef clefFromString(const std::string &name);

enum class Accidental
{
	None,
	Sharp,
	Flat,
	Natural,
	DoubleSharp,
	DoubleFlat,
};

enum class OttavaType
{
	None,
	Ottava8va,	// 8va  - display note one octave lower than actual
	Ottava8vb,	// 8vb  - display note one octave higher than actual
	Ottava15ma, // 15ma - display note two octaves lower than actual
	Ottava15mb, // 15mb - display note two octaves higher than actual
};


struct NoteDescriptor
{
	int		   midiNoteNumber  = 60; // Middle C = 60
	Accidental accidental	   = Accidental::None;
	bool	   showLedgerLines = true;

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

	int							getLedgerOverflow(int midiNote, Clef clef);

	static juce::Rectangle<int> getRecommendedBounds();

private:
	void				 loadNotationFont();

	void				 drawStaff(juce::Graphics &g, juce::Rectangle<float> staffArea);
	void				 drawClef(juce::Graphics &g, juce::Rectangle<float> staffArea, Clef clef);
	void				 drawNote(juce::Graphics &g, juce::Rectangle<float> staffArea, const NoteDescriptor &note, Clef clef, OttavaType ottava);
	void				 drawLedgerLines(juce::Graphics &g, juce::Rectangle<float> staffArea, int staffPosition, float noteX);
	void				 drawAccidental(juce::Graphics &g, float x, float y, Accidental accidental);

	/*
	 @brief					Draws the "8va"/"8vb" marking beside the notehead.
	 @param					[IN] x / y of the notehead the marking belongs to.
							Previously this was centred over the whole staff
							regardless of where the note actually sat, so it
							could land on top of - and be hidden behind - the
							notehead itself.
	*/
	void				 drawOttavaText(juce::Graphics &g, OttavaType ottava, float noteX, float noteY, float noteWidth);

	OttavaType			 determineOttava(int midiNote, Clef clef);

	int					 midiNoteToStaffPosition(const int midiNote, Clef clef);

	float				 staffPositionToY(int staffPosition, juce::Rectangle<float> staffArea) const;


	juce::Font			 mNotationFont;
	juce::Colour		 mStaffLineColor			 = juce::Colour::fromRGB(107, 103, 96);	 // textTertiary
	juce::Colour		 mNoteColor					 = juce::Colour::fromRGB(238, 233, 218); // textPrimary

	const float			 mStaffLineSpacing			 = 9.5f;								 // Space between staff lines in px
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

	// Max ledger lines before triggering ottava
	static constexpr int kMaxLedgerLines			 = 3;

	static constexpr float kNoteXFraction			 = 0.6f;
};
