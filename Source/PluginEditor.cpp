
#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
InstrumentsOfTheOrcehstraAudioProcessorEditor::InstrumentsOfTheOrcehstraAudioProcessorEditor (InstrumentsOfTheOrcehstraAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);
}

InstrumentsOfTheOrcehstraAudioProcessorEditor::~InstrumentsOfTheOrcehstraAudioProcessorEditor()
{
}

//==============================================================================
void InstrumentsOfTheOrcehstraAudioProcessorEditor::paint (Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
}

void InstrumentsOfTheOrcehstraAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}
