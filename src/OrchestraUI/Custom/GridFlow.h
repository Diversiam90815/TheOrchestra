/*
  ==============================================================================
	Module			GridFlow
	Description		One responsive column rule, shared by every card grid
  ==============================================================================
*/

#pragma once

#include <vector>

#include "JuceIncludes.h"


namespace GridFlow
{

int					 columnCount(int availableWidth, int minColumnWidth, int maxColumns);

std::vector<int>	 rowHeights(const std::vector<int> &cellHeights, int columns);

int					 totalHeight(const std::vector<int> &cellHeights, int columns, int rowGap);

juce::Rectangle<int> cellBounds(juce::Rectangle<int> area, int index, int columns, int gap, const std::vector<int> &heights);

} // namespace GridFlow
