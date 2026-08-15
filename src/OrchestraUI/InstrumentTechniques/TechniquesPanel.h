/*
  ==============================================================================
	Module			TechniquesPanel
	Description		Technique card grid with inline descriptions
  ==============================================================================
*/

#pragma once

#include "OrchestraPanel.h"


class TechniqueCard : public juce::Component
{
public:
	TechniqueCard(const std::string &name, const std::string &description);

	void				 paint(juce::Graphics &g) override;

	int					 getPreferredHeight(int width) const;

	static constexpr int kNameHeight = 24;
	static constexpr int kPadX		 = Space::m;
	static constexpr int kPadY		 = Space::s + 2;
	static constexpr int kMinHeight	 = 60;

private:
	std::string mName;
	std::string mDesc;
};


class TechniquesPanel : public OrchestraPanel, public HasPreferredHeight
{
public:
	TechniquesPanel();
	~TechniquesPanel() override = default;

	void setInstrument(const InstrumentProfile &instrument) override;
	void resized() override;

	int	 getPreferredHeight(int width) const override;

private:
	std::vector<int>							cellHeights(int width) const;

	std::vector<std::unique_ptr<TechniqueCard>> mCards;

	static constexpr int						kMinColumnWidth = 290;
	static constexpr int						kMaxColumns		= 3;
	static constexpr int						kGap			= Space::m;
};
