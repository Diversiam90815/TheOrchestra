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


void CustomLookAndFeel::init()
{
	setColour(juce::ResizableWindow::backgroundColourId, mTheme.background);
	setColour(juce::Label::textColourId, mTheme.textPrimary);

	setFont();
}


void CustomLookAndFeel::setFont()
{
	instrumentTypeface = juce::Typeface::createSystemTypefaceFor(TextFontData::SourceSerif4Regular_ttf, TextFontData::SourceSerif4Regular_ttfSize);

	instrumentNameFont = juce::Font(instrumentTypeface).withHeight(Type::display);
	sectionTitleFont   = juce::Font(instrumentTypeface).withHeight(Type::label);
	bodyFont		   = juce::Font(instrumentTypeface).withHeight(Type::body);

	instrumentNameFont.setExtraKerningFactor(0.01f);
	sectionTitleFont.setExtraKerningFactor(0.12f);
	bodyFont.setExtraKerningFactor(0.02f);
}


juce::Font CustomLookAndFeel::getSectionTitleFont() const
{
	return sectionTitleFont;
}


juce::Font CustomLookAndFeel::getSerifFont(float height, bool semiBold) const
{
	juce::Font font = juce::Font(instrumentTypeface).withHeight(height);
	font.setExtraKerningFactor(0.02f);

	if (semiBold)
		font = font.boldened();

	return font;
}


void CustomLookAndFeel::drawLabel(juce::Graphics &g, juce::Label &label)
{
	const auto bounds = label.getLocalBounds();

	switch (labelStyleOf(label))
	{
	case LabelStyle::InstrumentName:
		g.fillAll(label.findColour(juce::Label::backgroundColourId));
		g.setColour(mTheme.textPrimary);
		g.setFont(instrumentNameFont);
		g.drawText(label.getText(), bounds, juce::Justification::centredLeft, true);
		break;

	case LabelStyle::FamilySubtitle:
		g.fillAll(label.findColour(juce::Label::backgroundColourId));
		g.setColour(mTheme.textSecondary);
		g.setFont(bodyFont);
		g.drawText(label.getText(), bounds, juce::Justification::centredLeft, false);
		break;

	case LabelStyle::MetaInfo:
		// Non-interactive info pill (transposition)
		g.setColour(mTheme.surfaceElevated);
		g.fillRoundedRectangle(bounds.toFloat().reduced(0.5f), Radius::sm);

		g.setFont(getSerifFont(Type::bodySmall));
		g.setColour(mTheme.textSecondary);
		g.drawText(label.getText(), bounds, juce::Justification::centred, true);
		break;

	case LabelStyle::SectionTitle:
		g.fillAll(label.findColour(juce::Label::backgroundColourId));
		g.setColour(mTheme.textTertiary);
		g.setFont(sectionTitleFont);
		g.drawText(label.getText().toUpperCase(), bounds, juce::Justification::centredLeft, false);
		break;

	case LabelStyle::NoteName:
		g.fillAll(label.findColour(juce::Label::backgroundColourId));
		g.setColour(mTheme.textPrimary);
		g.setFont(getSerifFont(Type::heading));
		g.drawText(label.getText(), bounds, juce::Justification::centred, true);
		break;

	case LabelStyle::Status:
		g.fillAll(label.findColour(juce::Label::backgroundColourId));
		g.setColour(mTheme.textTertiary);
		g.setFont(getSerifFont(Type::caption));
		g.drawText(label.getText(), bounds, juce::Justification::centredLeft, true);
		break;

	case LabelStyle::Default:
	default:
		g.fillAll(label.findColour(juce::Label::backgroundColourId));
		g.setColour(label.findColour(juce::Label::textColourId));
		g.setFont(bodyFont);
		g.drawText(label.getText(), bounds, juce::Justification::centredLeft, false);
		break;
	}
}


void CustomLookAndFeel::drawButtonBackground(
	juce::Graphics &g, juce::Button &button, const juce::Colour &backgroundColour, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown)
{
	auto	   bounds	= button.getLocalBounds().toFloat().reduced(0.5f, 0.5f);

	const bool isActive = button.getToggleState();

	if (isActive)
		g.setColour(mTheme.accent);
	else if (shouldDrawButtonAsHighlighted)
		g.setColour(mTheme.surfaceElevated.brighter(0.08f));
	else
		g.setColour(mTheme.surfaceElevated);

	// Clef / pitch-mode pills are tighter than the articulation toggles.
	const float radius = (buttonStyleOf(button) == ButtonStyle::MetaTag) ? Radius::sm : Radius::md;

	g.fillRoundedRectangle(bounds, radius);
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
