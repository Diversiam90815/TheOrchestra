/*
  ==============================================================================
	Module			RolesPanel
	Description		Panel displaying orchestration roles as a bulleted, wrapped
					multi-column card grid.
  ==============================================================================
*/

#pragma once

#include "OrchestraPanel.h"


class RolesPanel : public OrchestraPanel, public HasPreferredHeight
{
public:
	RolesPanel();
	~RolesPanel() override = default;

	void					  paint(juce::Graphics &g) override;
	void					  setInstrument(const InstrumentProfile &instrument) override;

	int						  getPreferredHeight(int width) const override;

private:
	// Roles run to 83 characters, so each one is a wrapped block rather than a
	// single ellipsised line.
	int						  measureCell(const juce::Font &font, const juce::String &role, int cellWidth) const;
	std::vector<int>		  cellHeights(int width) const;

	std::vector<juce::String> mRoles;

	static constexpr int	  kMinColumnWidth = 350;
	static constexpr int	  kMaxColumns	  = 3;
	static constexpr int	  kGap			  = Space::l;
	static constexpr int	  kBulletGutter	  = Space::xl + Space::xs;
	static constexpr float	  kBulletSize	  = 7.0f;
	static constexpr int	  kMinCellHeight  = 48;
};
