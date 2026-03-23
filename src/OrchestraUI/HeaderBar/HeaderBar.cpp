/*
  ==============================================================================
	Module			HeaderBar
	Description		Family tab navigation bar with settings button
  ==============================================================================
*/

#include "HeaderBar.h"
#include "CustomLookAndFeel.h"


HeaderBar::HeaderBar()
{
	mTabs = {{&mWoodwindsTab, Family::Woodwinds},
			 {&mBrassTab, Family::Brass},
			 {&mStringsTab, Family::Strings},
			 {&mPercussionTab, Family::Percussion}};

	// Configure logo
	mLogo.setText("THE ORCHESTRA", juce::dontSendNotification);
	mLogo.setName("Logo");
	addAndMakeVisible(mLogo);

	// Configure family tabs
	mWoodwindsTab.setButtonText("WOODWINDS");
	mBrassTab.setButtonText("BRASS");
	mStringsTab.setButtonText("STRINGS");
	mPercussionTab.setButtonText("PERCUSSION");

	for (auto &[tab, family] : mTabs)
	{
		tab->setName("FamilyTab");
		tab->setClickingTogglesState(true);
		tab->setRadioGroupId(1);
		tab->onClick = [this, f = family]() { onFamilyClicked(f); };
		addAndMakeVisible(tab);
	}

	// Default to Strings
	mStringsTab.setToggleState(true, juce::dontSendNotification);

	// Settings button
	mSettingsBtn.setButtonText(juce::String::charToString(0x2699)); // Gear unicode
	mSettingsBtn.setName("SettingsButton");
	mSettingsBtn.onClick = [this]()
	{
		if (mSettingsClickedCallback)
			mSettingsClickedCallback();
	};
	addAndMakeVisible(mSettingsBtn);
}


void HeaderBar::paint(juce::Graphics &g)
{
	auto *lnf = dynamic_cast<CustomLookAndFeel *>(&getLookAndFeel());
	if (lnf)
		g.fillAll(lnf->getHeaderBarColour());
	else
		g.fillAll(juce::Colour(24, 21, 32));

	// Bottom border
	g.setColour(juce::Colours::white.withAlpha(0.04f));
	g.fillRect(0, getHeight() - 1, getWidth(), 1);
}


void HeaderBar::resized()
{
	auto area = getLocalBounds().reduced(12, 0);

	// Logo
	mLogo.setBounds(area.removeFromLeft(150).reduced(0, 4));

	area.removeFromLeft(12); // gap

	// Family tabs
	const int tabWidth	= 110;
	const int tabHeight = 28;
	const int tabY		= (getHeight() - tabHeight) / 2;
	const int tabGap	= 4;

	for (auto &[tab, family] : mTabs)
	{
		tab->setBounds(area.getX(), tabY, tabWidth, tabHeight);
		area.removeFromLeft(tabWidth + tabGap);
	}

	// Settings button (far right)
	mSettingsBtn.setBounds(getWidth() - 44, (getHeight() - 28) / 2, 28, 28);
}


void HeaderBar::setFamilySelectedCallback(FamilySelectedCallback callback)
{
	mFamilySelectedCallback = std::move(callback);
}


void HeaderBar::setSettingsClickedCallback(SettingsClickedCallback callback)
{
	mSettingsClickedCallback = std::move(callback);
}


void HeaderBar::setActiveFamily(Family family)
{
	mActiveFamily = family;
	for (auto &[tab, f] : mTabs)
	{
		tab->setToggleState(f == family, juce::dontSendNotification);
	}
}


void HeaderBar::onFamilyClicked(Family family)
{
	mActiveFamily = family;
	if (mFamilySelectedCallback)
		mFamilySelectedCallback(family);
}
