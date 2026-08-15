/*
  ==============================================================================
	Module			GridFlow
	Description		One responsive column rule, shared by every card grid
  ==============================================================================
*/

#include "GridFlow.h"


int GridFlow::columnCount(int availableWidth, int minColumnWidth, int maxColumns)
{
	if (availableWidth <= 0 || minColumnWidth <= 0)
		return 1;

	return juce::jlimit(1, juce::jmax(1, maxColumns), availableWidth / minColumnWidth);
}


std::vector<int> GridFlow::rowHeights(const std::vector<int> &cellHeights, int columns)
{
	std::vector<int> heights;

	if (columns <= 0)
		return heights;

	for (size_t i = 0; i < cellHeights.size(); ++i)
	{
		const size_t row = i / (size_t)columns;

		if (row >= heights.size())
			heights.push_back(cellHeights[i]);
		else
			heights[row] = juce::jmax(heights[row], cellHeights[i]);
	}

	return heights;
}


int GridFlow::totalHeight(const std::vector<int> &cellHeights, int columns, int rowGap)
{
	const auto heights = rowHeights(cellHeights, columns);

	if (heights.empty())
		return 0;

	int total = 0;
	for (int h : heights)
		total += h;

	return total + rowGap * ((int)heights.size() - 1);
}


juce::Rectangle<int> GridFlow::cellBounds(juce::Rectangle<int> area, int index, int columns, int gap, const std::vector<int> &heights)
{
	if (columns <= 0 || heights.empty())
		return {};

	const int col	   = index % columns;
	const int row	   = index / columns;

	if (row >= (int)heights.size())
		return {};

	const int colWidth = (area.getWidth() - gap * (columns - 1)) / columns;

	int		  y		   = area.getY();
	for (int r = 0; r < row; ++r)
		y += heights[(size_t)r] + gap;

	return { area.getX() + col * (colWidth + gap), y, colWidth, heights[(size_t)row] };
}
