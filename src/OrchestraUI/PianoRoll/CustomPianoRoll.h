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

	/*
	 @brief                 Fills the vector 'mMidiRanges' with the note ranges information from a StringArray
	 @param                 [IN] qualities as an StringArray.
	 @return                Boolean indicating success/failure
	*/
	bool setMidiRanges(const InstrumentRegisters &qualities);

	/*
	 @brief                 Fills the vector 'mMidiRanges' with the note ranges information from a String
	 @param                 [IN] ranges as an String.
	 @return                Boolean indicating success/failure
	*/
	bool setMidiRanges(const InstrumentRange &ranges);

	/*
	 @brief                 Sets the instrument's overall playable span.

							Registers are not always a partition of the range:
							for strings each "register" is a single open-string
							note (Violin: G3, D4, A4, E5) while the instrument
							plays everything from G3 to A7. Without this, every
							note between the open strings would be drawn as
							out-of-range.
	 @param                 [IN] lowNote / highNote as MIDI values.
	*/
	void setPlayableRange(int lowNote, int highNote);

	/*
	 @brief                 Sizes the keys so the whole keyboard fits the current
							width without JUCE's scroll buttons. At the default
							17px key width a 128-note keyboard needs ~1275px and
							was being clipped.
	*/
	void fitKeysToWidth();

private:
	/*
	 @brief                 Colour for a key, by note and key type.
	 @param                 [IN] midiNoteNumber to colour.
	 @param                 [IN] keyType being drawn - passed explicitly rather
							than stashed in a member between draw calls.
	 @return                The key's fill colour.
	*/
	juce::Colour						  getNoteColour(int midiNoteNumber, PianoKey keyType) const;

	/*
	 @brief                 Index of the register a note falls into, or -1.
	*/
	int									  getRegisterIndex(int midiNoteNumber) const;

	void								  drawWhiteNote(int midiNoteNumber,
														juce::Graphics		  &g,
														juce::Rectangle<float> area,
														bool				   isDown,
														bool				   isOver,
														juce::Colour		   lineColour,
														juce::Colour		   textColour) override;

	void								  drawBlackNote(int midiNoteNumber, juce::Graphics &g, juce::Rectangle<float> area, bool isDown, bool isOver, juce::Colour noteFillColour) override;

	void								  lookAndFeelChanged() override;

	/*
	 @brief                 Pushes theme colours into the keyboard's colour IDs.
							drawKeyboardBackground is final in JUCE and fills
							with whiteNoteColourId, so the well colour is set
							rather than painted.
	*/
	void								  applyThemeColours();

	/*
	 @brief                 Whether a note is anywhere the instrument can play.
	*/
	bool								  isPlayable(int midiNoteNumber) const;

	// Ranges as (lowNote, highNote) pairs, in register order. Message-thread
	// only - written by setMidiRanges, read by the paint callbacks.
	std::vector<std::pair<int, int>>	  mMidiRanges;

	// The instrument's overall span, which registers may only partly cover.
	std::pair<int, int>					  mPlayableRange = { 0, 0 };

	bool								  mRangesSet	 = false;

	// The keyboard shows all 128 notes, so keys are sized to fit rather than
	// clamped up - a lower bound here would bring back the scroll buttons.
	static constexpr float				  kMinKeyWidth = 6.0f;
};
