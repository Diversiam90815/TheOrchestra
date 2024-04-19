/*
  ==============================================================================

    CustomLookAndFeel.h
    Created: 19 Apr 2024 9:12:16am
    Author:  Jens.Langenberg

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class CustomLookAndFeel : public juce::LookAndFeel_V4 
{
public:
    CustomLookAndFeel();
    ~CustomLookAndFeel();

private:
    void drawLabel(juce::Graphics& g, juce::Label& label) override;

    void drawTextEditorOutline(juce::Graphics& g, int width, int height, juce::TextEditor& textEditor) override;
};
