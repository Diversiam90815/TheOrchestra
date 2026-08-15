/*
  ==============================================================================
	Module			FamilySwitcherView
	Description		The entry screen. Toolbar (logo + search + settings),
					a "Choose a family" title, and a 2x2 grid of family cards.
  ==============================================================================
*/

#pragma once

#include "JuceIncludes.h"
#include "Parameters.h"
#include "Theme.h"
#include "FamilyCard.h"

#include <functional>
#include <memory>
#include <vector>


class FamilySwitcherView : public juce::Component
{
public:
	FamilySwitcherView();
	~FamilySwitcherView() override = default;

	std::function<void(Family)> onFamilySelected;
	std::function<void()>		onSettings;

	void setFamilyCount(Family family, int count);
	void setSelectedFamily(Family family);

	void paint(juce::Graphics &g) override;
	void resized() override;
	void mouseUp(const juce::MouseEvent &e) override;

private:
	struct CardEntry
	{
		Family						family;
		std::unique_ptr<FamilyCard> card;
	};

	// Every rect is computed once in resized() and only read by paint().
	// Previously paint() re-derived the title offsets independently from
	// resized(), and mGearBounds was written in paint() but consumed by
	// mouseUp() - so the hit region was stale until the first repaint.
	void				   layout();

	std::vector<CardEntry> mCards;
	juce::Rectangle<int>   mGearBounds;
	juce::Rectangle<int>   mSearchBounds;
	juce::Rectangle<int>   mContentBounds;
	juce::Rectangle<int>   mTitleBounds;
	juce::Rectangle<int>   mSubtitleBounds;

	static constexpr int   kMaxContentW = 680;
	static constexpr int   kCardH		= 92;
	static constexpr int   kGridGap		= Space::l;
	static constexpr int   kTitleH		= 40;
	static constexpr int   kSubtitleH	= 28;
};
