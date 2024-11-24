/*
  ==============================================================================

	Module			CustomComponent
	Description		Customizing the Component class used by all sub-components

  ==============================================================================
*/

#pragma once
#include "JuceHeader.h"
#include "CustomLookAndFeel.h"
#include "InstrumentInfo.h"
#include "Helper.h"


class CustomComponent : public Component
{
public:
	CustomComponent();
	~CustomComponent();

	void		 paint(Graphics &g) override;

	virtual void displayInstrument(InstrumentInfo &instrument) = 0;

private:
	CustomLookAndFeel mCustomLookNFeel;

	Path			  p; // used for drawing the corner radius
};