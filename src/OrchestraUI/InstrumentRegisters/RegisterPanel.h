/*
  ==============================================================================
	Module			RegisterPanel
	Description		Panel displaying instrument register cards with color coding
  ==============================================================================
*/

#pragma once

#include "OrchestraPanel.h"


class RegisterPanel : public OrchestraPanel
{
public:
	RegisterPanel();
	~RegisterPanel() override = default;

	void paint(juce::Graphics &g) override;
	void setInstrument(const InstrumentProfile &instrument) override;

private:
	struct RegisterData
	{
		juce::String range;
		juce::String description;
	};

	std::vector<RegisterData> mRegisters;

	static constexpr int kCardHeight = 68;
	static constexpr int kBarWidth	 = 4;
	static constexpr int kCardGap	 = 8;
};
