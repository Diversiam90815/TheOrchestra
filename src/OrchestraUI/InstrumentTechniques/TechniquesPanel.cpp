/*
  ==============================================================================
	Module			TechniquesPanel
	Description		Technique card grid with inline descriptions.
  ==============================================================================
*/

#include "TechniquesPanel.h"
#include "CustomLookAndFeel.h"
#include "GridFlow.h"
#include "TextMeasure.h"


// ========== TechniqueCard ==========

TechniqueCard::TechniqueCard(const std::string &name, const std::string &description) : mName(name), mDesc(description) {}


int TechniqueCard::getPreferredHeight(int width) const
{
	auto	  *lnf		  = dynamic_cast<CustomLookAndFeel *>(&getLookAndFeel());
	const auto descFont	  = lnf ? lnf->getSerifFont(Type::bodySmall) : juce::Font(Type::bodySmall);

	const int  textWidth  = juce::jmax(1, width - kPadX * 2);
	const int  descHeight = TextMeasure::wrappedHeight(descFont, juce::String(mDesc), textWidth);

	return juce::jmax(kMinHeight, kPadY * 2 + kNameHeight + descHeight);
}


void TechniqueCard::paint(juce::Graphics &g)
{
	auto	   *lnf		 = dynamic_cast<CustomLookAndFeel *>(&getLookAndFeel());
	const auto &t		 = themeFor(*this);

	auto		bounds	 = getLocalBounds().toFloat();

	auto		bgColour = t.surfaceElevated;
	if (isMouseOver())
		bgColour = bgColour.brighter(0.08f);

	g.setColour(bgColour);
	g.fillRoundedRectangle(bounds, Radius::lg);

	auto textArea = getLocalBounds().reduced(kPadX, kPadY);

	auto nameFont = lnf ? lnf->getSerifFont(Type::body, true) : juce::Font(Type::body);
	g.setColour(t.textPrimary);
	g.setFont(nameFont);
	g.drawText(mName, textArea.removeFromTop(kNameHeight), juce::Justification::centredLeft, true);

	const auto descFont = lnf ? lnf->getSerifFont(Type::bodySmall) : juce::Font(Type::bodySmall);
	TextMeasure::drawWrapped(g, descFont, t.textSecondary, juce::String(mDesc), textArea);
}


// ========== TechniquesPanel ==========

TechniquesPanel::TechniquesPanel() : OrchestraPanel("PLAYING TECHNIQUES") {}


void TechniquesPanel::setInstrument(const InstrumentProfile &instrument)
{
	mCards.clear();

	for (const auto &tech : instrument.getTechniques())
	{
		auto card = std::make_unique<TechniqueCard>(tech.getName(), tech.getDescription());
		card->setRepaintsOnMouseActivity(true);
		addAndMakeVisible(card.get());
		mCards.push_back(std::move(card));
	}

	resized();
	repaint();
}


std::vector<int> TechniquesPanel::cellHeights(int width) const
{
	std::vector<int> heights;

	if (mCards.empty())
		return heights;

	const int gridWidth = width - kPadding * 2;
	const int columns	= GridFlow::columnCount(gridWidth, kMinColumnWidth, kMaxColumns);
	const int cellWidth = (gridWidth - kGap * (columns - 1)) / columns;

	heights.reserve(mCards.size());
	for (const auto &card : mCards)
		heights.push_back(card->getPreferredHeight(cellWidth));

	return heights;
}


int TechniquesPanel::getPreferredHeight(int width) const
{
	if (mCards.empty())
		return getChromeHeight();

	const int columns = GridFlow::columnCount(width - kPadding * 2, kMinColumnWidth, kMaxColumns);

	return getChromeHeight() + GridFlow::totalHeight(cellHeights(width), columns, kGap);
}


void TechniquesPanel::resized()
{
	if (mCards.empty())
		return;

	auto	   area	   = getContentArea();
	const int  columns = GridFlow::columnCount(area.getWidth(), kMinColumnWidth, kMaxColumns);
	const auto rows	   = GridFlow::rowHeights(cellHeights(getWidth()), columns);

	for (size_t i = 0; i < mCards.size(); ++i)
		mCards[i]->setBounds(GridFlow::cellBounds(area, (int)i, columns, kGap, rows));
}
