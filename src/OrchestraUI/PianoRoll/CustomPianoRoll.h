/*
  ==============================================================================
	Module			CustomPianoRoll
	Description		Creating our own custom piano roll, which displays the instrument's individual ranges
  ==============================================================================
*/

#pragma once

#include "JuceIncludes.h"
#include "Parameters.h"
#include "Theme.h"
#include "Helper.h"
#include "InstrumentInfo.h"


// Enum to identify the key used
enum PianoKey
{
	defaultKey = 0,
	blackKey,
	whiteKey
};


/*
 @brief                 Creating our own Piano Roll in order to display the instrument quality ranges with different colours on the Piano Roll
*/
class CustomPianoRoll : public juce::MidiKeyboardComponent
{
public:
	CustomPianoRoll(juce::MidiKeyboardState &state, juce::KeyboardComponentBase::Orientation orientation);
	~CustomPianoRoll() = default;

	bool setMidiRanges(const InstrumentRegisters &qualities);

	bool setMidiRanges(const InstrumentRange &ranges);

	void setPlayableRange(int lowNote, int highNote);

	void fitKeysToWidth();

private:
	juce::Colour getNoteColour(int midiNoteNumber, PianoKey keyType) const;

	int			 getRegisterIndex(int midiNoteNumber) const;

	void drawWhiteNote(int midiNoteNumber, juce::Graphics &g, juce::Rectangle<float> area, bool isDown, bool isOver, juce::Colour lineColour, juce::Colour textColour) override;

	void drawBlackNote(int midiNoteNumber, juce::Graphics &g, juce::Rectangle<float> area, bool isDown, bool isOver, juce::Colour noteFillColour) override;

	void lookAndFeelChanged() override;

	void applyThemeColours();

	bool isPlayable(int midiNoteNumber) const;


	std::vector<std::pair<int, int>> mMidiRanges;


	std::pair<int, int>				 mPlayableRange = {0, 0};

	bool							 mRangesSet		= false;

	static constexpr float			 kMinKeyWidth	= 6.0f;
};
