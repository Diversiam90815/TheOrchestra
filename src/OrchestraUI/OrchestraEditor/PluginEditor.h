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

	/*
	 @brief					Resizes the window to a view's natural size.

							The family switcher needs far less room than the
							instrument detail, so each view carries its own size
							and minimum. Once the user has resized the window
							themselves this becomes a no-op - their choice wins
							from then on.
	 @param					[IN] width / height the view wants.
	 @param					[IN] minWidth / minHeight below which it breaks.
	*/
	void applyViewSize(int width, int height, int minWidth, int minHeight);

	/*
	 @brief					True once the window differs from the size this
							class last applied, i.e. the user dragged it.
	*/
	bool hasUserResized() const;

	CoreManager		 *mCoreManager;
	OrchestraProcessor &audioProcessor;

	CustomLookAndFeel	 mCustomLookAndFeel;

	// The two top-level views (toggled by the router)
	FamilySwitcherView	 mFamilySwitcher;
	InstrumentDetailView mDetailView;

	// Per-view window sizes. The family switcher is a four-card chooser and
	// does not need the detail view's footprint.
	static constexpr int kFamilyWidth	  = 1040;
	static constexpr int kFamilyHeight	  = 760;
	static constexpr int kFamilyMinWidth  = 880;
	static constexpr int kFamilyMinHeight = 620;

	static constexpr int kDetailWidth	  = 1480;
	static constexpr int kDetailHeight	  = 940;
	static constexpr int kDetailMinWidth  = 1240;
	static constexpr int kDetailMinHeight = 860;

	// The size this class last applied; if the window no longer matches it, the
	// user has taken over.
	juce::Point<int>	 mAppliedSize { 0, 0 };

	InstrumentID		 mCurrentInstrument = 0;
	Family				 mCurrentFamily		= Family::Strings;

	friend class MainWindow;
};
