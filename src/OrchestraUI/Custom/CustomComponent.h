/*
  ==============================================================================
	Module			CustomComponent
	Description		Customizing the Component class used by all sub-components
  ==============================================================================
*/

#pragma once

#include "JuceIncludes.h"
#include "CustomLookAndFeel.h"
#include "InstrumentInfo.h"
#include "Helper.h"


class CustomComponent : public juce::Component
{
public:
	CustomComponent();
	~CustomComponent();

	void		 paint(juce::Graphics &g) override;

	virtual void init()											  = 0;
	virtual void displayInstrument(InstrumentProfile &instrument) = 0;

protected:
	void addAndConfigureTextEditor(juce::TextEditor &editor, int x, int y, int width, int height);

	void addAndConfigureComboBox(juce::ComboBox &box, int x, int y, int width, int height);

	void addAndConfigureButton(juce::TextButton &button, const juce::String &componentName, int x, int y, int width, int height, bool initiallyVisible = true);

	void addAndConfigureLabel(juce::Label		 &label,
							  const juce::String &componentName,
							  const juce::String &text,
							  int				  x,
							  int				  y,
							  int				  width,
							  int				  height,
							  juce::Justification justification = juce::Justification::centred);

	void addAndConfigureImage(juce::DrawableImage &image, int x, int y, int width, int height);

	void setAndRescaleImage(juce::DrawableImage &imageToBeSet, juce::File &imagePath, int x, int y, int width, int height);

private:
	CustomLookAndFeel mCustomLookNFeel;

	juce::Path		  p; // used for drawing the corner radius
};