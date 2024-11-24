/*
  ==============================================================================

	Module			CustomComponent
	Description		Customizing the Component class used by all sub-components

  ==============================================================================
*/

#include "CustomComponent.h"


CustomComponent::CustomComponent()
{
	setLookAndFeel(&mCustomLookNFeel);
}


CustomComponent::~CustomComponent()
{
	setLookAndFeel(nullptr);
}


void CustomComponent::paint(Graphics &g)
{
	float cornerRadius = mCustomLookNFeel.getCornerRadius();

	p.addRoundedRectangle(0, 0, static_cast<float>(getWidth()), static_cast<float>(getHeight()), cornerRadius, cornerRadius, true, true, true, true);

	g.setColour(mCustomLookNFeel.getBoxBackgroundColour());
	g.fillPath(p);
}
