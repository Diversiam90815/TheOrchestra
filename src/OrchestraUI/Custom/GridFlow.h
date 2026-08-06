/*
  ==============================================================================
	Module			GridFlow
	Description		One responsive column rule, shared by every card grid.

					Panels that used to render a single cramped column into a
					very wide body (roles, famous works, techniques) flow into
					as many columns as the width honestly supports.
  ==============================================================================
*/

#pragma once

#include <vector>

#include "JuceIncludes.h"


namespace GridFlow
{
/*
 @brief					How many columns fit, given a minimum readable width.
 @param					[IN] availableWidth for the whole grid.
 @param					[IN] minColumnWidth below which text stops being readable.
 @param					[IN] maxColumns ceiling.
 @return				Column count, always at least 1.
*/
int						 columnCount(int availableWidth, int minColumnWidth, int maxColumns);

/*
 @brief					Row heights for a grid laid out left-to-right, where each
						row is as tall as its tallest cell.
 @param					[IN] cellHeights in index order.
 @param					[IN] columns per row.
 @return				One height per row.
*/
std::vector<int>		 rowHeights(const std::vector<int> &cellHeights, int columns);

/*
 @brief					Total height of a grid including the gaps between rows.
*/
int						 totalHeight(const std::vector<int> &cellHeights, int columns, int rowGap);

/*
 @brief					Bounds of one cell in a left-to-right grid.
 @param					[IN] area the grid occupies.
 @param					[IN] index of the cell.
 @param					[IN] columns per row.
 @param					[IN] gap between columns and between rows.
 @param					[IN] heights of each row, from rowHeights().
*/
juce::Rectangle<int>	 cellBounds(juce::Rectangle<int> area, int index, int columns, int gap, const std::vector<int> &heights);
} // namespace GridFlow
