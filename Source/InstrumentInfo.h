/*
  ==============================================================================

    InstrumentInfo.h
    Created: 1 Apr 2024 3:50:07pm
    Author:  jerry

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

#include "Parameters.h"
#include "InstrumentData.h"



enum Family
{
    Default = 1,    //Displays default info at startup
    Brass,
    Strings,
    Woodwinds,
    Percussion
};

enum Strings
{
    Violin = 1,
    Viola,
    Violoncello,
    DoubleBass
};

enum Woodwinds
{
    Piccolo = 1,
    Flute,
    Oboe,
    CorAnglais,
    Clarinet,
    BassClarinet,
    Basson,
    Contrabassoon
};

enum Percussion
{
    Harp = 1,
    Celeste,
    Timpani,
    Marimba
};

enum Brass
{
    FrenchHorn = 1,
    Trumpet,
    TenorTrombone,
    BassTrombone,
    Cimbasso,
    Tuba
};

class InstrumentInfo 
{
public:
    InstrumentInfo();
    InstrumentInfo(const juce::String& name, const juce::String& range, const juce::StringArray& qualities, const juce::StringArray& roles, const juce::StringArray& famousWorks, const juce::String& transposition);
    ~InstrumentInfo();
    
private:
    juce::String name; // Optional, for identifying the instrument
    juce::String range;
    juce::StringArray qualities;
    juce::StringArray roles;
    juce::StringArray famousWorks;
    juce::String transposition; // Assuming transposition doesn't need to be a StringArray

    friend class InstrumentInfoModel;
    friend class InstrumentInfoView;
};

