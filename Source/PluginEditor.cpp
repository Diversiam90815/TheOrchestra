
#include "PluginProcessor.h"
#include "PluginEditor.h"


OrchestraEditor::OrchestraEditor (OrchestraProcessor& proc)
    : AudioProcessorEditor (&proc), audioProcessor (proc), mPianoRollView()
{
    showUI();
}


OrchestraEditor::~OrchestraEditor()
{
}


void OrchestraEditor::showUI()
{
    addAndMakeVisible(mPianoRollView);
    addAndMakeVisible(mInstrumentInfoView);

    mMenuBar.setModel(&mInstrumentInfoView);
    addAndMakeVisible(mMenuBar);

    setSize(900, 700);
}


void OrchestraEditor::paint (Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
}


void OrchestraEditor::resized()
{
    mPianoRollView.setBoundsRelative(0.0f, 0.85f, 1.0f, 0.15f);
    mInstrumentInfoView.setBoundsRelative(0.01f, 0.05f, 0.98f, 0.8f);
    mMenuBar.setBounds(getLocalBounds().removeFromTop(juce::LookAndFeel::getDefaultLookAndFeel().getDefaultMenuBarHeight()));
}
