/*
  ==============================================================================
	Module			RolesPanel
	Description		Panel displaying orchestration roles as a bulleted, wrapped
					multi-column card grid.
  ==============================================================================
*/

#include "RolesPanel.h"
#include "CustomLookAndFeel.h"
#include "GridFlow.h"
#include "TextMeasure.h"


RolesPanel::RolesPanel() : OrchestraPanel("ORCHESTRATION ROLES")
{
}


void RolesPanel::setInstrument(const InstrumentProfile &instrument)
{
	mRoles.clear();

	for (const auto &role : instrument.getRoles())
		mRoles.push_back(juce::String(role.getRole()));

	repaint();
}


int RolesPanel::measureCell(const juce::Font &font, const juce::String &role, int cellWidth) const
{
	const int textWidth = juce::jmax(1, cellWidth - kBulletGutter);
	return juce::jmax(kMinCellHeight, TextMeasure::wrappedHeight(font, role, textWidth) + Space::s);
}


std::vector<int> RolesPanel::cellHeights(int width) const
{
	std::vector<int> heights;

	if (mRoles.empty())
		return heights;

	auto	  *lnf		 = dynamic_cast<CustomLookAndFeel *>(&getLookAndFeel());
	const auto font		 = lnf ? lnf->getSerifFont(Type::body) : juce::Font(Type::body);

	const int  gridWidth = width - kPadding * 2;
	const int  columns	 = GridFlow::columnCount(gridWidth, kMinColumnWidth, kMaxColumns);
	const int  cellWidth = (gridWidth - kGap * (columns - 1)) / columns;

	heights.reserve(mRoles.size());
	for (const auto &role : mRoles)
		heights.push_back(measureCell(font, role, cellWidth));

	return heights;
}


int RolesPanel::getPreferredHeight(int width) const
{
	if (mRoles.empty())
		return getChromeHeight();

	const int columns = GridFlow::columnCount(width - kPadding * 2, kMinColumnWidth, kMaxColumns);

	return getChromeHeight() + GridFlow::totalHeight(cellHeights(width), columns, kGap);
}


void RolesPanel::paint(juce::Graphics &g)
{
	OrchestraPanel::paint(g);

	auto *lnf = dynamic_cast<CustomLookAndFeel *>(&getLookAndFeel());
	if (mRoles.empty())
		return;

	const auto &t		= themeFor(*this);
	const auto	font	= lnf ? lnf->getSerifFont(Type::body) : juce::Font(Type::body);

	auto		area	= getContentArea();
	const int	columns = GridFlow::columnCount(area.getWidth(), kMinColumnWidth, kMaxColumns);
	const auto	heights = cellHeights(getWidth());
	const auto	rows	= GridFlow::rowHeights(heights, columns);

	for (size_t i = 0; i < mRoles.size(); ++i)
	{
		auto cell = GridFlow::cellBounds(area, (int)i, columns, kGap, rows);
		if (cell.isEmpty())
			continue;

		// Gold bullet, aligned to the first line of the wrapped text.
		const float bulletY = (float)cell.getY() + font.getHeight() * 0.5f - kBulletSize * 0.5f;
		g.setColour(t.accent);
		g.fillEllipse((float)cell.getX(), bulletY, kBulletSize, kBulletSize);

		TextMeasure::drawWrapped(g, font, t.textSecondary, mRoles[i], cell.withTrimmedLeft(kBulletGutter));
	}
}
