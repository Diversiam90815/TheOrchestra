/*
  ==============================================================================
	Module			TechniquesPanel
	Description		Technique card grid with inline descriptions.

					Scrolling is owned by the detail view's body viewport - this
					panel reports its natural height and flows into it.
  ==============================================================================
*/

#pragma once

#include "OrchestraPanel.h"


class TechniqueCard : public juce::Component
{
public:
	TechniqueCard(const std::string &name, const std::string &description);

	void					 paint(juce::Graphics &g) override;

	/*
	 @brief					Height this card needs for its wrapped description.
	*/
	int						 getPreferredHeight(int width) const;

	static constexpr int	 kNameHeight   = 24;
	static constexpr int	 kPadX		   = Space::l;
	static constexpr int	 kPadY		   = Space::m;
	static constexpr int	 kMinHeight	   = 76;

private:
	std::string mName;
	std::string mDesc;
};


class TechniquesPanel : public OrchestraPanel, public HasPreferredHeight
{
public:
	TechniquesPanel();
	~TechniquesPanel() override = default;

	void					 setInstrument(const InstrumentProfile &instrument) override;
	void					 resized() override;

	int						 getPreferredHeight(int width) const override;

private:
	std::vector<int>		 cellHeights(int width) const;

	std::vector<std::unique_ptr<TechniqueCard>> mCards;

	static constexpr int	 kMinColumnWidth = 380;
	static constexpr int	 kMaxColumns	 = 3;
	static constexpr int	 kGap			 = Space::m;
};
