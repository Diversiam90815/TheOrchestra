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
    Contrabass
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


class InstrumentInfoView : public Component, public MenuBarModel
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

    void resized() override;

    StringArray getMenuBarNames() override;
    PopupMenu getMenuForIndex(int topLevelMenuIndex, const String& menuName) override;
    void menuItemSelected(int menuItemID, int topLevelMenuIndex) override;

private:

    int mCurrentSelectedInstrument = defaultInstrument;        //Default value out of reach of different enums

    int mCurrentFamily = Family::Default;

    MenuBarComponent menuBar;

    TextEditor mLabel;
    TextEditor mCommonTechniques;
    TextEditor mRoles;
    TextEditor mQualities;
    TextEditor mTransposition;
};