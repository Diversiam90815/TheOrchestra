/*
  ==============================================================================
	Module			HeaderBar
	Description		Family tab navigation bar with settings button
  ==============================================================================
*/

#pragma once

#include "JuceIncludes.h"
#include "Parameters.h"

#include <functional>


using FamilySelectedCallback	  = std::function<void(Family)>;
using SettingsClickedCallback	  = std::function<void()>;


class HeaderBar : public juce::Component
{
public:
	HeaderBar();
	~HeaderBar() override = default;

	void paint(juce::Graphics &g) override;
	void resized() override;

	void setFamilySelectedCallback(FamilySelectedCallback callback);
	void setSettingsClickedCallback(SettingsClickedCallback callback);

	void setActiveFamily(Family family);

private:
	void onFamilyClicked(Family family);

	juce::Label			   mLogo;

	juce::TextButton	   mWoodwindsTab;
	juce::TextButton	   mBrassTab;
	juce::TextButton	   mStringsTab;
	juce::TextButton	   mPercussionTab;
	juce::TextButton	   mSettingsBtn;

	Family				   mActiveFamily = Family::Strings;

	FamilySelectedCallback	mFamilySelectedCallback;
	SettingsClickedCallback mSettingsClickedCallback;

	std::vector<std::pair<juce::TextButton *, Family>> mTabs;
};
