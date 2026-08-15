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

	void	  setActiveTab(DetailTab tab);
	DetailTab getActiveTab() const { return mActiveTab; }

	void	  paint(juce::Graphics &g) override;
	void	  resized() override;
	void	  lookAndFeelChanged() override;
	void	  mouseUp(const juce::MouseEvent &e) override;

private:
	struct TabItem
	{
		DetailTab			 id;
		juce::String		 label;
		juce::Rectangle<int> bounds;
	};

	// Tab widths are text-measured, so layout must re-run whenever the size or
	// the font changes - not from paint(), which left mouseUp() hit-testing
	// bounds that were only valid after the first repaint.
	void				 layoutTabs();

	std::vector<TabItem> mTabs;
	DetailTab			 mActiveTab = DetailTab::Overview;

	static constexpr int kTabPadX	= Space::l;
	static constexpr int kTabGap	= Space::xs;
	static constexpr int kLeftInset = Space::xl;
};
