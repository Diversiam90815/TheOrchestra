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

	// Enable clipping to prevent notes from drawing outside bounds
	g.reduceClipRegion(bounds);

	juce::Rectangle<float> staffArea   = bounds.toFloat().reduced(3.0f, 0.0f);

	// Calculate staff height (4 spaces + line spacing)
	float				   staffHeight = mStaffLineSpacing * 4.0f;
	staffArea.setHeight(staffHeight);

	// Center staff vertically
	float yOffset = (bounds.getHeight() - staffHeight) * 0.5f;
	staffArea.translate(0.0f, yOffset);

	// Determine if ottava is needed
	OttavaType ottava = determineOttava(note.midiNoteNumber, clef);

	drawStaff(g, staffArea);
	drawClef(g, staffArea, clef);
	drawNote(g, staffArea, note, clef, ottava);
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
	return juce::Rectangle<int>(0, 0, 160, 128);
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


void NotationRenderer::drawNote(juce::Graphics &g, juce::Rectangle<float> staffArea, const NoteDescriptor &note, Clef clef, OttavaType ottava)
{
	// If ottava is active, shift the displayed note toward the staff by one
	// or two octaves.
	const int displayMidi	= note.midiNoteNumber + ottavaDisplacement(ottava);

	int		  staffPosition = midiNoteToStaffPosition(displayMidi, clef);
	float	  noteX			= staffArea.getX() + staffArea.getWidth() * kNoteXFraction;
	float	  noteY			= staffPositionToY(staffPosition, staffArea);

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

	if (ottava != OttavaType::None)
		drawOttavaText(g, ottava, noteX, noteY, noteWidth);
}


void NotationRenderer::drawOttavaText(juce::Graphics &g, OttavaType ottava, float noteX, float noteY, float noteWidth)
{
	g.setColour(mNoteColor.withAlpha(0.75f));

	auto textFont = juce::Font(juce::FontOptions(12.5f));
	textFont.setExtraKerningFactor(0.02f);
	g.setFont(textFont);

	juce::String text;
	switch (ottava)
	{
	case OttavaType::Ottava8va: text = "8va"; break;
	case OttavaType::Ottava8vb: text = "8vb"; break;
	case OttavaType::Ottava15ma: text = "15ma"; break;
	case OttavaType::Ottava15mb: text = "15mb"; break;
	default: return;
	}

	// Immediately to the right of the notehead, vertically centred on it -
	// previously this was centred over the whole staff at a fixed position
	// above/below it, independent of where the note actually landed, so it
	// could end up drawn behind the notehead instead of legible beside it.
	float x = noteX + (noteWidth * 0.5f) + 3.0f;
	float y = noteY - 7.0f;
	g.drawText(text, x, y, 36.0f, 14.0f, juce::Justification::centredLeft);
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


float NotationRenderer::staffPositionToY(int staffPosition, juce::Rectangle<float> staffArea) const
{
	// Staff position 0 = top line, 8 = bottom line
	// Each position is half a space (half of mStaffLineSpacing)
	float y = staffArea.getY() + (staffPosition * mStaffLineSpacing * 0.5f);
	return y;
}
