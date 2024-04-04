
#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "PianoRoll.h"
#include "InstrumentInfo.h"

class OrchestraEditor : public juce::AudioProcessorEditor
{
public:

	//==============================================================================
	//				CONSTRUCTOR DESTRUCTOR
	//==============================================================================

	OrchestraEditor(OrchestraProcessor&);

	~OrchestraEditor() override;


	//==============================================================================
	//				PUBLIC METHODS
	//==============================================================================

	void paint(Graphics&) override;

	void resized() override;

	void showUI();

private:

	//==============================================================================
	//				PRIVATE OBJECTS
	//==============================================================================

	OrchestraProcessor& audioProcessor;

	PianoRoll mPianoRollView;

	InstrumentInfoView mInstrumentInfoView;

	MenuBarComponent mMenuBar;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(OrchestraEditor)
};
