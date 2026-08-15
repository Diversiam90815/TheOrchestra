/*
  ==============================================================================
	Module			CustomPianoRoll
	Description		Creating our own custom piano roll, which displays the instrument's individual ranges
  ==============================================================================
*/

#include "CustomPianoRoll.h"


namespace
{
bool isWhiteKey(int midiNoteNumber)
{
	switch (midiNoteNumber % 12)
	{
	case 0:
	case 2:
	case 4:
	case 5:
	case 7:
	case 9:
	case 11: return true;
	default: return false;
	}
}
} // namespace


CustomPianoRoll::CustomPianoRoll(juce::MidiKeyboardState &state, juce::KeyboardComponentBase::Orientation orientation) : juce::MidiKeyboardComponent(state, orientation)
{
	setOctaveForMiddleC(4);
	setScrollButtonsVisible(false);
	setBlackNoteLengthProportion(0.62f);
	applyThemeColours();
}


void CustomPianoRoll::applyThemeColours()
{
	const auto &t = themeFor(*this);

	setColour(whiteNoteColourId, t.pianoWell);
	setColour(blackNoteColourId, Keys::blackInRange);
	setColour(keySeparatorLineColourId, t.background);
	setColour(textLabelColourId, t.background.withAlpha(0.55f));
	setColour(shadowColourId, juce::Colours::transparentBlack);
}


void CustomPianoRoll::lookAndFeelChanged()
{
	applyThemeColours();
}


void CustomPianoRoll::fitKeysToWidth()
{
	int whiteKeys = 0;
	for (int note = getRangeStart(); note <= getRangeEnd(); ++note)
		if (isWhiteKey(note))
			++whiteKeys;

	if (whiteKeys <= 0 || getWidth() <= 0)
		return;

	setKeyWidth(juce::jmax(kMinKeyWidth, (float)getWidth() / (float)whiteKeys));
}


void CustomPianoRoll::drawWhiteNote(int midiNoteNumber, juce::Graphics &g, juce::Rectangle<float> area, bool isDown, bool isOver, juce::Colour lineColour, juce::Colour textColour)
{
	if (!mRangesSet)
	{
		auto c = juce::Colours::transparentWhite;

		if (isDown)
			c = findColour(keyDownOverlayColourId);
		if (isOver)
			c = c.overlaidWith(findColour(mouseOverKeyOverlayColourId));

		g.setColour(c);
	}
	else
	{
		juce::Colour noteColour = getNoteColour(midiNoteNumber, PianoKey::whiteKey);

		// Interaction states are applied on top of the register tint so both read.
		if (isDown)
			noteColour = noteColour.interpolatedWith(findColour(keyDownOverlayColourId), 0.7f);
		else if (isOver)
			noteColour = noteColour.brighter(0.12f);

		g.setColour(noteColour);
	}

	g.fillRect(area);

	// Draw the outline for the white note to maintain the separators
	g.setColour(lineColour);
	g.drawRect(area);

	const auto currentOrientation = getOrientation();

	auto	   text				  = getWhiteNoteText(midiNoteNumber);

	if (text.isNotEmpty())
	{
		auto fontHeight = juce::jmin(12.0f, getKeyWidth() * 0.9f);

		g.setColour(textColour);
		g.setFont(juce::Font(juce::FontOptions().withHeight(fontHeight).withHorizontalScale(0.8f)));

		switch (currentOrientation)
		{
		case horizontalKeyboard: g.drawText(text, area.withTrimmedLeft(1.0f).withTrimmedBottom(2.0f), juce::Justification::centredBottom, false); break;
		case verticalKeyboardFacingLeft: g.drawText(text, area.reduced(2.0f), juce::Justification::centredLeft, false); break;
		case verticalKeyboardFacingRight: g.drawText(text, area.reduced(2.0f), juce::Justification::centredRight, false); break;
		default: break;
		}
	}

	if (!lineColour.isTransparent())
	{
		g.setColour(lineColour);

		switch (currentOrientation)
		{
		case horizontalKeyboard: g.fillRect(area.withWidth(1.0f)); break;
		case verticalKeyboardFacingLeft: g.fillRect(area.withHeight(1.0f)); break;
		case verticalKeyboardFacingRight: g.fillRect(area.removeFromBottom(1.0f)); break;
		default: break;
		}

		if (midiNoteNumber == getRangeEnd())
		{
			switch (currentOrientation)
			{
			case horizontalKeyboard: g.fillRect(area.expanded(1.0f, 0).removeFromRight(1.0f)); break;
			case verticalKeyboardFacingLeft: g.fillRect(area.expanded(0, 1.0f).removeFromBottom(1.0f)); break;
			case verticalKeyboardFacingRight: g.fillRect(area.expanded(0, 1.0f).removeFromTop(1.0f)); break;
			default: break;
			}
		}
	}
}


void CustomPianoRoll::drawBlackNote(int midiNoteNumber, juce::Graphics &g, juce::Rectangle<float> area, bool isDown, bool isOver, juce::Colour noteFillColour)
{
	juce::Colour baseColour = juce::Colours::black;

	if (mRangesSet)
	{
		// Drawn opaquely. The previous version alpha-blended an already
		// near-black colour onto black, which erased the register entirely.
		baseColour = getNoteColour(midiNoteNumber, PianoKey::blackKey);

		if (isDown)
			baseColour = baseColour.brighter(0.5f);
		else if (isOver)
			baseColour = baseColour.brighter(0.25f);
	}
	else
	{
		if (isDown)
			baseColour = baseColour.overlaidWith(findColour(keyDownOverlayColourId));
		if (isOver)
			baseColour = baseColour.overlaidWith(findColour(mouseOverKeyOverlayColourId));
	}

	g.setColour(baseColour);
	g.fillRect(area);

	if (isDown)
	{
		g.setColour(noteFillColour);
		g.drawRect(area, 1.0f);
	}
}


int CustomPianoRoll::getRegisterIndex(int midiNoteNumber) const
{
	for (size_t i = 0; i < mMidiRanges.size(); ++i)
	{
		const auto &range = mMidiRanges[i];

		if (midiNoteNumber >= range.first && midiNoteNumber <= range.second)
			return (int)i;
	}

	return -1;
}


bool CustomPianoRoll::isPlayable(int midiNoteNumber) const
{
	return midiNoteNumber >= mPlayableRange.first && midiNoteNumber <= mPlayableRange.second;
}


void CustomPianoRoll::setPlayableRange(int lowNote, int highNote)
{
	mPlayableRange = {lowNote, highNote};
}


juce::Colour CustomPianoRoll::getNoteColour(int midiNoteNumber, PianoKey keyType) const
{
	const auto &t		= themeFor(*this);
	const bool	isWhite = (keyType == PianoKey::whiteKey);

	if (!mRangesSet)
		return isWhite ? juce::Colours::transparentWhite : juce::Colours::black;

	// Inside a register: take its colour.
	if (const int index = getRegisterIndex(midiNoteNumber); index >= 0)
		return isWhite ? t.whiteKeyForRegister(index) : t.blackKeyForRegister(index);

	// Playable but not in any register: natural key colour, so the full span
	// still reads as playable.
	if (isPlayable(midiNoteNumber))
		return isWhite ? Keys::whiteInRange : Keys::blackInRange;

	// Out of range: pushed hard away from the in-range colours so the playable
	// span reads as one solid block.
	return isWhite ? Keys::whiteOutOfRange : Keys::blackOutOfRange;
}


bool CustomPianoRoll::setMidiRanges(const InstrumentRegisters &qualities)
{
	mRangesSet = false;
	mMidiRanges.clear();

	for (const auto &quality : qualities)
		mMidiRanges.push_back(std::make_pair(quality.getLowerNoteValue(), quality.getHigherNoteValue()));

	// More registers than the palette has colours would silently repeat a
	// colour, so clamp and flag it rather than mis-colouring.
	if (mMidiRanges.size() > defaultTheme().registerBase.size())
	{
		jassertfalse;
		mMidiRanges.resize(defaultTheme().registerBase.size());
	}

	mRangesSet = !mMidiRanges.empty();

	// Registers are written-pitch, so widen the playable span to cover them all
	// in case the caller has not set it yet.
	for (const auto &r : mMidiRanges)
	{
		mPlayableRange.first  = mPlayableRange.first == 0 ? r.first : juce::jmin(mPlayableRange.first, r.first);
		mPlayableRange.second = juce::jmax(mPlayableRange.second, r.second);
	}

	return mRangesSet;
}


bool CustomPianoRoll::setMidiRanges(const InstrumentRange &range)
{
	mMidiRanges.clear();
	mRangesSet	  = false;

	int startMidi = range.getSoundingLowNote().empty() ? range.getWrittenLowNoteAsMidiValue() : range.getSoundingLowNoteAsMidiValue();
	int endMidi	  = range.getSoundingHighNote().empty() ? range.getWrittenHighNoteAsMidiValue() : range.getSoundingHighNoteAsMidiValue();

	mMidiRanges.push_back(std::make_pair(startMidi, endMidi));
	setPlayableRange(startMidi, endMidi);

	mRangesSet = !mMidiRanges.empty();
	return mRangesSet;
}
