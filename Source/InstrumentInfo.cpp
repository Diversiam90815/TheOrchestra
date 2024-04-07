/*
  ==============================================================================

    InstrumentInfo.cpp
    Created: 1 Apr 2024 3:50:07pm
    Author:  jerry

  ==============================================================================
*/

#include "InstrumentInfo.h"


InstrumentInfoView::InstrumentInfoView()
{

    displayTextBoxes();
}


InstrumentInfoView::~InstrumentInfoView()
{

}


void InstrumentInfoView::displayTextBoxes()
{
    setupTextEditor(mLabel);
    setupTextEditor(mRange);
    setupTextEditor(mRoles);
    setupTextEditor(mQualities);
    setupTextEditor(mTransposition);
    setupTextEditor(mPlayingTechniques);
    setupTextEditor(mFamousWorks);

    mLabel.setTextToShowWhenEmpty("Instrument",Colours::beige);
    mRange.setTextToShowWhenEmpty("Range", Colours::beige);
    mRoles.setTextToShowWhenEmpty("Roles within the Orchestra", Colours::beige);
    mQualities.setTextToShowWhenEmpty("Qualities", Colours::beige);
    mTransposition.setTextToShowWhenEmpty("Transposition", Colours::beige);
    mFamousWorks.setTextToShowWhenEmpty("Famous Works", Colours::beige);
    mPlayingTechniques.setTextToShowWhenEmpty("Playing Techniques", Colours::beige);
}

void InstrumentInfoView::resized()
{
    // Assuming mLabel takes up about 10% of the height for the title.
    float titleLabelHeight = 0.1f;

    // Adjust the height for the TextEditors, now divided by 3 rows.
    float textEditorHeight = (1.0f - titleLabelHeight) / 3; // Now for 3 rows.

    // Set bounds for mLabel centered horizontally at the top.
    mLabel.setBoundsRelative(0.25f, 0.0f, 0.5f, titleLabelHeight);

    // First row of TextEditors
    mRange.setBoundsRelative(0.0f, titleLabelHeight, 0.5f, textEditorHeight);
    mRoles.setBoundsRelative(0.5f, titleLabelHeight, 0.5f, textEditorHeight);

    // Calculate the starting Y position for the second row
    float secondRowYStart = titleLabelHeight + textEditorHeight;

    // Second row of TextEditors
    mQualities.setBoundsRelative(0.0f, secondRowYStart, 0.5f, textEditorHeight);
    mTransposition.setBoundsRelative(0.5f, secondRowYStart, 0.5f, textEditorHeight);

    // Calculate the starting Y position for the third row
    float thirdRowYStart = secondRowYStart + textEditorHeight;

    // Third row of TextEditors
    mPlayingTechniques.setBoundsRelative(0.0f, thirdRowYStart, 0.5f, textEditorHeight);
    mFamousWorks.setBoundsRelative(0.5f, thirdRowYStart, 0.5f, textEditorHeight);
}



StringArray InstrumentInfoView::getMenuBarNames()
{
    return { "Strings", "Woodwinds", "Brass", "Percussion" };
}


PopupMenu InstrumentInfoView::getMenuForIndex(int topLevelMenuIndex, const String& menuName)
{
    PopupMenu menu;
    if (topLevelMenuIndex == 0) // Strings
    {
        menu.addItem(Strings::Violin, ViolinName);
        menu.addItem(Strings::Viola, ViolaName);
        menu.addItem(Strings::Violoncello, VioloncelloName);
        menu.addItem(Strings::DoubleBass, DoubleBassName);
    }
    else if (topLevelMenuIndex == 1) // Woodwinds
    {
        menu.addItem(Woodwinds::Piccolo, PiccoloName);
        menu.addItem(Woodwinds::Flute, FluteName);
        menu.addItem(Woodwinds::Oboe, OboeName);
        menu.addItem(Woodwinds::CorAnglais, CorAnglaisName);
        menu.addItem(Woodwinds::Clarinet, ClarinetName);
        menu.addItem(Woodwinds::BassClarinet, BassClarinetName);
        menu.addItem(Woodwinds::Basson,BassoonName);
        menu.addItem(Woodwinds::Contrabassoon, ContrabassonName);
    }
    else if (topLevelMenuIndex == 2) //Brass
    {
        menu.addItem(Brass::FrenchHorn, FrenchHornName);
        menu.addItem(Brass::Trumpet, TrumpetName);
        menu.addItem(Brass::TenorTrombone, TenorTromboneName);
        menu.addItem(Brass::BassTrombone, BassTromboneName);
        menu.addItem(Brass::Cimbasso, CimbassoName);
        menu.addItem(Brass::Tuba, TubaName);
    }
    else if (topLevelMenuIndex == 3) //Percussion
    {
        menu.addItem(Percussion::Celeste, CelesteName);
        menu.addItem(Percussion::Harp, HarpName);
        menu.addItem(Percussion::Timpani, TimpaniName);
        menu.addItem(Percussion::Marimba, MarimbaName);
    }

    return menu;
}


void InstrumentInfoView::menuItemSelected(int menuItemID, int topLevelMenuIndex)
{
    if (topLevelMenuIndex == 0) //Strings family selected
    {
        showStringsInstrument(menuItemID);
    }
}


void InstrumentInfoView::displayInstrument(int family, int instrument)
{
    switch (family)
    {
    case (Family::Default):
    {
        mCurrentFamily = Family::Default;
        mCurrentSelectedInstrument = defaultInstrument;
        break;
    }

    case (Family::Strings):
    {
        mCurrentFamily = Family::Strings;
        
        break;
    }

    case (Family::Brass):
    {
        mCurrentFamily = Family::Brass;
        break;
    }

    case (Family::Woodwinds):
    {
        mCurrentFamily = Family::Woodwinds;
        break;
    }

    case (Family::Percussion):
    {
        mCurrentFamily = Family::Percussion;
        break;
    }

    default: break;
    }
}


void InstrumentInfoView::showStringsInstrument(int instrument)
{
    showText(mPlayingTechniques, stringsPlayingTechniques);

    switch (instrument)
    {
    
    case (Strings::Violin):
    {
        showText(mRange, violinRange);
        showText(mQualities, violinQualities);
        showText(mRoles, violinRoles);
        showText(mFamousWorks, violinFamousWorks);
        showText(mTransposition, violinTransposition);
        break;
    }

    case (Strings::Viola):
    {
        showText(mRange, violaRange);
        showText(mQualities, violaQualities);
        showText(mRoles, violaRoles);
        showText(mFamousWorks, violaFamousWorks);
        showText(mTransposition, violaTransposition);
        break;
    }

    case (Strings::Violoncello):
    {
        break;
    }

    case (Strings::DoubleBass):
    {
        break;
    }

    default: break;

    }
}


void InstrumentInfoView::showBrassInstrument(int instrument)
{
    switch (instrument)
    {

    case (Brass::FrenchHorn):
    {
        break;
    }

    case (Brass::Trumpet):
    {
        break;
    }

    case (Brass::TenorTrombone):
    {
        break;
    }

    case (Brass::BassTrombone):
    {
        break;
    }

    case (Brass::Cimbasso):
    {
        break;
    }

    case (Brass::Tuba):
    {
        break;
    }

    default: break;

    }
}


void InstrumentInfoView::showPercussionInstrument(int instrument)
{
    switch (instrument)
    {

    case (Percussion::Harp):
    {
        break;
    }

    case (Percussion::Celeste):
    {
        break;
    }

    case (Percussion::Timpani):
    {
        break;
    }

    case (Percussion::Marimba):
    {
        break;
    }

    default: break;

    }
}


void InstrumentInfoView::showWoodwindInstrument(int instrument)
{
    switch (instrument)
    {

    case (Woodwinds::Piccolo):
    {
        break;
    }

    case (Woodwinds::Flute):
    {
        break;
    }

    case (Woodwinds::Oboe):
    {
        break;
    }

    case (Woodwinds::CorAnglais):
    {
        break;
    }   
    
    case (Woodwinds::Clarinet):
    {
        break;
    }    
    
    case (Woodwinds::BassClarinet):
    {
        break;
    }

    case (Woodwinds::Basson):
    {
        break;
    }

    case (Woodwinds::Contrabassoon):
    {
        break;
    }

    default: break;

    }
}

void InstrumentInfoView::showText(TextEditor &destinationEditor, StringArray textToShow)
{
    destinationEditor.clear();

    for (auto& info : textToShow)
    {
        destinationEditor.moveCaretToEnd();
        destinationEditor.insertTextAtCaret(info + newLine);
    }
}


void InstrumentInfoView::showText(TextEditor& destinationEditor, String textToShow)
{
    destinationEditor.clear();
    destinationEditor.moveCaretToEnd();
    destinationEditor.insertTextAtCaret(textToShow);
}


void InstrumentInfoView::setupTextEditor(TextEditor& editorToSetup)
{
    addAndMakeVisible(&editorToSetup);
    editorToSetup.setMultiLine(true);
    editorToSetup.setReturnKeyStartsNewLine(true);
    editorToSetup.setReadOnly(true);
    editorToSetup.setScrollbarsShown(true);
    editorToSetup.setCaretVisible(false);
    editorToSetup.setPopupMenuEnabled(true);
}