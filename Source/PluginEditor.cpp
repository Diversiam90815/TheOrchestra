
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
    mPianoRollView.setBoundsRelative(0.0f, 0.8f, 1.0f, 0.2f);
    mInstrumentInfoView.setBoundsRelative(0.01f, 0.08f, 0.98f, 0.5f);
    mMenuBar.setBounds(getLocalBounds().removeFromTop(juce::LookAndFeel::getDefaultLookAndFeel().getDefaultMenuBarHeight()));
}
