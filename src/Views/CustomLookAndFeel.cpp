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


CustomLookAndFeel::~CustomLookAndFeel() {}


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

	setColour(ComboBox::backgroundColourId, comboBoxBackground);

	setFont();
}


void CustomLookAndFeel::setFont()
{
	// Load the custom typeface from BinaryData
	instrumentTypeface = Typeface::createSystemTypefaceFor(BinaryData::InstrumentSerifRegular_ttf, BinaryData::InstrumentSerifRegular_ttfSize);

	// Set the font
	headerFont		   = Font(instrumentTypeface).withHeight(27.0f);
	noteNameFonts	   = Font(instrumentTypeface).withHeight(25.0f);
	menuFont		   = Font(instrumentTypeface).withHeight(27.0f);
	infoTextFont	   = Font(instrumentTypeface).withHeight(22.0f);
	qualityTextFont	   = Font(instrumentTypeface).withHeight(20.0f);
	tooltipFont		   = Font(instrumentTypeface).withHeight(20.0f);

	headerFont.setExtraKerningFactor(0.003f);
	noteNameFonts.setExtraKerningFactor(0.003f);
	menuFont.setExtraKerningFactor(0.003f);
	infoTextFont.setExtraKerningFactor(0.003f);
	tooltipFont.setExtraKerningFactor(0.003f);
	qualityTextFont.setExtraKerningFactor(0.003f);
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


void CustomLookAndFeel::drawButtonBackground(Graphics &g, Button &button, const Colour &backgroundColour, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown)
{
	auto cornerSize = 6.0f;
	auto bounds		= button.getLocalBounds().toFloat().reduced(0.5f, 0.5f);

	if (button.getName().contains("FirstQuality"))
	{
		g.setColour(firstQualityColour);
	}

	else if (button.getName().contains("SecondQuality"))
	{
		g.setColour(secondQualityColour);
	}

	else if (button.getName().contains("ThirdQuality"))
	{
		g.setColour(thirdQualityColour);
	}

	else if (button.getName().contains("FourthQuality"))
	{
		g.setColour(fourthQualityColour);
	}

	else
	{
		g.setColour(techniqueButtonColour);
	}

	auto flatOnLeft	  = button.isConnectedOnLeft();
	auto flatOnRight  = button.isConnectedOnRight();
	auto flatOnTop	  = button.isConnectedOnTop();
	auto flatOnBottom = button.isConnectedOnBottom();

	if (flatOnLeft || flatOnRight || flatOnTop || flatOnBottom)
	{
		Path path;
		path.addRoundedRectangle(bounds.getX(), bounds.getY(), bounds.getWidth(), bounds.getHeight(), cornerSize, cornerSize, !(flatOnLeft || flatOnTop),
								 !(flatOnRight || flatOnTop), !(flatOnLeft || flatOnBottom), !(flatOnRight || flatOnBottom));

		g.fillPath(path);

		g.setColour(button.findColour(ComboBox::outlineColourId));
		g.strokePath(path, PathStrokeType(1.0f));
	}
	else
	{
		g.fillRoundedRectangle(bounds, cornerSize);

		g.setColour(button.findColour(ComboBox::outlineColourId));
		g.drawRoundedRectangle(bounds, cornerSize, 1.0f);
	}
}


void CustomLookAndFeel::drawTooltip(Graphics &g, const String &text, int width, int height)
{
	Rectangle<int> bounds(tooltipWidth, tooltipHeight);

	g.setColour(tooltipWindowBackground);
	g.fillRoundedRectangle(bounds.toFloat(), mCornerRadius);

	TextLayout tl = layoutTooltipText(text);
	tl.draw(g, bounds.toFloat());
}


TextLayout CustomLookAndFeel::layoutTooltipText(const String &text) const noexcept
{
	AttributedString s;
	s.setJustification(Justification::centredLeft);
	s.append(text, tooltipFont, tooltipFontColour);

	TextLayout tl;
	tl.createLayoutWithBalancedLineLengths(s, (float)tooltipWidth);
	return tl;
}


void CustomLookAndFeel::drawTextEditorOutline(Graphics &g, int width, int height, TextEditor &textEditor)
{
	g.setColour(Colours::transparentBlack);
	g.drawRect(0, 0, width, height);
}


void CustomLookAndFeel::fillTextEditorBackground(Graphics &g, int width, int height, TextEditor &textEditor)
{
	g.setColour(Colours::transparentBlack);
	g.fillRect(0, 0, width, height);
}


Font CustomLookAndFeel::getTextEditorFont()
{
	return qualityTextFont;
}


std::vector<Colour> CustomLookAndFeel::getQualityColours()
{
	std::vector<Colour> qualityColours;
	qualityColours.reserve(4);

	// Add brighter versions for the colours for the piano roll
	qualityColours.push_back(firstQualityColour.brighter());
	qualityColours.push_back(secondQualityColour.brighter());
	qualityColours.push_back(thirdQualityColour.brighter());
	qualityColours.push_back(fourthQualityColour.brighter());

	return qualityColours;
}
