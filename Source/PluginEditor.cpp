
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

    setSize(700, 500);
}


void OrchestraEditor::paint (Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
}


void OrchestraEditor::resized()
{
    mPianoRollView.setBoundsRelative(0.0f, 0.7f, 1.0f, 0.2f);

}
