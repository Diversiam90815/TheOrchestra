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


juce::Colour CustomLookAndFeel::getBoxBackgroundColour() const
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
	setColour(juce::ResizableWindow::backgroundColourId, background);
	setColour(juce::Label::textColourId, fontColor);

	setColour(juce::PopupMenu::backgroundColourId, juce::Colours::black);
	setColour(juce::PopupMenu::highlightedBackgroundColourId, menuBarBackground);
	setColour(juce::PopupMenu::highlightedTextColourId, whiteFontColour);
	setColour(juce::PopupMenu::textColourId, fontColor);

	setColour(juce::ComboBox::backgroundColourId, comboBoxBackground);

	setFont();
}


void CustomLookAndFeel::setFont()
{
	// Load the custom typeface from BinaryData
	instrumentTypeface = juce::Typeface::createSystemTypefaceFor(BinaryData::InstrumentSerifRegular_ttf, BinaryData::InstrumentSerifRegular_ttfSize);

	// Set the font
	headerFont		   = juce::Font(instrumentTypeface).withHeight(27.0f);
	noteNameFonts	   = juce::Font(instrumentTypeface).withHeight(25.0f);
	menuFont		   = juce::Font(instrumentTypeface).withHeight(27.0f);
	infoTextFont	   = juce::Font(instrumentTypeface).withHeight(22.0f);
	textEditorFont	   = juce::Font(instrumentTypeface).withHeight(20.0f);
	tooltipFont		   = juce::Font(instrumentTypeface).withHeight(20.0f);

	headerFont.setExtraKerningFactor(0.003f);
	noteNameFonts.setExtraKerningFactor(0.003f);
	menuFont.setExtraKerningFactor(0.003f);
	infoTextFont.setExtraKerningFactor(0.003f);
	tooltipFont.setExtraKerningFactor(0.003f);
	textEditorFont.setExtraKerningFactor(0.003f);
}


void CustomLookAndFeel::drawLabel(juce::Graphics &g, juce::Label &label)
{
	juce::String labelName = label.getName();

	if (labelName.contains("Title") || labelName.contains("NoteName"))
	{
		g.fillAll(label.findColour(juce::Label::backgroundColourId));
		g.setColour(label.findColour(juce::Label::textColourId));
		g.setFont(headerFont);
		g.drawText(label.getText(), label.getLocalBounds(), juce::Justification::centred, true);
	}
	else
	{
		g.fillAll(label.findColour(juce::Label::backgroundColourId));
		g.setColour(label.findColour(juce::Label::textColourId));
		g.setFont(infoTextFont);
		g.drawText(label.getText(), label.getLocalBounds(), juce::Justification::centredLeft, false);
	}
}


void CustomLookAndFeel::drawMenuBarBackground(juce::Graphics &g, int width, int height, bool isMouseOverBar, juce::MenuBarComponent &menuBar)
{
	g.fillAll(menuBarBackground);
	g.fillRect(0, 0, width, height);
}


void CustomLookAndFeel::drawPopupMenuItem(juce::Graphics			 &g,
										  const juce::Rectangle<int> &area,
										  const bool				  isSeparator,
										  const bool				  isActive,
										  const bool				  isHighlighted,
										  const bool				  isTicked,
										  const bool				  hasSubMenu,
										  const juce::String		 &text,
										  const juce::String		 &shortcutKeyText,
										  const juce::Drawable		 *icon,
										  const juce::Colour		 *textColour)
{
	juce::Colour		 baseColour = findColour(juce::PopupMenu::backgroundColourId);
	juce::ColourGradient gradient(baseColour, 0, 0, baseColour.darker(0.1f), 0, float(area.getHeight()), false);

	if (isHighlighted)
	{
		gradient = juce::ColourGradient(findColour(juce::PopupMenu::highlightedBackgroundColourId), 0, 0, findColour(juce::PopupMenu::highlightedBackgroundColourId).darker(0.2f),
										0, float(area.getHeight()), false);
	}
	g.setGradientFill(gradient);
	g.fillRect(area);

	g.setColour(isHighlighted ? findColour(juce::PopupMenu::highlightedTextColourId) : findColour(juce::PopupMenu::textColourId));
	g.setFont(getPopupMenuFont());
	g.drawText(text, area.reduced(10, 0), juce::Justification::centred, true);
}


void CustomLookAndFeel::drawButtonBackground(
	juce::Graphics &g, juce::Button &button, const juce::Colour &backgroundColour, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown)
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
		juce::Path path;
		path.addRoundedRectangle(bounds.getX(), bounds.getY(), bounds.getWidth(), bounds.getHeight(), cornerSize, cornerSize, !(flatOnLeft || flatOnTop),
								 !(flatOnRight || flatOnTop), !(flatOnLeft || flatOnBottom), !(flatOnRight || flatOnBottom));

		g.fillPath(path);

		g.setColour(button.findColour(juce::ComboBox::outlineColourId));
		g.strokePath(path, juce::PathStrokeType(1.0f));
	}
	else
	{
		g.fillRoundedRectangle(bounds, cornerSize);

		g.setColour(button.findColour(juce::ComboBox::outlineColourId));
		g.drawRoundedRectangle(bounds, cornerSize, 1.0f);
	}
}


void CustomLookAndFeel::drawTooltip(juce::Graphics &g, const juce::String &text, int width, int height)
{
	g.setColour(tooltipWindowBackground);
	g.fillRoundedRectangle(0, 0, (float)tooltipWidth, (float)tooltipHeight, mCornerRadius);

	juce::TextLayout tl = layoutTooltipText(text);
	tl.draw(g, juce::Rectangle<float>(5.0f, 0.0f, (float)tooltipWidth - 10.0f, (float)tooltipHeight - 6.0f));
}


juce::TextLayout CustomLookAndFeel::layoutTooltipText(const juce::String &text) const noexcept
{
	juce::AttributedString s;
	s.setJustification(juce::Justification::centredLeft);
	s.append(text, tooltipFont, tooltipFontColour);
	s.setLineSpacing(1.05);

	juce::TextLayout tl;
	tl.createLayout(s, (float)tooltipWidth - 10.0f);
	return tl;
}


void CustomLookAndFeel::drawTextEditorOutline(juce::Graphics &g, int width, int height, juce::TextEditor &textEditor)
{
	g.setColour(juce::Colours::transparentBlack);
	g.drawRect(0, 0, width, height);
}


void CustomLookAndFeel::fillTextEditorBackground(juce::Graphics &g, int width, int height, juce::TextEditor &textEditor)
{
	g.setColour(juce::Colours::transparentBlack);
	g.fillRect(0, 0, width, height);
}


juce::Font CustomLookAndFeel::getTextEditorFont()
{
	return textEditorFont;
}


std::vector<juce::Colour> CustomLookAndFeel::getQualityColours()
{
	std::vector<juce::Colour> qualityColours;
	qualityColours.reserve(4);

	// Add brighter versions for the colours for the piano roll
	qualityColours.push_back(firstQualityColour.brighter());
	qualityColours.push_back(secondQualityColour.brighter());
	qualityColours.push_back(thirdQualityColour.brighter());
	qualityColours.push_back(fourthQualityColour.brighter());

	return qualityColours;
}
