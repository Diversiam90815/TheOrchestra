/*
  ==============================================================================

	CustomPianoRoll.cpp
	Created: 18 Apr 2024 3:58:09pm
	Author:  Jens.Langenberg

  ==============================================================================
*/

#include "CustomPianoRoll.h"

CustomPianoRoll::CustomPianoRoll(MidiKeyboardState &state, Orientation orientation) : MidiKeyboardComponent(state, orientation)
{
}


void CustomPianoRoll::drawWhiteNote(int midiNoteNumber, Graphics &g, Rectangle<float> area, bool isDown, bool isOver, Colour lineColour, Colour textColour)
{
	mCurrentKeyType = key::whiteKey;

	if (!mRangesSet.get())
	{
		auto c = Colours::transparentWhite;

		if (isDown)
			c = findColour(keyDownOverlayColourId);
		if (isOver)
			c = c.overlaidWith(findColour(mouseOverKeyOverlayColourId));

		g.setColour(c);
	}
	else
	{
		Colour noteColour = getNoteColour(midiNoteNumber);
		g.setColour(isDown ? noteColour.brighter() : noteColour);
		g.setColour(isOver ? noteColour.brighter() : noteColour);
	}

	g.fillRect(area);

	// Draw the outline for the white note to maintain the separators
	g.setColour(lineColour);
	g.drawRect(area);

	const auto currentOrientation = getOrientation();

	auto	   text				  = getWhiteNoteText(midiNoteNumber);

	if (text.isNotEmpty())
	{
		auto fontHeight = jmin(12.0f, getKeyWidth() * 0.9f);

		g.setColour(textColour);
		g.setFont(Font(fontHeight).withHorizontalScale(0.8f));

		switch (currentOrientation)
		{
		case horizontalKeyboard: g.drawText(text, area.withTrimmedLeft(1.0f).withTrimmedBottom(2.0f), Justification::centredBottom, false); break;
		case verticalKeyboardFacingLeft: g.drawText(text, area.reduced(2.0f), Justification::centredLeft, false); break;
		case verticalKeyboardFacingRight: g.drawText(text, area.reduced(2.0f), Justification::centredRight, false); break;
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


void CustomPianoRoll::drawBlackNote(int midiNoteNumber, Graphics &g, Rectangle<float> area, bool isDown, bool isOver, Colour noteFillColour)
{
	mCurrentKeyType			 = key::blackKey;

	Colour baseColour		 = Colours::black;
	Colour noteOverlayColour = getNoteColour(midiNoteNumber).withAlpha(0.4f);

	if (mRangesSet.get())
	{
		if (isDown)
		{
			baseColour = baseColour.overlaidWith(noteOverlayColour.brighter(0.5f)); // Less brightening when down
		}
		else if (isOver)
		{
			baseColour = baseColour.overlaidWith(noteOverlayColour.brighter(0.4f)); // Very subtle brightening when over
		}
		else
		{
			baseColour = baseColour.overlaidWith(noteOverlayColour); // Normal state
		}
	}
	else
	{
		if (isDown)
		{
			baseColour = baseColour.overlaidWith(findColour(keyDownOverlayColourId));
		}
		if (isOver)
		{
			baseColour = baseColour.overlaidWith(findColour(mouseOverKeyOverlayColourId));
		}
	}

	// Set the color and fill the key area
	g.setColour(baseColour);
	g.fillRect(area);

	// Drawing border for key down state
	if (isDown)
	{
		g.setColour(noteFillColour);
		g.drawRect(area, 1.0f); // Specify thickness if needed
	}
	else
	{
		// Optionally draw a subtle highlight at the top for additional feedback
		g.setColour(baseColour);
		float sideIndent = 1.0f / 8.0f;
		float topIndent	 = 7.0f / 8.0f;
		float w			 = area.getWidth();
		float h			 = area.getHeight();

		switch (getOrientation())
		{
		case horizontalKeyboard: g.fillRect(area.reduced(w * sideIndent, 0).removeFromTop(h * topIndent)); break;
		case verticalKeyboardFacingLeft: g.fillRect(area.reduced(0, h * sideIndent).removeFromRight(w * topIndent)); break;
		case verticalKeyboardFacingRight: g.fillRect(area.reduced(0, h * sideIndent).removeFromLeft(w * topIndent)); break;
		default: break;
		}
	}
}


Colour CustomPianoRoll::getNoteColour(int midiNoteNumber)
{
	// Ensure there is a color for each range
	if (mMidiRanges.size() > qualityColours.size())
	{
		jassertfalse; // More ranges than colors provided
		if (mCurrentKeyType.get() == key::whiteKey)
		{
			return Colours::transparentWhite;
		}
		if (mCurrentKeyType.get() == key::blackKey)
		{
			return Colours::black;
		}
	}

	// Check which range the midiNoteNumber falls into
	for (size_t i = 0; i < mMidiRanges.size(); ++i)
	{
		const auto &range = mMidiRanges[i];
		if (midiNoteNumber >= range.first && midiNoteNumber <= range.second)
		{
			return qualityColours[i]; // Return the corresponding color
		}
	}

	// If no range matches, return a default color
	if (mCurrentKeyType.get() == key::whiteKey)
	{
		return Colours::transparentWhite;
	}
	if (mCurrentKeyType.get() == key::blackKey)
	{
		return Colours::black;
	}
}


int CustomPianoRoll::turnNotenameIntoMidinumber(String notename)
{
	wchar_t				  wOctave			= notename.getLastCharacter();
	int					  octave			= wOctave - '0';

	String				  noteWithoutOctave = notename.dropLastCharacters(1);

	std::map<String, int> noteToMidi		= {{"C", 0},  {"C#", 1}, {"Db", 1}, {"D", 2},  {"D#", 3}, {"Eb", 3},  {"E", 4},	  {"F", 5}, {"F#", 6},
											   {"Gb", 6}, {"G", 7},	 {"G#", 8}, {"Ab", 8}, {"A", 9},  {"A#", 10}, {"Bb", 10}, {"B", 11}};

	int					  noteValue			= 0;

	if (noteToMidi.find(noteWithoutOctave) != noteToMidi.end())
	{
		noteValue = noteToMidi[noteWithoutOctave];
	}

	else
		return -1;

	int midiNumber = 12 * (octave + 2) + noteValue;

	return midiNumber;
}


bool CustomPianoRoll::setMidiRanges(const StringArray &qualities)
{
	mRangesSet = false;
	mMidiRanges.clear();

	for (const auto &quality : qualities)
	{
		// Tokenize the string around the colon to separate the note range from the description
		int colonPos = quality.indexOf(":");
		if (colonPos != -1)
		{
			String range   = quality.substring(0, colonPos).trim();

			// Find the dash separating the start and end notes
			int	   dashPos = range.indexOf("-");
			if (dashPos != -1)
			{
				String startNote = range.substring(0, dashPos).trim();
				String endNote	 = range.substring(dashPos + 1).trim();

				// Convert start and end notes to MIDI numbers
				int	   startMidi = turnNotenameIntoMidinumber(startNote);
				int	   endMidi	 = turnNotenameIntoMidinumber(endNote);

				// Store the range as a pair of MIDI numbers
				mMidiRanges.push_back(std::make_pair(startMidi, endMidi));
			}
		}
	}

	bool result = !mMidiRanges.empty();
	mRangesSet	= result;
	return result;
}


bool CustomPianoRoll::setMidiRanges(const String &range)
{
	// Find the dash separating the start and end notes
	int dashPos = range.indexOf("-");
	if (dashPos != -1)
	{
		String startNote = range.substring(0, dashPos).trim();
		String endNote	 = range.substring(dashPos + 1).trim();

		// Convert start and end notes to MIDI numbers
		int	   startMidi = turnNotenameIntoMidinumber(startNote);
		int	   endMidi	 = turnNotenameIntoMidinumber(endNote);

		// Store the range as a pair of MIDI numbers
		mMidiRanges.push_back(std::make_pair(startMidi, endMidi));
	}

	bool result = !mMidiRanges.empty();
	mRangesSet	= result;
	return result;
}
