/*
  ==============================================================================
	Module			CustomPianoRoll
	Description		Creating our own custom piano roll, which displays the instrument's individual ranges
  ==============================================================================
*/

#include "CustomPianoRoll.h"


CustomPianoRoll::CustomPianoRoll(juce::MidiKeyboardState &state, juce::KeyboardComponentBase::Orientation orientation) : juce::MidiKeyboardComponent(state, orientation)
{
	setOctaveForMiddleC(4);
}


void CustomPianoRoll::drawWhiteNote(int midiNoteNumber, juce::Graphics &g, juce::Rectangle<float> area, bool isDown, bool isOver, juce::Colour lineColour, juce::Colour textColour)
{
	mCurrentKeyType = PianoKey::whiteKey;

	if (!mRangesSet.load())
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
		juce::Colour noteColour = getNoteColour(midiNoteNumber);

		if (isDown)
			noteColour = noteColour.interpolatedWith(findColour(keyDownOverlayColourId), 0.8f);

		if (isOver)
			noteColour = noteColour.brighter(0.1f);

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
		g.setFont(juce::Font(fontHeight).withHorizontalScale(0.8f));

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
	mCurrentKeyType			 = PianoKey::blackKey;

	juce::Colour baseColour		   = juce::Colours::black;
	juce::Colour noteOverlayColour = getNoteColour(midiNoteNumber).withAlpha(0.4f);

	if (mRangesSet.load())
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


juce::Colour CustomPianoRoll::getNoteColour(int midiNoteNumber)
{
	auto qualityColours = mCustomLookAndFeel.getQualityColours(); // Get the colours for the note ranges

	if (mMidiRanges.size() > qualityColours.size())				  // Ensure there is a color for each range
	{
		jassertfalse;											  // More ranges than colors provided
		if (mCurrentKeyType.load() == PianoKey::whiteKey)
		{
			return juce::Colours::transparentWhite;
		}
		if (mCurrentKeyType.load() == PianoKey::blackKey)
		{
			return juce::Colours::black;
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
	if (mCurrentKeyType.load() == PianoKey::whiteKey)
	{
		return juce::Colours::transparentWhite;
	}
	if (mCurrentKeyType.load() == PianoKey::blackKey)
	{
		return juce::Colours::black;
	}
	return {};
}


bool CustomPianoRoll::setMidiRanges(const juce::StringArray &qualities)
{
	mRangesSet = false;
	mMidiRanges.clear();

	for (const auto &quality : qualities)
	{
		// Tokenize the string around the colon to separate the note range from the description
		int colonPos = quality.indexOf(":");
		if (colonPos != -1)
		{
			juce::String range	 = quality.substring(0, colonPos).trim();

			// Find the dash separating the start and end notes
			int	   dashPos = range.indexOf("-");
			if (dashPos != -1)
			{
				juce::String startNote = range.substring(0, dashPos).trim();
				juce::String endNote   = range.substring(dashPos + 1).trim();

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


bool CustomPianoRoll::setMidiRanges(const juce::String &range)
{
	mMidiRanges.clear();
	mRangesSet	= false;

	// Find the dash separating the start and end notes
	int dashPos = range.indexOf("-");
	if (dashPos != -1)
	{
		juce::String startNote = range.substring(0, dashPos).trim();
		juce::String endNote   = range.substring(dashPos + 1).trim();

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
