/*
  ==============================================================================
	Module			QualitiesPanel
	Description		The "QUALITIES" list from the Overview tab: colored swatches +
					register descriptions
  ==============================================================================
*/

#include "QualitiesPanel.h"
#include "CustomLookAndFeel.h"


void QualitiesPanel::setInstrument(const InstrumentProfile &instrument)
{
	mDescriptions.clear();

	for (const auto &reg : instrument.getRegisters())
		mDescriptions.push_back(juce::String(reg.getDescription()));

	auto range		  = instrument.getRange();
	mHasTransposition = (range.getWrittenLowNote() != range.getSoundingLowNote()) || (range.getWrittenHighNote() != range.getSoundingHighNote());
	mPitchMode		  = PitchMode::Written;

	repaint();
}


void QualitiesPanel::setPitchMode(PitchMode mode)
{
	mPitchMode = mode;
	repaint();
}


void QualitiesPanel::paint(juce::Graphics &g)
{
	auto *lf = dynamic_cast<CustomLookAndFeel *>(&getLookAndFeel());

	const juce::Colour muted	 = lf ? lf->getTextTertiaryColour() : juce::Colour::fromRGB(107, 103, 96);
	const juce::Colour secondary = lf ? lf->getTextSecondaryColour() : juce::Colour::fromRGB(158, 154, 142);
	const juce::Colour gold		 = lf ? lf->getAccentColour() : juce::Colour::fromRGB(196, 148, 58);
	auto			   colours	 = lf ? lf->getQualityColours() : std::vector<juce::Colour>{};

	auto area = getLocalBounds();

	// Header row: QUALITIES (left) + pitch-mode label (right)
	auto header = area.removeFromTop(20);

	g.setColour(muted);
	g.setFont(lf ? lf->getSerifFont(10.5f, true) : juce::Font(10.5f));
	g.drawText("QUALITIES", header, juce::Justification::centredLeft, false);

	if (mHasTransposition)
	{
		g.setColour(gold);
		g.setFont(lf ? lf->getSerifFont(11.0f) : juce::Font(11.0f));
		g.drawText(mPitchMode == PitchMode::Sounding ? "Sounding Pitch" : "Written Pitch", header, juce::Justification::centredRight, false);
	}

	area.removeFromTop(10);

	// Rows: swatch + description
	const int rowH		= 20;
	const int rowGap	= 7;
	const int swatch	= 8;
	const int textInset = 8 + swatch + 8;

	g.setFont(lf ? lf->getSerifFont(12.5f) : juce::Font(12.5f));

	for (size_t i = 0; i < mDescriptions.size(); ++i)
	{
		auto row = area.removeFromTop(rowH);

		auto swatchRect = juce::Rectangle<float>((float)row.getX(), (float)(row.getCentreY() - swatch / 2), (float)swatch, (float)swatch);
		g.setColour(i < colours.size() ? colours[i] : juce::Colours::grey);
		g.fillRoundedRectangle(swatchRect, 2.0f);

		g.setColour(secondary);
		g.drawText(mDescriptions[i], row.withTrimmedLeft(textInset), juce::Justification::centredLeft, true);

		area.removeFromTop(rowGap);
	}
}
