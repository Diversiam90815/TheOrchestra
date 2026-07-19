/*
  ==============================================================================
	Module			TabBar
	Description		Horizontal tab strip for the instrument detail view
  ==============================================================================
*/


#include "TabBar.h"
#include "CustomLookAndFeel.h"


TabBar::TabBar()
{
	mTabs = {
		{ DetailTab::Overview,	  "Overview",	  {} },
		{ DetailTab::Techniques,  "Techniques",	  {} },
		{ DetailTab::Roles,		  "Roles",		  {} },
		{ DetailTab::FamousWorks, "Famous Works", {} },
	};
}


void TabBar::setActiveTab(DetailTab tab)
{
	if (tab != mActiveTab)
	{
		mActiveTab = tab;
		repaint();
	}
}


void TabBar::layoutTabs()
{
	auto *lf   = dynamic_cast<CustomLookAndFeel *>(&getLookAndFeel());
	auto  font = lf ? lf->getSerifFont(12.5f, true) : juce::Font(12.5f);

	int x = kLeftInset;
	for (auto &tab : mTabs)
	{
		const int textW = font.getStringWidth(tab.label);
		const int tabW	= textW + kTabPadX * 2;
		tab.bounds		= juce::Rectangle<int>(x, 0, tabW, getHeight());
		x += tabW + 2;	// 2px gap between tabs
	}
}


void TabBar::paint(juce::Graphics &g)
{
	auto *lf = dynamic_cast<CustomLookAndFeel *>(&getLookAndFeel());

	const juce::Colour barBg	 = lf ? lf->getToolbarColour() : juce::Colour::fromRGB(24, 21, 32);
	const juce::Colour gold		 = lf ? lf->getAccentColour() : juce::Colour::fromRGB(196, 148, 58);
	const juce::Colour inactive	 = lf ? lf->getTextTertiaryColour() : juce::Colour::fromRGB(107, 103, 96);
	const juce::Colour divider	 = lf ? lf->getDividerColour(0.1f) : juce::Colour::fromRGB(196, 148, 58).withAlpha(0.1f);

	g.fillAll(barBg);

	layoutTabs();

	for (const auto &tab : mTabs)
	{
		const bool active = (tab.id == mActiveTab);

		g.setColour(active ? gold : inactive);
		g.setFont(lf ? lf->getSerifFont(12.5f, active) : juce::Font(12.5f));
		g.drawText(tab.label, tab.bounds, juce::Justification::centred, false);

		if (active)
		{
			auto underline = juce::Rectangle<int>(tab.bounds.getX() + kTabPadX, getHeight() - 2, tab.bounds.getWidth() - kTabPadX * 2, 2);
			g.setColour(gold);
			g.fillRect(underline);
		}
	}

	// Bottom hairline
	g.setColour(divider);
	g.fillRect(0, getHeight() - 1, getWidth(), 1);
}


void TabBar::mouseUp(const juce::MouseEvent &e)
{
	for (const auto &tab : mTabs)
	{
		if (tab.bounds.contains(e.getPosition()))
		{
			if (tab.id != mActiveTab)
			{
				setActiveTab(tab.id);
				if (onTabChanged)
					onTabChanged(tab.id);
			}
			return;
		}
	}
}
