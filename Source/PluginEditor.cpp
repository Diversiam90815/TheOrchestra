
#include "PluginProcessor.h"
#include "PluginEditor.h"


OrchestraEditor::OrchestraEditor (OrchestraProcessor& proc)
    : AudioProcessorEditor (&proc), audioProcessor (proc), mPianoRollView(), mInstrumentInfoView(*mPianoRollView.mPianoRoll.get())
{
    showUI();
    setLookAndFeel(&mCustomLookAndFeel);
}


OrchestraEditor::~OrchestraEditor()
{
    setLookAndFeel(nullptr);
}


void OrchestraEditor::showUI()
{
    addAndMakeVisible(mPianoRollView);
    addAndMakeVisible(mInstrumentInfoView);

    mMenuBar.setModel(&mInstrumentInfoView);
    addAndMakeVisible(mMenuBar);

    setSize(1000, 800);
}


void OrchestraEditor::paint (Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
}


void OrchestraEditor::resized()
{
    mPianoRollView.setBoundsRelative(0.0f, 0.9f, 1.0f, 0.1f);
    mInstrumentInfoView.setBoundsRelative(0.01f, 0.05f, 0.98f, 0.8f);
    mMenuBar.setBounds(getLocalBounds().removeFromTop(mCustomLookAndFeel.getDefaultMenuBarHeight()));
}