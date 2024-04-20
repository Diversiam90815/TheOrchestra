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
    Woodwinds = 1,
    Brass,
    Strings,
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
    InstrumentInfo(const String& name, const String& range, const StringArray& qualities, const StringArray& roles, const StringArray& famousWorks, const String& transposition, const StringArray& playingTechniques);
    ~InstrumentInfo();
    
private:
    String mName;
    String mRange;
    StringArray mQualities;
    StringArray mUsefulInformation;
    StringArray mFamousWorks;
    String mTransposition;
    StringArray mPlayingTechniques;

    friend class InstrumentInfoModel;
    friend class InstrumentInfoView;
};

