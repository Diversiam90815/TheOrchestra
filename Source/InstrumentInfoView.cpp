/*
  ==============================================================================

    InstrumentInfoView.cpp
    Created: 8 Apr 2024 6:24:22pm
    Author:  Jens.Langenberg

  ==============================================================================
*/

#include "InstrumentInfoView.h"


InstrumentInfoView::InstrumentInfoView(CustomPianoRoll& piano) : mCustomPianoRoll(piano)
{
    displayTextBoxes();
    displayLabels();
}


InstrumentInfoView::~InstrumentInfoView()
{

}


void InstrumentInfoView::displayTextBoxes()
{
    setupTextEditor(mRange);
    setupTextEditor(mRoles);
    setupTextEditor(mQualities);
    setupTextEditor(mTransposition);
    setupTextEditor(mPlayingTechniques);
    setupTextEditor(mFamousWorks);

    mRange.setTextToShowWhenEmpty("Range", Colours::beige);
    mRoles.setTextToShowWhenEmpty("Roles within the Orchestra", Colours::beige);
    mQualities.setTextToShowWhenEmpty("Qualities", Colours::beige);
    mTransposition.setTextToShowWhenEmpty("Transposition", Colours::beige);
    mFamousWorks.setTextToShowWhenEmpty("Famous Works", Colours::beige);
    mPlayingTechniques.setTextToShowWhenEmpty("Playing Techniques", Colours::beige);
}


void InstrumentInfoView::displayLabels()
{
    setupLabel(mInstrument, "Instrument");
    setupLabel(mRangeTitle, "Ranges");
    setupLabel(mQualitiesTitle, "Qualities");
    setupLabel(mFamousWorksTitle, "Famous Works");
    setupLabel(mPlayingTechniquesTitle, "Playing Techniques");
    setupLabel(mRolesTitle, "Roles");
    setupLabel(mTranspositionTitle, "Transposition");
}


void InstrumentInfoView::resized()
{
    // Assuming mLabel takes up about 10% of the height for the title, as before.
    float titleLabelHeight = 0.1f;

    // Adjusting for the addition of title labels. Assuming each title label takes up a small percentage of the height.
    // You can adjust the titleHeightPercentage as needed.
    float titleHeightPercentage = 0.05f; // Example height for title labels

    // Adjust the height for the TextEditors, now divided by 3 rows, subtracting the space needed for titles.
    float textEditorHeight = (1.0f - titleLabelHeight - (titleHeightPercentage * 6)) / 3; // Now for 3 rows, 6 titles.

    // Set bounds for mLabel centered horizontally at the top.
    mInstrument.setBoundsRelative(0.25f, 0.0f, 0.5f, titleLabelHeight);

    // Calculate Y positions where the titles will start.
    float firstRowTitlesY = titleLabelHeight;
    float firstRowYStart = firstRowTitlesY + titleHeightPercentage;

    // First row of Titles and TextEditors
    mRangeTitle.setBoundsRelative(0.0f, firstRowTitlesY, 0.5f, titleHeightPercentage);
    mRolesTitle.setBoundsRelative(0.5f, firstRowTitlesY, 0.5f, titleHeightPercentage);
    mRange.setBoundsRelative(0.0f, firstRowYStart, 0.5f, textEditorHeight);
    mRoles.setBoundsRelative(0.5f, firstRowYStart, 0.5f, textEditorHeight);

    // Calculate the starting Y position for the second row titles and TextEditors
    float secondRowTitlesY = firstRowYStart + textEditorHeight;
    float secondRowYStart = secondRowTitlesY + titleHeightPercentage;

    // Second row of Titles and TextEditors
    mQualitiesTitle.setBoundsRelative(0.0f, secondRowTitlesY, 0.5f, titleHeightPercentage);
    mTranspositionTitle.setBoundsRelative(0.5f, secondRowTitlesY, 0.5f, titleHeightPercentage);
    mQualities.setBoundsRelative(0.0f, secondRowYStart, 0.5f, textEditorHeight);
    mTransposition.setBoundsRelative(0.5f, secondRowYStart, 0.5f, textEditorHeight);

    // Calculate the starting Y position for the third row titles and TextEditors
    float thirdRowTitlesY = secondRowYStart + textEditorHeight;
    float thirdRowYStart = thirdRowTitlesY + titleHeightPercentage;

    // Third row of Titles and TextEditors
    mPlayingTechniquesTitle.setBoundsRelative(0.0f, thirdRowTitlesY, 0.5f, titleHeightPercentage);
    mFamousWorksTitle.setBoundsRelative(0.5f, thirdRowTitlesY, 0.5f, titleHeightPercentage);
    mPlayingTechniques.setBoundsRelative(0.0f, thirdRowYStart, 0.5f, textEditorHeight);
    mFamousWorks.setBoundsRelative(0.5f, thirdRowYStart, 0.5f, textEditorHeight);
}



StringArray InstrumentInfoView::getMenuBarNames()
{
    return {"Woodwinds", "Brass", "Strings", "Percussion" };
}


PopupMenu InstrumentInfoView::getMenuForIndex(int topLevelMenuIndex, const String& menuName)
{
    PopupMenu menu;

    if (topLevelMenuIndex == 0) // Woodwinds
    {
        menu.addItem(Woodwinds::Piccolo, PiccoloName);
        menu.addItem(Woodwinds::Flute, FluteName);
        menu.addItem(Woodwinds::Oboe, OboeName);
        menu.addItem(Woodwinds::CorAnglais, CorAnglaisName);
        menu.addItem(Woodwinds::Clarinet, ClarinetName);
        menu.addItem(Woodwinds::BassClarinet, BassClarinetName);
        menu.addItem(Woodwinds::Basson, BassoonName);
        menu.addItem(Woodwinds::Contrabassoon, ContrabassonName);
    }
    else if (topLevelMenuIndex == 1) //Brass
    {
        menu.addItem(Brass::FrenchHorn, FrenchHornName);
        menu.addItem(Brass::Trumpet, TrumpetName);
        menu.addItem(Brass::TenorTrombone, TenorTromboneName);
        menu.addItem(Brass::BassTrombone, BassTromboneName);
        menu.addItem(Brass::Cimbasso, CimbassoName);
        menu.addItem(Brass::Tuba, TubaName);
    }
    else if (topLevelMenuIndex == 2) // Strings
    {
        menu.addItem(Strings::Violin, ViolinName);
        menu.addItem(Strings::Viola, ViolaName);
        menu.addItem(Strings::Violoncello, VioloncelloName);
        menu.addItem(Strings::DoubleBass, DoubleBassName);
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
    int key = (topLevelMenuIndex + 1) * 100 + menuItemID;
    showInstrumentInfo(key);
}


void InstrumentInfoView::showInstrumentInfo(int key)
{    
    auto info = mInstrumentModel.getInstrument(key);
    mInstrument.setText(info.mName,dontSendNotification);

    showText(mRange, info.mRange);
    showText(mQualities, info.mQualities);
    showText(mRoles, info.mRoles);
    showText(mFamousWorks, info.mFamousWorks);
    showText(mTransposition, info.mTransposition);
    showText(mPlayingTechniques, info.mPlayingTechniques);

    mCustomPianoRoll.setMidiRanges(info.mQualities);
    mCustomPianoRoll.repaint();
}


void InstrumentInfoView::showText(TextEditor& destinationEditor, StringArray textToShow)
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
    destinationEditor.moveCaretToTop(false);
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

void InstrumentInfoView::setupLabel(Label& labelToSetup, const String& title)
{
    addAndMakeVisible(&labelToSetup);
    labelToSetup.setText(title, dontSendNotification);
    labelToSetup.setFont(Font(16.0f, Font::bold));
    labelToSetup.setJustificationType(Justification::centred);
}
