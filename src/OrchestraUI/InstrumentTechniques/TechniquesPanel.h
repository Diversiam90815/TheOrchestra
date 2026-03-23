/*
  ==============================================================================
	Module			TechniquesPanel
	Description		Dynamic scrollable technique card grid with inline descriptions
  ==============================================================================
*/

#pragma once

#include "OrchestraPanel.h"


class TechniqueCard : public juce::Component
{
public:
	TechniqueCard(const std::string &name, const std::string &description);
	void paint(juce::Graphics &g) override;

private:
	std::string mName;
	std::string mDesc;
};


class TechniquesPanel : public OrchestraPanel
{
public:
	TechniquesPanel();
	~TechniquesPanel() override = default;

	void setInstrument(const InstrumentProfile &instrument) override;
	void resized() override;

private:
	juce::Viewport									  mViewport;
	juce::Component									  mContent;
	std::vector<std::unique_ptr<TechniqueCard>>		  mCards;
};
