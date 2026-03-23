/*
  ==============================================================================
	Module			RolesPanel
	Description		Panel displaying orchestration roles as a bulleted list
  ==============================================================================
*/

#pragma once

#include "OrchestraPanel.h"


class RolesPanel : public OrchestraPanel
{
public:
	RolesPanel();
	~RolesPanel() override = default;

	void paint(juce::Graphics &g) override;
	void setInstrument(const InstrumentProfile &instrument) override;

private:
	std::vector<juce::String> mRoles;

	static constexpr int   kRowHeight	= 28;
	static constexpr float kBulletSize	= 5.0f;
	static constexpr int   kTextPadding = 18;
};
