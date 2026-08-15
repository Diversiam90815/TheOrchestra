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
	return Radius::xl;
}


void CustomLookAndFeel::init()
{
	setColour(juce::ResizableWindow::backgroundColourId, mTheme.background);
	setColour(juce::Label::textColourId, mTheme.textPrimary);

	setColour(juce::PopupMenu::backgroundColourId, juce::Colours::black);
	setColour(juce::PopupMenu::highlightedBackgroundColourId, mTheme.surfaceElevated);
	setColour(juce::PopupMenu::highlightedTextColourId, mTheme.textPrimary);
	setColour(juce::PopupMenu::textColourId, mTheme.textSecondary);

	setColour(juce::ComboBox::backgroundColourId, mTheme.surface);

	setFont();
}


void CustomLookAndFeel::setFont()
{
	instrumentTypeface = juce::Typeface::createSystemTypefaceFor(TextFontData::SourceSerif4Regular_ttf, TextFontData::SourceSerif4Regular_ttfSize);

	instrumentNameFont = juce::Font(instrumentTypeface).withHeight(Type::display);
	sectionTitleFont   = juce::Font(instrumentTypeface).withHeight(Type::label);
	bodyFont		   = juce::Font(instrumentTypeface).withHeight(Type::body);
	smallFont		   = juce::Font(instrumentTypeface).withHeight(Type::bodySmall);
	textEditorFont	   = juce::Font(instrumentTypeface).withHeight(Type::body);
	tooltipFont		   = juce::Font(instrumentTypeface).withHeight(Type::bodySmall);

	instrumentNameFont.setExtraKerningFactor(0.01f);
	sectionTitleFont.setExtraKerningFactor(0.12f);
	bodyFont.setExtraKerningFactor(0.02f);
	smallFont.setExtraKerningFactor(0.02f);
	textEditorFont.setExtraKerningFactor(0.02f);
	tooltipFont.setExtraKerningFactor(0.02f);
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


juce::Font CustomLookAndFeel::getSerifFont(float height, bool semiBold) const
{
	juce::Font font = juce::Font(instrumentTypeface).withHeight(height);
	font.setExtraKerningFactor(0.02f);

	// Source Serif 4 ships Regular only; synthesize a heavier weight for the design's 600-weight text.
	if (semiBold)
		font = font.boldened();

	return font;
}


void CustomLookAndFeel::drawLabel(juce::Graphics &g, juce::Label &label)
{
	juce::String labelName = label.getName();

	if (labelName.contains("InstrumentName"))
	{
		g.fillAll(label.findColour(juce::Label::backgroundColourId));
		g.setColour(mTheme.textPrimary);
		g.setFont(instrumentNameFont);
		g.drawText(label.getText(), label.getLocalBounds(), juce::Justification::centredLeft, true);
	}
	else if (labelName.contains("FamilySubtitle"))
	{
		g.fillAll(label.findColour(juce::Label::backgroundColourId));
		g.setColour(mTheme.textSecondary);
		g.setFont(bodyFont);
		g.drawText(label.getText(), label.getLocalBounds(), juce::Justification::centredLeft, false);
	}
	else if (labelName.contains("MetaInfo"))
	{
		// Non-interactive info pill (clefs, transposition)
		auto bounds = label.getLocalBounds().toFloat().reduced(0.5f);
		g.setColour(mTheme.surfaceElevated);
		g.fillRoundedRectangle(bounds, Radius::sm);

		auto font = juce::Font(instrumentTypeface).withHeight(Type::bodySmall);
		font.setExtraKerningFactor(0.02f);
		g.setFont(font);
		g.setColour(mTheme.textSecondary);
		g.drawText(label.getText(), label.getLocalBounds(), juce::Justification::centred, true);
	}
	else if (labelName.contains("SectionTitle"))
	{
		g.fillAll(label.findColour(juce::Label::backgroundColourId));
		g.setColour(mTheme.textTertiary);
		g.setFont(sectionTitleFont);
		g.drawText(label.getText().toUpperCase(), label.getLocalBounds(), juce::Justification::centredLeft, false);
	}
	else if (labelName.contains("Title") || labelName.contains("NoteName"))
	{
		g.fillAll(label.findColour(juce::Label::backgroundColourId));
		g.setColour(mTheme.textPrimary);
		auto font = juce::Font(instrumentTypeface).withHeight(Type::heading);
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
	g.fillAll(mTheme.toolbar);
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
		gradient = juce::ColourGradient(mTheme.surfaceElevated, 0, 0, mTheme.surfaceElevated.darker(0.2f), 0, float(area.getHeight()), false);
	}
	g.setGradientFill(gradient);
	g.fillRect(area);

	g.setColour(isHighlighted ? mTheme.textPrimary : mTheme.textSecondary);
	g.setFont(getPopupMenuFont());
	g.drawText(text, area.reduced(10, 0), juce::Justification::centred, true);
}


void CustomLookAndFeel::drawButtonBackground(
	juce::Graphics &g, juce::Button &button, const juce::Colour &backgroundColour, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown)
{
	auto	   bounds	  = button.getLocalBounds().toFloat().reduced(0.5f, 0.5f);
	auto	   buttonName = button.getName();

	const bool isActive	  = button.getToggleState();

	if (isActive)
		g.setColour(mTheme.accent);
	else if (shouldDrawButtonAsHighlighted)
		g.setColour(mTheme.surfaceElevated.brighter(0.08f));
	else
		g.setColour(mTheme.surfaceElevated);

	// Clef / pitch-mode pills are tighter than the articulation toggles.
	g.fillRoundedRectangle(bounds, buttonName.contains("MetaTag") ? Radius::sm : Radius::md);
}


void CustomLookAndFeel::drawTooltip(juce::Graphics &g, const juce::String &text, int width, int height)
{
	g.setColour(mTheme.surfaceElevated);
	g.fillRoundedRectangle(0, 0, (float)width, (float)height, Radius::xl);

	// Gold accent border
	g.setColour(mTheme.outline());
	g.drawRoundedRectangle(0.5f, 0.5f, (float)width - 1.0f, (float)height - 1.0f, Radius::xl, 1.0f);

	juce::TextLayout tl = layoutTooltipText(text);
	tl.draw(g, juce::Rectangle<float>(8.0f, 4.0f, (float)width - 16.0f, (float)height - 8.0f));
}


juce::TextLayout CustomLookAndFeel::layoutTooltipText(const juce::String &text) const noexcept
{
	juce::AttributedString s;
	s.setJustification(juce::Justification::centredLeft);
	s.append(text, tooltipFont, mTheme.textPrimary);
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


void CustomLookAndFeel::drawButtonText(juce::Graphics &g, juce::TextButton &button, bool /*shouldDrawButtonAsHighlighted*/, bool /*shouldDrawButtonAsDown*/)
{
	auto font = juce::Font(instrumentTypeface).withHeight(Type::bodySmall);
	font.setExtraKerningFactor(0.02f);
	g.setFont(font);

	// Active pills fill with gold, so their label needs the dark surface colour.
	g.setColour(button.getToggleState() ? mTheme.background : mTheme.textSecondary);

	g.drawText(button.getButtonText(), button.getLocalBounds(), juce::Justification::centred, true);
}
