/*
  ==============================================================================

	Module			CustomComponent
	Description		Customizing the Component class used by all sub-components

  ==============================================================================
*/

#pragma once
#include "JuceHeader.h"
#include "CustomLookAndFeel.h"


class CustomComponent : public Component
{
public:
	CustomComponent();
	~CustomComponent();

	void paint(Graphics &g) override;


private:
	CustomLookAndFeel mCustomLookNFeel;

	Path p;		// used for drawing the corner radius
};