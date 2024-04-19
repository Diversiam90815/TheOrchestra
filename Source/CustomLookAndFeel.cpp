/*
  ==============================================================================

    CustomLookAndFeel.cpp
    Created: 19 Apr 2024 9:12:16am
    Author:  Jens.Langenberg

  ==============================================================================
*/

#include "CustomLookAndFeel.h"

CustomLookAndFeel::CustomLookAndFeel()
{
    // Set default font
    setDefaultSansSerifTypefaceName("Arial");

    // Set some color schemes for general UI elements
    setColour(juce::TextEditor::backgroundColourId, juce::Colour(0xff222222));
    setColour(juce::TextEditor::textColourId, juce::Colours::white);
    setColour(juce::TextEditor::outlineColourId, juce::Colours::grey);
    setColour(juce::Label::textColourId, juce::Colours::aquamarine);

    // You can add more component-specific colors and settings here
}


CustomLookAndFeel::~CustomLookAndFeel()
{

}


void CustomLookAndFeel::drawLabel(juce::Graphics& g, juce::Label& label)
{
    g.fillAll(label.findColour(juce::Label::backgroundColourId));
    g.setColour(label.findColour(juce::Label::textColourId));
    g.setFont(juce::Font("Arial", 16.0f, juce::Font::bold));
    g.drawText(label.getText(), label.getLocalBounds(), juce::Justification::centredLeft, true);
}


void CustomLookAndFeel::drawTextEditorOutline(juce::Graphics& g, int width, int height, juce::TextEditor& textEditor)
{
    g.setColour(textEditor.findColour(juce::TextEditor::outlineColourId));
    g.drawRect(0, 0, width, height, 1); // Thin outline with a thickness of 1 pixel
}