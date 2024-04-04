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
    //menuBar.setModel(this);
    //addAndMakeVisible(menuBar);

    displayTextBoxes();
}


InstrumentInfoView::~InstrumentInfoView()
{

}


void InstrumentInfoView::displayTextBoxes()
{
    addAndMakeVisible(mLabel);
    addAndMakeVisible(mCommonTechniques);
    addAndMakeVisible(mRoles);
    addAndMakeVisible(mQualities);
    addAndMakeVisible(mTransposition);
    
    mLabel.setTextToShowWhenEmpty("Instrument",Colours::beige);
    mCommonTechniques.setTextToShowWhenEmpty("Techniques", Colours::beige);
    mRoles.setTextToShowWhenEmpty("Roles within the Orchestra", Colours::beige);
    mQualities.setTextToShowWhenEmpty("Qualities", Colours::beige);
    mTransposition.setTextToShowWhenEmpty("Transposition", Colours::beige);
}


void InstrumentInfoView::resized()
{
    // Assuming mLabel takes up about 10% of the height for the title.
    float titleLabelHeight = 0.1f;

    // Calculate the height for the TextEditors, considering they need to be bigger and fill the rest of the space.
    float textEditorHeight = (1.0f - titleLabelHeight) / 2; // Divided by 2 rows.

    // Set bounds for mLabel centered horizontally at the top.
    mLabel.setBoundsRelative(0.25f, 0.0f, 0.5f, titleLabelHeight);

    // First row of TextEditors
    mCommonTechniques.setBoundsRelative(0.0f, titleLabelHeight, 0.5f, textEditorHeight);
    mRoles.setBoundsRelative(0.5f, titleLabelHeight, 0.5f, textEditorHeight);

    // Calculate the starting Y position for the second row, considering the height of the first row.
    float secondRowYStart = titleLabelHeight + textEditorHeight;

    // Second row of TextEditors
    mQualities.setBoundsRelative(0.0f, secondRowYStart, 0.5f, textEditorHeight);
    mTransposition.setBoundsRelative(0.5f, secondRowYStart, 0.5f, textEditorHeight);

    //menuBar.setBounds(getLocalBounds().removeFromTop(juce::LookAndFeel::getDefaultLookAndFeel().getDefaultMenuBarHeight()));

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
        menu.addItem(Strings::Contrabass, ContrabassName);
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
    switch (instrument)
    {
    
    case (Strings::Violin):
    {
        break;
    }

    case (Strings::Viola):
    {
        std::cout << "ViolaPicked" << std::endl;
        break;
    }

    case (Strings::Violoncello):
    {
        break;
    }

    case (Strings::Contrabass):
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
