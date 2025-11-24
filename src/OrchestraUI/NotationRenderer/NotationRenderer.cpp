/*
  ==============================================================================
	Module			NotationRenderer
	Description		Renders musical notation
  ==============================================================================
*/

#include "NotationRenderer.h"


NotationRenderer::NotationRenderer()
{
	loadNotationFont();
}


void NotationRenderer::renderStaffWithNote(juce::Graphics &g, juce::Rectangle<int> bounds, const NoteDescriptor &note, Clef clef)
{
	if (bounds.isEmpty())
		return;

	juce::Rectangle<float> staffArea   = bounds.toFloat().reduced(3.0f, 0.0f);

	// Calculate staff height (4 spaces + line spacing)
	float				   staffHeight = mStaffLineSpacing * 4.0f;
	staffArea.setHeight(staffHeight);

	// Center staff vertically
	float yOffset = (bounds.getHeight() - staffHeight) * 0.5f;
	staffArea.translate(0.0f, yOffset);

	drawStaff(g, staffArea);
	drawClef(g, staffArea, clef);
	drawNote(g, staffArea, note, clef);
}


void NotationRenderer::setStafflineColour(juce::Colour colour)
{
	mStaffLineColor = colour;
}


void NotationRenderer::setNoteColour(juce::Colour colour)
{
	mNoteColor = colour;
}


juce::Rectangle<int> NotationRenderer::getRecommendedBounds()
{
	return juce::Rectangle<int>(0, 0, 100, 80);
}


void NotationRenderer::loadNotationFont()
{
	// Load bravura font from binarydata

	juce::Typeface::Ptr typeface = juce::Typeface::createSystemTypefaceFor(NotationFontData::Bravura_otf, NotationFontData::Bravura_otfSize);

	if (!typeface)
	{
		mNotationFont = juce::Font(juce::Font::getDefaultSerifFontName(), 40.0f, juce::Font::plain);
		LOG_ERROR("Bravura font not found! Notation will not render correctly.");
		return;
	}

	mNotationFont = juce::Font(typeface);
	mNotationFont.setHeight(40.0f);
	LOG_INFO("Bravura font loaded successfully from binary data");
}


void NotationRenderer::drawStaff(juce::Graphics &g, juce::Rectangle<float> staffArea)
{
	g.setColour(mStaffLineColor);

	for (int line = 0; line < 5; ++line)
	{
		float y = staffArea.getY() + (line * mStaffLineSpacing);
		g.fillRect(staffArea.getX(), y, staffArea.getWidth(), mStaffLineThickness);
	}
}


void NotationRenderer::drawClef(juce::Graphics &g, juce::Rectangle<float> staffArea, Clef clef)
{
	g.setColour(mNoteColor);
	g.setFont(mNotationFont.withHeight(mStaffLineSpacing * 15.0f));

	float clefX = staffArea.getX() + 5.0f;
	float clefY = 0.0f;

	switch (clef)
	{
	case Clef::Treble:
	{
		clefY			   = staffArea.getY() + (mStaffLineSpacing * 3.0f);
		juce::String glyph = juce::String::charToString(kGlyphClefG);
		g.drawText(glyph, clefX, clefY - (mStaffLineSpacing * 3.5f), 40.0f, mStaffLineSpacing * 7.0f, juce::Justification::centredLeft);
		break;
	}
	case Clef::Bass:
	{
		clefY			   = staffArea.getY() + (mStaffLineSpacing * 1.0f);
		juce::String glyph = juce::String::charToString(kGlyphClefF);
		g.drawText(glyph, clefX, clefY - (mStaffLineSpacing * 1.0f), 40.0f, mStaffLineSpacing * 5.0f, juce::Justification::centredLeft);
		break;
	}
	case Clef::Alto:
	{
		clefY			   = staffArea.getY() + (mStaffLineSpacing * 2.0f);
		juce::String glyph = juce::String::charToString(kGlyphClefC);
		g.drawText(glyph, clefX, clefY - (mStaffLineSpacing * 2.0f), 40.0f, mStaffLineSpacing * 5.0f, juce::Justification::centredLeft);
		break;
	}
	case Clef::Tenor:
	{
		clefY			   = staffArea.getY() + (mStaffLineSpacing * 1.0f);
		juce::String glyph = juce::String::charToString(kGlyphClefC);
		g.drawText(glyph, clefX, clefY - (mStaffLineSpacing * 1.5f), 40.0f, mStaffLineSpacing * 5.0f, juce::Justification::centredLeft);
		break;
	}
	default: break;
	}
}


void NotationRenderer::drawNote(juce::Graphics &g, juce::Rectangle<float> staffArea, const NoteDescriptor &note, Clef clef)
{
	int	  staffPosition = midiNoteToStaffPosition(note.midiNoteNumber, clef);
	float noteX			= staffArea.getCentreX() * 1.2f;
	float noteY			= staffPositionToY(staffPosition, staffArea);

	// Draw ledger lines if needed
	if (note.showLedgerLines)
		drawLedgerLines(g, staffArea, staffPosition, noteX);

	// Draw accidental if needed
	if (note.accidental != Accidental::None)
		drawAccidental(g, noteX - 22.0f, noteY, note.accidental);

	// Draw notehead
	g.setColour(mNoteColor);
	g.setFont(mNotationFont.withHeight(mStaffLineSpacing * 18.0f));

	juce::String noteGlyph = juce::String::charToString(kGlyphNoteheadBlack);
	float		 noteWidth = mStaffLineSpacing * 2.5f;
	g.drawText(noteGlyph, noteX - (noteWidth * 0.5f), noteY - (mStaffLineSpacing * 1.5f), noteWidth, mStaffLineSpacing * 3.0f, juce::Justification::centred);
}


void NotationRenderer::drawLedgerLines(juce::Graphics &g, juce::Rectangle<float> staffArea, int staffPosition, float noteX)
{
	g.setColour(mStaffLineColor);

	float ledgerLineWidth = mStaffLineSpacing * 1.5f;
	float ledgerLineX	  = noteX - (ledgerLineWidth * 0.5f);

	// Ledger lines above staff (position < 0)
	if (staffPosition < 0)
	{
		for (int pos = -2; pos >= staffPosition; pos -= 2)
		{
			float y = staffPositionToY(pos, staffArea);
			g.fillRect(ledgerLineX, y, ledgerLineWidth, mStaffLineThickness);
		}
	}

	// Ledger lines below staff (position > 8)
	if (staffPosition > 8)
	{
		for (int pos = 10; pos <= staffPosition; pos += 2)
		{
			float y = staffPositionToY(pos, staffArea);
			g.fillRect(ledgerLineX, y, ledgerLineWidth, mStaffLineThickness);
		}
	}
}


void NotationRenderer::drawAccidental(juce::Graphics &g, float x, float y, Accidental accidental)
{
	g.setColour(mNoteColor);
	g.setFont(mNotationFont.withHeight(mStaffLineSpacing * 12.0f));

	int glyphCode = kGlyphAccidentalNatural;

	switch (accidental)
	{
	case Accidental::Sharp: glyphCode = kGlyphAccidentalSharp; break;
	case Accidental::Flat: glyphCode = kGlyphAccidentalFlat; break;
	case Accidental::Natural: glyphCode = kGlyphAccidentalNatural; break;
	case Accidental::DoubleSharp: glyphCode = kGlyphAccidentalDoubleSharp; break;
	case Accidental::DoubleFlat: glyphCode = kGlyphAccidentalDoubleFlat; break;
	default: return;
	}

	juce::String glyph = juce::String::charToString(glyphCode);
	g.drawText(glyph, x - 10.0f, y - (mStaffLineSpacing * 1.5f), 20.0f, mStaffLineSpacing * 3.0f, juce::Justification::centred);
}


int NotationRenderer::midiNoteToStaffPosition(const int midiNote, Clef clef)
{
	// Convert midi note to diatonic staff position
	// Staff position 0 = top line, increasing downward

	// 1 -	Get note class (C=0, C#=1, D=2,..)
	int				 noteClass				 = midiNote % 12;
	int				 octave					 = (midiNote / 12) - 1; // Midi Octave: C4 = oct. 4

	// 2 -	Map chromatic note class to diatonic position within octave
	//		C=0, D=1, E=2, F=3,..
	static const int chromaticToDiatonic[12] = {
		0, // C
		0, // C# (display as C)
		1, // D
		1, // D# (display as D)
		2, // E
		3, // F
		3, // F# (display as F)
		4, // G
		4, // G# (display as G)
		5, // A
		5, // A# (display as A)
		6  // B
	};

	int diatonicNote			 = chromaticToDiatonic[noteClass];

	// 3 -	Calculate absolute diatonic positon (C0 = pos 0)
	int absoluteDiatonicPosition = octave * 7 + diatonicNote;

	// 4 -	Calculate staff position relative to clef
	int referencePosition		 = 0; // Position on staff for reference note
	int referenceDiatonicPos	 = 0; // Absolute diatonic position of reference

	switch (clef)
	{
	case Clef::Treble:
		// F5 is on top line (position 0)
		// F5 = MIDI 77, octave 5, F = diatonic 3
		referencePosition	 = 0;
		referenceDiatonicPos = 5 * 7 + 3; // Octave 5, F
		break;

	case Clef::Bass:
		// A3 is on top line (position 0)
		// A3 = MIDI 57, octave 3, A = diatonic 5
		referencePosition	 = 0;
		referenceDiatonicPos = 3 * 7 + 5; // Octave 3, A
		break;

	case Clef::Alto:
		// C4 is on middle line (position 4)
		// C4 = MIDI 60, octave 4, C = diatonic 0
		referencePosition	 = 4;
		referenceDiatonicPos = 4 * 7 + 0; // Octave 4, C
		break;

	case Clef::Tenor:
		// A3 is on middle line (position 4)
		// A3 = MIDI 57, octave 3, A = diatonic 5
		referencePosition	 = 4;
		referenceDiatonicPos = 3 * 7 + 5; // Octave 3, A
		break;
	}

	// calculate staff position (going down from reference = positive positions)
	int staffPosition = referencePosition + (referenceDiatonicPos - absoluteDiatonicPosition);

	return staffPosition;
}


float NotationRenderer::staffPositionToY(int staffPosition, juce::Rectangle<float> staffArea) const
{
	// Staff position 0 = top line, 8 = bottom line
	// Each position is half a space (half of mStaffLineSpacing)
	float y = staffArea.getY() + (staffPosition * mStaffLineSpacing * 0.5f);
	return y;
}


juce::String NotationRenderer::getSMuFLCharacter(const juce::String &glyphname)
{
	return juce::String();
}
