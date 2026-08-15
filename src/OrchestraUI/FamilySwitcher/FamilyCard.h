/*
  ==============================================================================
	Module			FamilyCard
	Description		One family card on the family-switcher screen: tinted glyph
					badge + name + instrument count. Clickable, with selected/hover
					states.
  ==============================================================================
*/

#pragma once

#include "JuceIncludes.h"
#include "Parameters.h"

#include <functional>


class FamilyCard : public juce::Component
{
public:
	FamilyCard(Family family, const juce::String &name, const juce::String &letter);
	~FamilyCard() override = default;

	std::function<void(Family)> onClicked;

	void				 setCount(int count);
	void				 setSelected(bool selected);

	void				 paint(juce::Graphics &g) override;
	void				 mouseEnter(const juce::MouseEvent &) override;
	void				 mouseExit(const juce::MouseEvent &) override;
	void				 mouseUp(const juce::MouseEvent &e) override;

	static constexpr int kBadgeSize = 54;

private:
	Family		 mFamily;
	juce::String mName;
	juce::String mLetter;
	int			 mCount	   = 0;
	bool		 mSelected = false;
	bool		 mHover	   = false;
};
