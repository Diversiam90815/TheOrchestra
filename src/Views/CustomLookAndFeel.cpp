/*
  ==============================================================================

	Module			CustomLookAndFeel
	Description		Customizing the LookNFeel class used by the Editor

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


Colour CustomLookAndFeel::getBoxBackgroundColour() const
{
	return boxesBackground;
}


float CustomLookAndFeel::getCornerRadius() const
{
	return mCornerRadius;
}


void CustomLookAndFeel::init()
{
	// Set different colours
	setColour(ResizableWindow::backgroundColourId, background);
	setColour(Label::textColourId, fontColor);

	setColour(PopupMenu::backgroundColourId, Colours::black);
	setColour(PopupMenu::highlightedBackgroundColourId, menuBarBackground);
	setColour(PopupMenu::highlightedTextColourId, whiteFontColour);
	setColour(PopupMenu::textColourId, fontColor);
}


void CustomLookAndFeel::setFont()
{
	auto fontData = Binary
}


void CustomLookAndFeel::drawLabel(Graphics &g, Label &label)
{
	String labelName = label.getName();

	if (labelName.contains("Title") || labelName.contains("NoteName"))
	{
		g.fillAll(label.findColour(Label::backgroundColourId));
		g.setColour(label.findColour(Label::textColourId));
		g.setFont(headerFont);
		g.drawText(label.getText(), label.getLocalBounds(), Justification::centred, true);
	}
	else
	{
		g.fillAll(label.findColour(Label::backgroundColourId));
		g.setColour(label.findColour(Label::textColourId));
		g.setFont(infoTextFont);
		g.drawText(label.getText(), label.getLocalBounds(), Justification::centredLeft, false);
	}
}


void CustomLookAndFeel::drawMenuBarBackground(Graphics &g, int width, int height, bool isMouseOverBar, MenuBarComponent &menuBar)
{
	g.fillAll(menuBarBackground);

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
