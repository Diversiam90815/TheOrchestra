/*
  ==============================================================================
	Module			TabBar
	Description		Horizontal tab strip for the instrument detail view
  ==============================================================================
*/


#include "TabBar.h"
#include "CustomLookAndFeel.h"
#include "TextMeasure.h"


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
	auto  font = lf ? lf->getSerifFont(Type::bodySmall, true) : juce::Font(Type::bodySmall);

	int	  x	   = kLeftInset;
	for (auto &tab : mTabs)
	{
		const int tabW = TextMeasure::lineWidth(font, tab.label) + kTabPadX * 2;
		tab.bounds	   = juce::Rectangle<int>(x, 0, tabW, getHeight());
		x += tabW + kTabGap;
	}
}


void TabBar::resized()
{
	layoutTabs();
}


void TabBar::lookAndFeelChanged()
{
	// Tab widths are measured from the font, so re-run when the font source changes.
	layoutTabs();
}


void TabBar::paint(juce::Graphics &g)
{
	auto	   *lf = dynamic_cast<CustomLookAndFeel *>(&getLookAndFeel());
	const auto &t  = themeFor(*this);

	g.fillAll(t.toolbar);

	for (const auto &tab : mTabs)
	{
		const bool active = (tab.id == mActiveTab);

		g.setColour(active ? t.accent : t.textTertiary);
		g.setFont(lf ? lf->getSerifFont(Type::bodySmall, active) : juce::Font(Type::bodySmall));
		g.drawText(tab.label, tab.bounds, juce::Justification::centred, false);

		if (active)
		{
			g.setColour(t.accent);
			g.fillRect(tab.bounds.getX() + kTabPadX, getHeight() - 2, tab.bounds.getWidth() - kTabPadX * 2, 2);
		}
	}

	// Bottom hairline
	g.setColour(t.divider(0.1f));
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
