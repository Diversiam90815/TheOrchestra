/*
  ==============================================================================

    PianoRoll.cpp
    Created: 17 Feb 2024 2:40:46pm
    Author:  jerry

  ==============================================================================
*/

#include "PianoRoll.h"


PianoRoll::PianoRoll()
{
    mPianoState.addListener(this);

    mPianoRoll = std::make_unique<CustomMidiKeyboardComponent>(mPianoState, MidiKeyboardComponent::horizontalKeyboard);

    showPianoRoll();
    turnNotenameIntoMidinumber("D4");
    turnNotenameIntoMidinumber("C4");
}


PianoRoll::~PianoRoll()
{
    mPianoRoll->removeAllChangeListeners();
    mPianoState.removeListener(this);
    mPianoRoll.reset();
}


void PianoRoll::resized()
{
    mPianoRoll->setBoundsRelative(0.0f, 0.0f, 1.0f, 1.0f);
}


void PianoRoll::showPianoRoll()
{
    mPianoRoll->setName("Piano Roll");
    addAndMakeVisible(mPianoRoll.get());
}


void PianoRoll::handleNoteOn(MidiKeyboardState*, int midiChannel, int midiNoteNumber, float velocity)
{

}


void PianoRoll::handleNoteOff(MidiKeyboardState*, int midiChannel, int midiNoteNumber, float velocity)
{

}


int PianoRoll::turnNotenameIntoMidinumber(String& notename)
{
    wchar_t wOctave = notename.getLastCharacter();
    int octave = wOctave - '0';
    
    String noteWithoutOctave = notename.dropLastCharacters(1);

    std::map<String, int> noteToMidi = { {"C", 0}, {"C#", 1}, {"Db", 1}, {"D", 2}, {"D#", 3}, {"Eb", 3},
                                       {"E", 4}, {"F", 5}, {"F#", 6}, {"Gb", 6}, {"G", 7}, {"G#", 8},
                                       {"Ab", 8}, {"A", 9}, {"A#", 10}, {"Bb", 10}, {"B", 11} };

    int noteValue = 0;

    if (noteToMidi.find(noteWithoutOctave) != noteToMidi.end()) 
    {
        noteValue = noteToMidi[noteWithoutOctave];
    }

    else 
    {
        return -1;
    }

    int midiNumber = 12 * (octave + 1) + noteValue;

    return midiNumber;
}


std::vector<std::pair<int, int>> PianoRoll::getMidiRanges(const StringArray& qualities) {
    std::vector<std::pair<int, int>> midiRanges;

    for (const auto& quality : qualities) 
    {
        // Tokenize the string around the colon to separate the note range from the description
        int colonPos = quality.indexOf(":");
        if (colonPos != -1) 
        {
            String range = quality.substring(0, colonPos).trim();

            // Find the dash separating the start and end notes
            int dashPos = range.indexOf("-");
            if (dashPos != -1) 
            {
                String startNote = range.substring(0, dashPos).trim();
                String endNote = range.substring(dashPos + 1).trim();

                // Convert start and end notes to MIDI numbers
                int startMidi = turnNotenameIntoMidinumber(startNote);
                int endMidi = turnNotenameIntoMidinumber(endNote);

                // Store the range as a pair of MIDI numbers
                midiRanges.push_back(std::make_pair(startMidi, endMidi));
            }
        }
    }

    return midiRanges;
}
