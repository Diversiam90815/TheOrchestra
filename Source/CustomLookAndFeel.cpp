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
	init();
}


CustomLookAndFeel::~CustomLookAndFeel()
{
}


void CustomLookAndFeel::init()
{
	// Set default font
	setDefaultSansSerifTypefaceName("Lato"); // A modern, readable font that works well for UI

	// Set different colours
	setColour(ResizableWindow::backgroundColourId, Colour(0xFF2A2F36)); // Deep blue-gray
	setColour(TextEditor::backgroundColourId, Colour(0xFF1E1E1E));		// Dark charcoal
	setColour(TextEditor::textColourId, Colour(0xFFF0F0F0));			// Off-white for high contrast readability
	setColour(TextEditor::outlineColourId, Colour(0xFF404040));			// Slightly lighter grey for outlines
	setColour(Label::textColourId, Colour(0xFF4CAF50));					// A refreshing green that stands out yet is soft
	setColour(PopupMenu::backgroundColourId, Colours::black);
	setColour(PopupMenu::highlightedBackgroundColourId, Colours::black.brighter(0.5f));
	setColour(PopupMenu::highlightedTextColourId, Colours::white);
	setColour(PopupMenu::textColourId, Colours::lightgrey);

	// Configure fonts
	infoFont.setTypefaceName("Lato");
	infoFont.setHeight(16);

	titleFont.setTypefaceName("Lato");
	titleFont.setBold(true);
	titleFont.setHeight(20);

	popupmenuFont.setTypefaceName("Lato");
	popupmenuFont.setHeight(16);
}


void CustomLookAndFeel::drawLabel(Graphics &g, Label &label)
{
	String labelName = label.getName();

	if (labelName.contains("Title"))
	{
		g.fillAll(label.findColour(Label::backgroundColourId));
		g.setColour(label.findColour(Label::textColourId));
		g.setFont(titleFont);
		g.drawText(label.getText(), label.getLocalBounds(), Justification::centred, true);
	}
	else
	{
		g.fillAll(label.findColour(Label::backgroundColourId));
		g.setColour((Colours::white));
		g.setFont(infoFont);
		g.drawText(label.getText(), label.getLocalBounds(), Justification::centredLeft, false);
	}
}


void CustomLookAndFeel::drawTextEditorOutline(Graphics &g, int width, int height, TextEditor &textEditor)
{
	g.setColour(textEditor.findColour(TextEditor::outlineColourId));
	g.setFont(infoFont);
	g.drawRect(0, 0, width, height, 1); // Thin outline with a thickness of 1 pixel
}


Font CustomLookAndFeel::getEditorFont()
{
	return infoFont;
}


void CustomLookAndFeel::drawMenuBarBackground(Graphics &g, int width, int height, bool isMouseOverBar, MenuBarComponent &menuBar)
{
	// Simple solid color background
	g.fillAll(Colours::black);

	// Optionally add a subtle gradient
	ColourGradient gradient(Colours::darkgrey, 0, 0, Colours::black, 0, (float)height, false);
	g.setGradientFill(gradient);
	g.fillRect(0, 0, width, height);
}


void CustomLookAndFeel::drawPopupMenuItem(Graphics			   &g,
										  const Rectangle<int> &area,
										  const bool			isSeparator,
										  const bool			isActive,
										  const bool			isHighlighted,
										  const bool			isTicked,
										  const bool			hasSubMenu,
										  const String		   &text,
										  const String		   &shortcutKeyText,
										  const Drawable	   *icon,
										  const Colour		   *textColour)
{
	Colour		   baseColour = findColour(PopupMenu::backgroundColourId);
	ColourGradient gradient(baseColour, 0, 0, baseColour.darker(0.1f), 0, float(area.getHeight()), false);

	if (isHighlighted)
	{
		gradient = ColourGradient(findColour(PopupMenu::highlightedBackgroundColourId), 0, 0, findColour(PopupMenu::highlightedBackgroundColourId).darker(0.2f), 0,
								  float(area.getHeight()), false);
	}
	g.setGradientFill(gradient);
	g.fillRect(area);

	g.setColour(isHighlighted ? findColour(PopupMenu::highlightedTextColourId) : findColour(PopupMenu::textColourId));
	g.setFont(getPopupMenuFont());
	g.drawText(text, area.reduced(10, 0), Justification::centred, true);
}


Font CustomLookAndFeel::getPopupMenuFont()
{
	return popupmenuFont;
}