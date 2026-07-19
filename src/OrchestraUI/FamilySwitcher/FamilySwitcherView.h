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

	std::vector<CardEntry> mCards;
	juce::Rectangle<int>   mGearBounds;
	juce::Rectangle<int>   mContentBounds;

	static constexpr int   kToolbarH   = 56;
	static constexpr int   kMaxContentW = 620;
	static constexpr int   kCardH	   = 74;
	static constexpr int   kGridGap	   = 12;
};
