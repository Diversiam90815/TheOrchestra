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


float CustomLookAndFeel::getCornerRadius() const
{
	return mCornerRadius;
}


void CustomLookAndFeel::init()
{
	setColour(juce::ResizableWindow::backgroundColourId, background);
	setColour(juce::Label::textColourId, textPrimary);

	setColour(juce::PopupMenu::backgroundColourId, juce::Colours::black);
	setColour(juce::PopupMenu::highlightedBackgroundColourId, surfaceElevated);
	setColour(juce::PopupMenu::highlightedTextColourId, textPrimary);
	setColour(juce::PopupMenu::textColourId, textSecondary);

	setColour(juce::ComboBox::backgroundColourId, surface);

	setFont();
}


void CustomLookAndFeel::setFont()
{
	instrumentTypeface = juce::Typeface::createSystemTypefaceFor(TextFontData::InstrumentSerifRegular_ttf, TextFontData::InstrumentSerifRegular_ttfSize);

	instrumentNameFont = juce::Font(instrumentTypeface).withHeight(36.0f);
	sectionTitleFont   = juce::Font(instrumentTypeface).withHeight(14.0f);
	bodyFont		   = juce::Font(instrumentTypeface).withHeight(16.0f);
	smallFont		   = juce::Font(instrumentTypeface).withHeight(14.0f);
	textEditorFont	   = juce::Font(instrumentTypeface).withHeight(16.0f);
	tooltipFont		   = juce::Font(instrumentTypeface).withHeight(15.0f);

	instrumentNameFont.setExtraKerningFactor(0.005f);
	sectionTitleFont.setExtraKerningFactor(0.1f);
	bodyFont.setExtraKerningFactor(0.003f);
	smallFont.setExtraKerningFactor(0.003f);
	textEditorFont.setExtraKerningFactor(0.003f);
	tooltipFont.setExtraKerningFactor(0.003f);
}


juce::Font CustomLookAndFeel::getTextEditorFont()
{
	return textEditorFont;
}


juce::Font CustomLookAndFeel::getSectionTitleFont()
{
	return sectionTitleFont;
}


juce::Font CustomLookAndFeel::getBodyFont()
{
	return bodyFont;
}


juce::Font CustomLookAndFeel::getSmallFont()
{
	return smallFont;
}


juce::Font CustomLookAndFeel::getInstrumentNameFont()
{
	return instrumentNameFont;
}


void CustomLookAndFeel::drawLabel(juce::Graphics &g, juce::Label &label)
{
	juce::String labelName = label.getName();

	if (labelName.contains("InstrumentName"))
	{
		g.fillAll(label.findColour(juce::Label::backgroundColourId));
		g.setColour(textPrimary);
		g.setFont(instrumentNameFont);
		g.drawText(label.getText(), label.getLocalBounds(), juce::Justification::centredLeft, true);
	}
	else if (labelName.contains("SectionTitle"))
	{
		g.fillAll(label.findColour(juce::Label::backgroundColourId));
		g.setColour(textTertiary);
		g.setFont(sectionTitleFont);
		g.drawText(label.getText().toUpperCase(), label.getLocalBounds(), juce::Justification::centredLeft, false);
	}
	else if (labelName.contains("Title") || labelName.contains("NoteName"))
	{
		g.fillAll(label.findColour(juce::Label::backgroundColourId));
		g.setColour(textPrimary);
		auto font = juce::Font(instrumentTypeface).withHeight(18.0f);
		font.setExtraKerningFactor(0.003f);
		g.setFont(font);
		g.drawText(label.getText(), label.getLocalBounds(), juce::Justification::centred, true);
	}
	else
	{
		g.fillAll(label.findColour(juce::Label::backgroundColourId));
		g.setColour(label.findColour(juce::Label::textColourId));
		g.setFont(bodyFont);
		g.drawText(label.getText(), label.getLocalBounds(), juce::Justification::centredLeft, false);
	}
}


void CustomLookAndFeel::drawMenuBarBackground(juce::Graphics &g, int width, int height, bool isMouseOverBar, juce::MenuBarComponent &menuBar)
{
	g.fillAll(headerBar);
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
		gradient = juce::ColourGradient(surfaceElevated, 0, 0, surfaceElevated.darker(0.2f), 0, float(area.getHeight()), false);
	}
	g.setGradientFill(gradient);
	g.fillRect(area);

	g.setColour(isHighlighted ? textPrimary : textSecondary);
	g.setFont(getPopupMenuFont());
	g.drawText(text, area.reduced(10, 0), juce::Justification::centred, true);
}


void CustomLookAndFeel::drawButtonBackground(
	juce::Graphics &g, juce::Button &button, const juce::Colour &backgroundColour, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown)
{
	auto cornerSize = 6.0f;
	auto bounds		= button.getLocalBounds().toFloat().reduced(0.5f, 0.5f);

	auto buttonName = button.getName();

	// Family tab buttons
	if (buttonName.contains("FamilyTab"))
	{
		bool isActive = button.getToggleState();

		if (isActive)
			g.setColour(accentGold);
		else if (shouldDrawButtonAsHighlighted)
			g.setColour(tabInactive.brighter(0.1f));
		else
			g.setColour(juce::Colours::transparentBlack);

		g.fillRoundedRectangle(bounds, cornerSize);

		// Text color is handled by the label
		return;
	}

	// Articulation toggle buttons
	if (buttonName.contains("Articulation"))
	{
		bool isSelected = button.getToggleState();

		if (isSelected)
			g.setColour(accentGold);
		else if (shouldDrawButtonAsHighlighted)
			g.setColour(surfaceElevated.brighter(0.08f));
		else
			g.setColour(surfaceElevated);

		g.fillRoundedRectangle(bounds, cornerSize);
		return;
	}

	// Clef / pitch mode toggle pills
	if (buttonName.contains("MetaTag"))
	{
		bool isActive = button.getToggleState();

		if (isActive)
			g.setColour(accentGold);
		else if (shouldDrawButtonAsHighlighted)
			g.setColour(surfaceElevated.brighter(0.08f));
		else
			g.setColour(surfaceElevated);

		g.fillRoundedRectangle(bounds, 4.0f);
		return;
	}

	// Register/Quality buttons (legacy support during transition)
	if (buttonName.contains("FirstQuality"))
		g.setColour(firstQualityColour);
	else if (buttonName.contains("SecondQuality"))
		g.setColour(secondQualityColour);
	else if (buttonName.contains("ThirdQuality"))
		g.setColour(thirdQualityColour);
	else if (buttonName.contains("FourthQuality"))
		g.setColour(fourthQualityColour);
	else
		g.setColour(surfaceElevated);

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
	}
	else
	{
		g.fillRoundedRectangle(bounds, cornerSize);
	}
}


void CustomLookAndFeel::drawTooltip(juce::Graphics &g, const juce::String &text, int width, int height)
{
	g.setColour(surfaceElevated);
	g.fillRoundedRectangle(0, 0, (float)width, (float)height, mCornerRadius);

	// Gold accent border
	g.setColour(accentGold.withAlpha(0.3f));
	g.drawRoundedRectangle(0.5f, 0.5f, (float)width - 1.0f, (float)height - 1.0f, mCornerRadius, 1.0f);

	juce::TextLayout tl = layoutTooltipText(text);
	tl.draw(g, juce::Rectangle<float>(8.0f, 4.0f, (float)width - 16.0f, (float)height - 8.0f));
}


juce::TextLayout CustomLookAndFeel::layoutTooltipText(const juce::String &text) const noexcept
{
	juce::AttributedString s;
	s.setJustification(juce::Justification::centredLeft);
	s.append(text, tooltipFont, textPrimary);
	s.setLineSpacing(1.05);

	juce::TextLayout tl;
	tl.createLayout(s, (float)tooltipWidth - 16.0f);
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


std::vector<juce::Colour> CustomLookAndFeel::getQualityColours()
{
	std::vector<juce::Colour> qualityColours;
	qualityColours.reserve(4);

	qualityColours.push_back(firstQualityColour.brighter(0.3f));
	qualityColours.push_back(secondQualityColour.brighter(0.3f));
	qualityColours.push_back(thirdQualityColour.brighter(0.3f));
	qualityColours.push_back(fourthQualityColour.brighter(0.3f));

	return qualityColours;
}


std::vector<juce::Colour> CustomLookAndFeel::getQualityColoursBase()
{
	return {firstQualityColour, secondQualityColour, thirdQualityColour, fourthQualityColour};
}
