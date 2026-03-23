/*
  ==============================================================================
	Module			FamousWorksPanel
	Description		Panel displaying famous works featuring the instrument
  ==============================================================================
*/

#include "FamousWorksPanel.h"
#include "CustomLookAndFeel.h"


FamousWorksPanel::FamousWorksPanel() : OrchestraPanel("FAMOUS WORKS")
{
}


void FamousWorksPanel::setInstrument(const InstrumentProfile &instrument)
{
	mWorks.clear();

	for (const auto &work : instrument.getFamousWorks())
	{
		WorkData data;
		data.composer = juce::String(work.getComposer());
		data.title	  = juce::String(work.getTitle());
		mWorks.push_back(data);
	}

	repaint();
}


void FamousWorksPanel::paint(juce::Graphics &g)
{
	OrchestraPanel::paint(g);

	auto *lnf = dynamic_cast<CustomLookAndFeel *>(&getLookAndFeel());
	if (!lnf || mWorks.empty())
		return;

	auto primaryCol	 = lnf->getTextPrimaryColour();
	auto tertiaryCol = lnf->getTextTertiaryColour();

	auto area = getContentArea();

	for (size_t i = 0; i < mWorks.size(); ++i)
	{
		auto entryBounds = area.removeFromTop(kEntryHeight);

		// Composer line (uppercase, small)
		auto composerArea = entryBounds.removeFromTop(14);
		g.setColour(tertiaryCol);
		auto composerFont = juce::Font(lnf->getInstrumentTypeface()).withHeight(11.0f);
		composerFont.setExtraKerningFactor(0.08f);
		g.setFont(composerFont);
		g.drawText(mWorks[i].composer.toUpperCase(), composerArea, juce::Justification::centredLeft, false);

		// Title line
		auto titleArea = entryBounds;
		g.setColour(primaryCol);
		g.setFont(lnf->getBodyFont());
		g.drawText(mWorks[i].title, titleArea, juce::Justification::centredLeft, true);
	}
}
