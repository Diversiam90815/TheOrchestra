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


void CustomComponent::addAndConfigureTextEditor(TextEditor &editor, int x, int y, int width, int height)
{
	addAndMakeVisible(editor);
	editor.setBounds(x, y, width, height);
	editor.setFont(mCustomLookNFeel.getTextEditorFont());
	editor.setReadOnly(true);
	editor.setMultiLine(true);
	editor.setJustification(Justification::centred);
}


void CustomComponent::addAndConfigureComboBox(ComboBox &box, int x, int y, int width, int height)
{
	addAndMakeVisible(box);
	box.setBounds(x, y, width, height);
	box.setEditableText(false);
}


void CustomComponent::addAndConfigureButton(TextButton &button, const String &componentName, int x, int y, int width, int height, bool initiallyVisible)
{
	button.setName(componentName);

	if (componentName.contains("QualityHigher"))
	{
		button.setConnectedEdges(Button::ConnectedEdgeFlags::ConnectedOnLeft);
	}

	else if (componentName.contains("QualityLower"))
	{
		button.setConnectedEdges(Button::ConnectedEdgeFlags::ConnectedOnRight);
	}

	addAndMakeVisible(button);
	button.setVisible(initiallyVisible);
	button.setBounds(x, y, width, height);
}


void CustomComponent::addAndConfigureLabel(Label &label, const String &componentName, const String &text, int x, int y, int width, int height, Justification justification)
{
	label.setName(componentName);
	label.setText(text, dontSendNotification);
	addAndMakeVisible(label);
	label.setBounds(x, y, width, height);
	label.setJustificationType(justification);
}


void CustomComponent::addAndConfigureImage(DrawableImage &image, int x, int y, int width, int height)
{
	addAndMakeVisible(&image);
	image.setBounds(x, y, width, height);
}


void CustomComponent::setAndRescaleImage(DrawableImage &imageToBeSet, File &imagePath, int x, int y, int width, int height)
{
	Image image = ImageFileFormat::loadFrom(imagePath);
	image		= image.rescaled(width, height);

	imageToBeSet.setImage(image);

	// Reapply the bounds after setting the image
	imageToBeSet.setBounds(x, y, width, height);
}
