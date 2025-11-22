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


void				 NotationRenderer::renderStaffWithNote(juce::Graphics &g, juce::Rectangle<int> bounds, const NoteDescriptor &note, Clef clef) {}


void				 NotationRenderer::setStafflineColour(juce::Colour colour) {}


void				 NotationRenderer::setNoteColour(juce::Colour colour) {}


juce::Rectangle<int> NotationRenderer::getRecommendedBounds()
{
	return juce::Rectangle<int>();
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


void NotationRenderer::drawStaff(juce::Graphics &g, juce::Rectangle<float> staffArea) {}


void NotationRenderer::drawClef(juce::Graphics &g, juce::Rectangle<float> staffArea, Clef clef) {}


void NotationRenderer::drawNote(juce::Graphics &g, juce::Rectangle<float> staffArea, const NoteDescriptor &note, Clef clef) {}


void NotationRenderer::drawLedgerLines(juce::Graphics &g, juce::Rectangle<float> staffArea, int staffPosition, float noteX) {}


void NotationRenderer::drawAccidental(juce::Graphics &g, float x, float y, Accidental accidental) {}


int	 NotationRenderer::midiNoteToStaffPosition(const int midiNote, Clef clef)
{
	return 0;
}


float NotationRenderer::staffPositionToY(int staffPosition, juce::Rectangle<int> staffArea)
{
	return 0.0f;
}


juce::String NotationRenderer::getSMuFLCharacter(const juce::String &glyphname)
{
	return juce::String();
}
