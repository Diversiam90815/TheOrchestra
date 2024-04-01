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



enum Family
{
    Default = 0,    //Displays default info at startup
    Brass,
    Strings,
    Woodwinds,
    Percussion
};

enum Strings
{
    Violin = 0,
    Viola,
    Violoncello,
    Contrabass
};

enum Woodwinds
{
    Piccolo = 0,
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
    Harp = 0,
    Celeste,
    Timpani,
    Marimba
};

enum Brass
{
    FrenchHorn = 0,
    Trumpet,
    TenorTrombone,
    BassTrombone,
    Cimbasso,
    Tuba
};


class InstrumentInfoView
{
public:
    InstrumentInfoView();
    ~InstrumentInfoView();

    void displayTextBoxes();

    void displayInstrument(int family, int instrument);

    void showStringsInstrument(int instrument);

    void showBrassInstrument(int instrument);

    void showPercussionInstrument(int instrument);

    void showWoodwindInstrument(int instrument);

private:

    int mCurrentSelectedInstrument = defaultInstrument;        //Default value out of reach of different enums

    int mCurrentFamily = Family::Default;


    TextEditor mLabel;
    TextEditor mCommonTechniques;
    TextEditor mRoles;
    TextEditor mQualities;
    TextEditor mTransposition;
};