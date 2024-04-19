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
    setColour(TextEditor::backgroundColourId, Colour(0xff222222));
    setColour(TextEditor::textColourId, Colours::white);
    setColour(TextEditor::outlineColourId, Colours::grey);
    setColour(Label::textColourId, Colours::aquamarine);

}


CustomLookAndFeel::~CustomLookAndFeel()
{

}


void CustomLookAndFeel::drawLabel(Graphics& g, Label& label)
{
    g.fillAll(label.findColour(Label::backgroundColourId));
    g.setColour(label.findColour(Label::textColourId));
    g.setFont(Font("Arial", 16.0f, Font::bold));
    g.drawText(label.getText(), label.getLocalBounds(), Justification::centred, true);
}


void CustomLookAndFeel::drawTextEditorOutline(Graphics& g, int width, int height, TextEditor& textEditor)
{
    g.setColour(textEditor.findColour(TextEditor::outlineColourId));
    g.drawRect(0, 0, width, height, 1); // Thin outline with a thickness of 1 pixel
}