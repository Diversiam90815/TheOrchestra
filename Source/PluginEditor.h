
#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class InstrumentsOfTheOrcehstraAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    InstrumentsOfTheOrcehstraAudioProcessorEditor (InstrumentsOfTheOrcehstraAudioProcessor&);
    ~InstrumentsOfTheOrcehstraAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    InstrumentsOfTheOrcehstraAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (InstrumentsOfTheOrcehstraAudioProcessorEditor)
};
