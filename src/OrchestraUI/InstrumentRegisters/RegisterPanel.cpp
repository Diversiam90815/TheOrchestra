/*
  ==============================================================================
	Module			RegisterPanel
	Description		Panel displaying instrument register cards with color coding
  ==============================================================================
*/

#include "RegisterPanel.h"
#include "CustomLookAndFeel.h"


RegisterPanel::RegisterPanel() : OrchestraPanel("REGISTERS")
{
}


void RegisterPanel::setInstrument(const InstrumentProfile &instrument)
{
	mRegisters.clear();
	mIsStringInstrument = false;

	auto registers = instrument.getRegisters();

	// Detect string instruments: all registers have low == high (open string tuning)
	if (!registers.empty())
	{
		bool allSingleNote = true;
		for (const auto &reg : registers)
		{
			if (reg.getLowerRange() != reg.getHigherRange())
			{
				allSingleNote = false;
				break;
			}
		}
		mIsStringInstrument = allSingleNote;
	}

	// Update panel title based on instrument type
	setTitle(mIsStringInstrument ? "STRINGS" : "REGISTERS");

	for (const auto &reg : registers)
	{
		RegisterData data;

		if (mIsStringInstrument)
		{
			// String instruments: show just the note as the string identifier
			data.range = juce::String(reg.getLowerRange()) + " String";
		}
		else
		{
			// Wind/brass: show pitch range
			data.range = juce::String(reg.getLowerRange() + " - " + reg.getHigherRange());
		}

		data.description = juce::String(reg.getDescription());
		mRegisters.push_back(data);
	}

	repaint();
}


void RegisterPanel::paint(juce::Graphics &g)
{
	OrchestraPanel::paint(g);

	auto *lnf = dynamic_cast<CustomLookAndFeel *>(&getLookAndFeel());
	if (!lnf || mRegisters.empty())
		return;

	auto colours	  = lnf->getQualityColoursBase();
	auto primaryCol	  = lnf->getTextPrimaryColour();
	auto secondaryCol = lnf->getTextSecondaryColour();

	auto area = getContentArea();

	for (size_t i = 0; i < mRegisters.size(); ++i)
	{
		auto cardBounds = area.removeFromTop(kCardHeight);

		auto colour = colours[i % colours.size()];

		// Card background with rounded right corners
		{
			auto bgRect = cardBounds.toFloat();
			juce::Path bgPath;
			bgPath.addRoundedRectangle(bgRect.getX(), bgRect.getY(), bgRect.getWidth(), bgRect.getHeight(), 8.0f, 8.0f, false, true, false, true);
			g.setColour(colour.withAlpha(0.08f));
			g.fillPath(bgPath);
		}

		// Left color bar
		{
			auto barRect = cardBounds.removeFromLeft(kBarWidth).toFloat();
			g.setColour(colour);
			g.fillRect(barRect);
		}

		// Text area
		auto textArea = cardBounds.reduced(10, 8);

		// Range label
		auto rangeArea = textArea.removeFromTop(20);
		g.setColour(primaryCol);
		g.setFont(lnf->getBodyFont());
		g.drawText(mRegisters[i].range, rangeArea, juce::Justification::centredLeft, false);

		// Description
		g.setColour(secondaryCol);
		g.setFont(lnf->getSmallFont());
		g.drawFittedText(mRegisters[i].description, textArea, juce::Justification::topLeft, 2);

		// Gap between cards
		if (i < mRegisters.size() - 1)
			area.removeFromTop(kCardGap);
	}
}
