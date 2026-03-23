/*
  ==============================================================================
	Module			RolesPanel
	Description		Panel displaying orchestration roles as a bulleted list
  ==============================================================================
*/

#include "RolesPanel.h"
#include "CustomLookAndFeel.h"


RolesPanel::RolesPanel() : OrchestraPanel("ORCHESTRATION ROLES")
{
}


void RolesPanel::setInstrument(const InstrumentProfile &instrument)
{
	mRoles.clear();

	for (const auto &role : instrument.getRoles())
		mRoles.push_back(juce::String(role.getRole()));

	repaint();
}


void RolesPanel::paint(juce::Graphics &g)
{
	OrchestraPanel::paint(g);

	auto *lnf = dynamic_cast<CustomLookAndFeel *>(&getLookAndFeel());
	if (!lnf || mRoles.empty())
		return;

	auto accentCol	  = lnf->getAccentColour();
	auto secondaryCol = lnf->getTextSecondaryColour();

	auto area = getContentArea();

	auto roleFont = juce::Font(lnf->getInstrumentTypeface()).withHeight(13.0f);
	roleFont.setExtraKerningFactor(0.003f);
	g.setFont(roleFont);

	for (size_t i = 0; i < mRoles.size(); ++i)
	{
		auto rowBounds = area.removeFromTop(kRowHeight);

		// Gold bullet dot
		auto bulletArea = rowBounds.removeFromLeft(kTextPadding);
		float bulletY	= bulletArea.getCentreY() - kBulletSize * 0.5f;
		float bulletX	= bulletArea.getX();
		g.setColour(accentCol);
		g.fillEllipse(bulletX, bulletY, kBulletSize, kBulletSize);

		// Role text
		g.setColour(secondaryCol);
		g.drawText(mRoles[i], rowBounds, juce::Justification::centredLeft, true);
	}
}
