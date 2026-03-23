/*
  ==============================================================================
	Module			TechniquesPanel
	Description		Dynamic scrollable technique card grid with inline descriptions
  ==============================================================================
*/

#include "TechniquesPanel.h"
#include "CustomLookAndFeel.h"


// ========== TechniqueCard ==========

TechniqueCard::TechniqueCard(const std::string &name, const std::string &description)
	: mName(name), mDesc(description)
{
}


void TechniqueCard::paint(juce::Graphics &g)
{
	auto bounds = getLocalBounds().toFloat();
	auto *lnf	= dynamic_cast<CustomLookAndFeel *>(&getLookAndFeel());

	// Card background
	auto bgColour = lnf ? lnf->getSurfaceElevatedColour() : juce::Colour(40, 36, 64);

	if (isMouseOver())
		bgColour = bgColour.brighter(0.08f);

	g.setColour(bgColour);
	g.fillRoundedRectangle(bounds, 8.0f);

	// Name
	auto nameColour = lnf ? lnf->getTextPrimaryColour() : juce::Colour(238, 233, 218);
	auto descColour = lnf ? lnf->getTextSecondaryColour() : juce::Colour(158, 154, 142);

	auto textArea = bounds.reduced(12.0f, 8.0f);

	auto nameFont = lnf ? juce::Font(lnf->getInstrumentTypeface()).withHeight(16.0f) : juce::Font(16.0f);
	nameFont.setExtraKerningFactor(0.003f);
	g.setColour(nameColour);
	g.setFont(nameFont);
	g.drawText(mName, textArea.removeFromTop(20.0f), juce::Justification::centredLeft, true);

	// Description
	auto descFont = lnf ? juce::Font(lnf->getInstrumentTypeface()).withHeight(14.0f) : juce::Font(14.0f);
	descFont.setExtraKerningFactor(0.003f);
	g.setColour(descColour);
	g.setFont(descFont);
	g.drawText(mDesc, textArea, juce::Justification::topLeft, true);
}


// ========== TechniquesPanel ==========

TechniquesPanel::TechniquesPanel() : OrchestraPanel("Playing Techniques")
{
	mViewport.setViewedComponent(&mContent, false);
	mViewport.setScrollBarsShown(true, false);
	mViewport.setScrollBarThickness(4);
	addAndMakeVisible(mViewport);
}


void TechniquesPanel::setInstrument(const InstrumentProfile &instrument)
{
	// Remove old cards
	mCards.clear();

	auto techniques = instrument.getTechniques();

	for (const auto &tech : techniques)
	{
		auto card = std::make_unique<TechniqueCard>(tech.getName(), tech.getDescription());
		card->setRepaintsOnMouseActivity(true);
		mContent.addAndMakeVisible(card.get());
		mCards.push_back(std::move(card));
	}

	resized();
	repaint();
}


void TechniquesPanel::resized()
{
	auto area = getContentArea();
	mViewport.setBounds(area);

	// Layout cards in 2-column grid
	const int gap		  = 8;
	const int numCols	  = 2;
	const int colWidth	  = (area.getWidth() - gap - 8) / numCols; // -8 for scrollbar
	const int cardHeight  = 62;

	int totalRows = (static_cast<int>(mCards.size()) + numCols - 1) / numCols;
	int contentHeight = totalRows * (cardHeight + gap);
	mContent.setSize(area.getWidth() - 8, juce::jmax(contentHeight, area.getHeight()));

	for (size_t i = 0; i < mCards.size(); ++i)
	{
		int col = static_cast<int>(i) % numCols;
		int row = static_cast<int>(i) / numCols;
		int x	= col * (colWidth + gap);
		int y	= row * (cardHeight + gap);
		mCards[i]->setBounds(x, y, colWidth, cardHeight);
	}
}
