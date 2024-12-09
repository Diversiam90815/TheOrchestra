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

protected:
	void addAndConfigureTextEditor(TextEditor &editor, int x, int y, int width, int height);

	void addAndConfigureButton(TextButton &button, const String &componentName, int x, int y, int width, int height, bool initiallyVisible = true);

	void addAndConfigureLabel(
		Label &label, const String &componentName, const String &text, int x, int y, int width, int height, Justification justification = Justification::centred);

	void addAndConfigureImage(DrawableImage &image, int x, int y, int width, int height);

	void setAndRescaleImage(DrawableImage &imageToBeSet, File &imagePath, int x, int y, int width, int height);

private:
	CustomLookAndFeel mCustomLookNFeel;

	Path			  p; // used for drawing the corner radius
};