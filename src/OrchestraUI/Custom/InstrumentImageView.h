/*
  ==============================================================================
	Module			InstrumentImageView
	Description		Draws an instrument photo at its natural aspect ratio
  ==============================================================================
*/

#pragma once

#include "JuceIncludes.h"


class InstrumentImageView : public juce::Component
{
public:
	InstrumentImageView();
	~InstrumentImageView() override = default;

	void setImageFile(const juce::File &file);

	void clear();

	bool hasImage() const { return mImage.isValid(); }

	void paint(juce::Graphics &g) override;

private:
	juce::Image mImage;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(InstrumentImageView)
};
