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

	juce::Rectangle<float> staffArea   = bounds.toFloat().reduced(10.0f);

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
	g.setFont(mNotationFont.withHeight(mStaffLineSpacing * 10.0f));

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
	float noteX			= staffArea.getCentreX();
	float noteY			= staffPositionToY(staffPosition, staffArea);

	// Draw ledger lines if needed
	if (note.showLedgerLines)
		drawLedgerLines(g, staffArea, staffPosition, noteX);

	// Draw accidental if needed
	if (note.accidental != Accidental::None)
		drawAccidental(g, noteX - 20.0f, noteY, note.accidental);

	// Draw notehead
	g.setColour(mNoteColor);
	g.setFont(mNotationFont.withHeight(mStaffLineSpacing * 10.0f));

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
	g.setFont(mNotationFont.withHeight(mStaffLineSpacing * 2.5f));

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
	// Staff position 0 = top line, increasing downward
	// Even numbers = lines, Odd numbers = spaces

	int referenceNote	  = 0;
	int referencePosition = 0;

	switch (clef)
	{
	case Clef::Treble: // F5 (MIDI 77) is on the top line (position 0)
		referenceNote	  = 77;
		referencePosition = 0;
		break;

	case Clef::Bass: // A3 (MIDI 57) is on the top line (position 0)
		referenceNote	  = 57;
		referencePosition = 0;
		break;

	case Clef::Alto: // C5 (MIDI 72) is on the middle line (position 4)
		referenceNote	  = 72;
		referencePosition = 4;
		break;

	case Clef::Tenor: // A4 (MIDI 69) is on the middle line (position 4)
		referenceNote	  = 69;
		referencePosition = 4;
		break;
	}

	// Calculate positon based on chromatic distance
	// Approximate: 2 chrom. steps = 1 staff position

	int chromaticDiff = referenceNote - midiNote;
	int staffPosition = referencePosition + chromaticDiff;

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
