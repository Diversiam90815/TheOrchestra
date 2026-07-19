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

	void	  setActiveTab(DetailTab tab);
	DetailTab getActiveTab() const { return mActiveTab; }

	void	  paint(juce::Graphics &g) override;
	void	  mouseUp(const juce::MouseEvent &e) override;

private:
	struct TabItem
	{
		DetailTab			 id;
		juce::String		 label;
		juce::Rectangle<int> bounds;	// filled in during paint/layout
	};

	void			layoutTabs();

	std::vector<TabItem> mTabs;
	DetailTab			 mActiveTab = DetailTab::Overview;

	static constexpr int kTabPadX	= 15;
	static constexpr int kLeftInset = 26;
};
