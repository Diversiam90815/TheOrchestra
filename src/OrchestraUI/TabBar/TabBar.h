/*
  ==============================================================================
	Module			TabBar
	Description		Horizontal tab strip for the instrument detail view
  ==============================================================================
*/

#pragma once

#include <functional>
#include <vector>

#include "JuceIncludes.h"
#include "Theme.h"


enum class DetailTab
{
	Overview = 0,
	Techniques,
	Roles,
	FamousWorks
};


class TabBar : public juce::Component
{
public:
	TabBar();
	~TabBar() override = default;

	std::function<void(DetailTab)> onTabChanged;

	void						   setActiveTab(DetailTab tab);
	DetailTab					   getActiveTab() const { return mActiveTab; }

	void						   paint(juce::Graphics &g) override;
	void						   resized() override;
	void						   lookAndFeelChanged() override;
	void						   mouseUp(const juce::MouseEvent &e) override;

private:
	struct TabItem
	{
		DetailTab			 id;
		juce::String		 label;
		juce::Rectangle<int> bounds;
	};

	void				 layoutTabs();

	std::vector<TabItem> mTabs;
	DetailTab			 mActiveTab = DetailTab::Overview;

	static constexpr int kTabPadX	= Space::l;
	static constexpr int kTabGap	= Space::xs;
	static constexpr int kLeftInset = Space::xl;
};
