/*
  ==============================================================================
	Module			FamousWorksPanel
	Description		Panel displaying famous works featuring the instrument, as a
					wrapped multi-column card grid.
  ==============================================================================
*/

#include "FamousWorksPanel.h"
#include "CustomLookAndFeel.h"
#include "GridFlow.h"
#include "TextMeasure.h"


FamousWorksPanel::FamousWorksPanel() : OrchestraPanel("FAMOUS WORKS") {}


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


std::vector<int> FamousWorksPanel::cellHeights(int width) const
{
	std::vector<int> heights;

	if (mWorks.empty())
		return heights;

	auto	  *lnf		 = dynamic_cast<CustomLookAndFeel *>(&getLookAndFeel());
	const auto titleFont = lnf ? lnf->getSerifFont(Type::body) : juce::Font(Type::body);

	const int  gridWidth = width - kPadding * 2;
	const int  columns	 = GridFlow::columnCount(gridWidth, kMinColumnWidth, kMaxColumns);
	const int  cellWidth = (gridWidth - kGap * (columns - 1)) / columns;

	heights.reserve(mWorks.size());
	for (const auto &work : mWorks)
	{
		const int titleHeight = TextMeasure::wrappedHeight(titleFont, work.title, cellWidth);
		heights.push_back(juce::jmax(kMinCellHeight, kComposerHeight + Space::xs + titleHeight + Space::s));
	}

	return heights;
}


int FamousWorksPanel::getPreferredHeight(int width) const
{
	if (mWorks.empty())
		return getChromeHeight();

	const int columns = GridFlow::columnCount(width - kPadding * 2, kMinColumnWidth, kMaxColumns);

	return getChromeHeight() + GridFlow::totalHeight(cellHeights(width), columns, kGap);
}


void FamousWorksPanel::paint(juce::Graphics &g)
{
	OrchestraPanel::paint(g);

	auto *lnf = dynamic_cast<CustomLookAndFeel *>(&getLookAndFeel());
	if (mWorks.empty())
		return;

	const auto &t			 = themeFor(*this);

	auto		composerFont = lnf ? lnf->getSerifFont(Type::label) : juce::Font(Type::label);
	composerFont.setExtraKerningFactor(0.10f);

	const auto titleFont = lnf ? lnf->getSerifFont(Type::body) : juce::Font(Type::body);

	auto	   area		 = getContentArea();
	const int  columns	 = GridFlow::columnCount(area.getWidth(), kMinColumnWidth, kMaxColumns);
	const auto heights	 = cellHeights(getWidth());
	const auto rows		 = GridFlow::rowHeights(heights, columns);

	for (size_t i = 0; i < mWorks.size(); ++i)
	{
		auto cell = GridFlow::cellBounds(area, (int)i, columns, kGap, rows);
		if (cell.isEmpty())
			continue;

		auto composerArea = cell.removeFromTop(kComposerHeight);
		g.setColour(t.textTertiary);
		g.setFont(composerFont);
		g.drawText(mWorks[i].composer.toUpperCase(), composerArea, juce::Justification::centredLeft, false);

		cell.removeFromTop(Space::xs);

		TextMeasure::drawWrapped(g, titleFont, t.textPrimary, mWorks[i].title, cell);
	}
}
