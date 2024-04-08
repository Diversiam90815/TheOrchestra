/*
  ==============================================================================

    InstrumentInfoView.h
    Created: 8 Apr 2024 6:24:22pm
    Author:  Jens.Langenberg

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "InstrumentInfoModel.h"


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

    void showInstrument(InstrumentInfo info);

    void showText(TextEditor& destinationEditor, StringArray textToShow);

    void showText(TextEditor& destinationEditor, String textToShow);

    void setupTextEditor(TextEditor& editorToSetup);

    StringArray getMenuBarNames() override;
    PopupMenu getMenuForIndex(int topLevelMenuIndex, const String& menuName) override;
    void menuItemSelected(int menuItemID, int topLevelMenuIndex) override;

private:

    int mCurrentSelectedInstrument = defaultInstrument;        //Default value out of reach of different enums

    int mCurrentFamily = Family::Default;

    MenuBarComponent menuBar;

    InstrumentInfoModel mInstrumentModel;

    TextEditor mLabel;
    TextEditor mRange;
    TextEditor mRoles;
    TextEditor mQualities;
    TextEditor mTransposition;
    TextEditor mPlayingTechniques;
    TextEditor mFamousWorks;
};