/*
  ==============================================================================
	Module			FamilySwitcherView
	Description		The entry screen
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

	void						setFamilyCount(Family family, int count);
	void						setSelectedFamily(Family family);

	void						paint(juce::Graphics &g) override;
	void						resized() override;
	void						mouseUp(const juce::MouseEvent &e) override;

private:
	struct CardEntry
	{
		Family						family;
		std::unique_ptr<FamilyCard> card;
	};

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
