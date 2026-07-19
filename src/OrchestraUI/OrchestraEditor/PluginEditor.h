/*
  ==============================================================================
	Module			PluginEditor
	Description		Main UI - view router between the family switcher and the instrument detail view
  ==============================================================================
*/

#pragma once

#include "PluginProcessor.h"

#include "CustomLookAndFeel.h"
#include "FamilySwitcherView.h"
#include "InstrumentDetailView.h"


class OrchestraEditor : public juce::AudioProcessorEditor
{
public:
	OrchestraEditor(OrchestraProcessor &);
	~OrchestraEditor() override;

	void	   paint(juce::Graphics &) override;
	void	   resized() override;

	// The underlying PianoRoll implements juce::MidiInputCallback; the app registers it for MIDI-in.
	PianoRoll &getPianoRollForMidiInput() { return mDetailView.getPianoRoll(); }

private:
	void changeFamily(Family family);
	void changeInstrument(InstrumentID key);
	void showFamilySwitcher();
	void showInstrumentDetail();
	void onSettingsClicked();
	void populateFamilyCounts();

	CoreManager		 *mCoreManager;
	OrchestraProcessor &audioProcessor;

	CustomLookAndFeel	 mCustomLookAndFeel;

	// The two top-level views (toggled by the router)
	FamilySwitcherView	 mFamilySwitcher;
	InstrumentDetailView mDetailView;

	static constexpr int kWidth	 = 1440;
	static constexpr int kHeight = 900;

	InstrumentID		 mCurrentInstrument = 0;
	Family				 mCurrentFamily		= Family::Strings;

	friend class MainWindow;
};
