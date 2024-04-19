/*
  ==============================================================================

    CustomLookAndFeel.h
    Created: 19 Apr 2024 9:12:16am
    Author:  Jens.Langenberg

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class CustomLookAndFeel : public LookAndFeel_V4 
{
public:
    CustomLookAndFeel();
    ~CustomLookAndFeel();

    Font getEditorFont();

private:
    void init();

    void drawLabel(Graphics& g, Label& label) override;

    void drawTextEditorOutline(Graphics& g, int width, int height, TextEditor& textEditor) override;

    Font textEditorFont;
    Font labelFont;
};
