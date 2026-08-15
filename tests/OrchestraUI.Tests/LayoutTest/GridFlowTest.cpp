/*
  ==============================================================================
	Module          GridFlow Tests
	Description     The responsive column rule shared by every card grid
  ==============================================================================
*/

#include <gtest/gtest.h>

#include "GridFlow.h"

namespace GridFlowTests
{

//==============================================================================
// columnCount
//==============================================================================

TEST(ColumnCountTest, FitsAsManyColumnsAsTheWidthAllows)
{
	EXPECT_EQ(GridFlow::columnCount(600, 200, 4), 3);
	EXPECT_EQ(GridFlow::columnCount(400, 200, 4), 2);
	EXPECT_EQ(GridFlow::columnCount(200, 200, 4), 1);
}


TEST(ColumnCountTest, NeverExceedsTheColumnCap)
{
	EXPECT_EQ(GridFlow::columnCount(10000, 100, 3), 3) << "A very wide panel should still respect maxColumns";
	EXPECT_EQ(GridFlow::columnCount(10000, 100, 1), 1);
}


TEST(ColumnCountTest, NeverReturnsFewerThanOneColumn)
{
	// A panel narrower than a single column still has to lay one out.
	EXPECT_EQ(GridFlow::columnCount(50, 200, 4), 1);
	EXPECT_EQ(GridFlow::columnCount(0, 200, 4), 1);
	EXPECT_EQ(GridFlow::columnCount(-100, 200, 4), 1);
}


TEST(ColumnCountTest, HandlesDegenerateInputsWithoutDividingByZero)
{
	EXPECT_EQ(GridFlow::columnCount(600, 0, 4), 1);
	EXPECT_EQ(GridFlow::columnCount(600, -10, 4), 1);
	EXPECT_EQ(GridFlow::columnCount(600, 200, 0), 1) << "A zero cap should still yield one column";
}


//==============================================================================
// rowHeights
//==============================================================================

TEST(RowHeightsTest, EachRowTakesItsTallestCell)
{
	// Two columns, so rows are {10, 40} and {25, 5}.
	const std::vector<int> cells = {10, 40, 25, 5};
	const auto			   rows	 = GridFlow::rowHeights(cells, 2);

	ASSERT_EQ(rows.size(), 2u);
	EXPECT_EQ(rows[0], 40);
	EXPECT_EQ(rows[1], 25);
}


TEST(RowHeightsTest, HandlesAPartiallyFilledFinalRow)
{
	// Three columns, five cells: the last row holds only two.
	const std::vector<int> cells = {10, 20, 30, 40, 50};
	const auto			   rows	 = GridFlow::rowHeights(cells, 3);

	ASSERT_EQ(rows.size(), 2u);
	EXPECT_EQ(rows[0], 30);
	EXPECT_EQ(rows[1], 50);
}


TEST(RowHeightsTest, SingleColumnGivesOneRowPerCell)
{
	const std::vector<int> cells = {10, 20, 30};
	const auto			   rows	 = GridFlow::rowHeights(cells, 1);

	ASSERT_EQ(rows.size(), 3u);
	EXPECT_EQ(rows[0], 10);
	EXPECT_EQ(rows[1], 20);
	EXPECT_EQ(rows[2], 30);
}


TEST(RowHeightsTest, EmptyInputsYieldNoRows)
{
	EXPECT_TRUE(GridFlow::rowHeights({}, 3).empty());
	EXPECT_TRUE(GridFlow::rowHeights({10, 20}, 0).empty()) << "Zero columns cannot produce rows";
	EXPECT_TRUE(GridFlow::rowHeights({10, 20}, -1).empty());
}


//==============================================================================
// totalHeight
//==============================================================================

TEST(TotalHeightTest, SumsRowsAndTheGapsBetweenThem)
{
	// Rows are 40 and 25, with one 8px gap between them.
	const std::vector<int> cells = {10, 40, 25, 5};

	EXPECT_EQ(GridFlow::totalHeight(cells, 2, 8), 40 + 25 + 8);
}


TEST(TotalHeightTest, ASingleRowHasNoGap)
{
	const std::vector<int> cells = {10, 40};

	EXPECT_EQ(GridFlow::totalHeight(cells, 2, 8), 40) << "One row means zero inter-row gaps";
}


TEST(TotalHeightTest, EmptyGridIsZeroTall)
{
	EXPECT_EQ(GridFlow::totalHeight({}, 3, 8), 0);
	EXPECT_EQ(GridFlow::totalHeight({10, 20}, 0, 8), 0);
}


//==============================================================================
// cellBounds
//==============================================================================

TEST(CellBoundsTest, LaysCellsLeftToRightThenTopToBottom)
{
	const juce::Rectangle<int> area(0, 0, 316, 200); // 2 cols of 150 with an 16px gap
	const std::vector<int>	   rows	  = {50, 30};
	constexpr int			   gap	  = 16;

	const auto				   first  = GridFlow::cellBounds(area, 0, 2, gap, rows);
	const auto				   second = GridFlow::cellBounds(area, 1, 2, gap, rows);
	const auto				   third  = GridFlow::cellBounds(area, 2, 2, gap, rows);

	EXPECT_EQ(first.getX(), 0);
	EXPECT_EQ(first.getY(), 0);
	EXPECT_EQ(first.getWidth(), 150);
	EXPECT_EQ(first.getHeight(), 50) << "Row 0 is 50 tall";

	EXPECT_EQ(second.getX(), 166) << "Second column starts after the first column plus the gap";
	EXPECT_EQ(second.getY(), 0) << "Still row 0";

	EXPECT_EQ(third.getX(), 0) << "Third cell wraps back to column 0";
	EXPECT_EQ(third.getY(), 66) << "And drops by row 0's height plus the gap";
	EXPECT_EQ(third.getHeight(), 30) << "Row 1 is 30 tall";
}


TEST(CellBoundsTest, RespectsTheAreaOrigin)
{
	const juce::Rectangle<int> area(40, 25, 316, 200);
	const std::vector<int>	   rows	 = {50, 30};

	const auto				   first = GridFlow::cellBounds(area, 0, 2, 16, rows);

	EXPECT_EQ(first.getX(), 40) << "Cells should be offset by the area's origin";
	EXPECT_EQ(first.getY(), 25);
}


TEST(CellBoundsTest, CellsInARowShareAWidthAndFillTheArea)
{
	const juce::Rectangle<int> area(0, 0, 300, 200);
	const std::vector<int>	   rows = {50};
	constexpr int			   gap	= 10;
	constexpr int			   cols = 3;

	const auto				   a	= GridFlow::cellBounds(area, 0, cols, gap, rows);
	const auto				   b	= GridFlow::cellBounds(area, 1, cols, gap, rows);
	const auto				   c	= GridFlow::cellBounds(area, 2, cols, gap, rows);

	EXPECT_EQ(a.getWidth(), b.getWidth());
	EXPECT_EQ(b.getWidth(), c.getWidth());

	// Columns plus gaps should not overflow the area.
	EXPECT_LE(c.getRight(), area.getRight());

	// And they should not overlap.
	EXPECT_GE(b.getX(), a.getRight());
	EXPECT_GE(c.getX(), b.getRight());
}


TEST(CellBoundsTest, OutOfRangeIndicesReturnAnEmptyRectangle)
{
	const juce::Rectangle<int> area(0, 0, 300, 200);
	const std::vector<int>	   rows = {50};

	// Index 3 would be row 1, but only one row exists.
	EXPECT_TRUE(GridFlow::cellBounds(area, 3, 3, 10, rows).isEmpty());
	EXPECT_TRUE(GridFlow::cellBounds(area, 0, 0, 10, rows).isEmpty()) << "Zero columns has no valid cell";
	EXPECT_TRUE(GridFlow::cellBounds(area, 0, 3, 10, {}).isEmpty()) << "No rows means no valid cell";
}

} // namespace GridFlowTests
