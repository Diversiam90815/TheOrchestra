/*
  ==============================================================================
	Module			InstrumentHeaderPanel
	Description		Displays instrument name, image, family, clefs, transposition info
  ==============================================================================
*/

#pragma once

#include "OrchestraPanel.h"
#include "NotationRenderer.h"
#include "FileManager.h"

#include <functional>


using ClefChangedCallback	  = std::function<void(Clef)>;
using PitchModeChangedCallback = std::function<void(PitchMode)>;


class InstrumentHeaderPanel : public OrchestraPanel
{
public:
	InstrumentHeaderPanel();
	~InstrumentHeaderPanel() override = default;

	void setInstrument(const InstrumentProfile &instrument) override;
	void resized() override;

	void setClefChangedCallback(ClefChangedCallback callback);
	void setPitchModeChangedCallback(PitchModeChangedCallback callback);

private:
	void		rebuildMetaTags();
	juce::String deriveTranspositionLabel(const std::string &writtenLow, const std::string &soundingLow) const;

	juce::DrawableImage mInstrumentImage;
	juce::Label			mNameLabel;
	juce::Label			mFamilyLabel;
	juce::Label			mTranspositionLabel; // Shows "in Bb", "in F", etc.

	// Interactive clef + pitch mode toggle buttons
	std::vector<std::unique_ptr<juce::TextButton>> mClefButtons;
	std::unique_ptr<juce::TextButton>			   mWrittenBtn;
	std::unique_ptr<juce::TextButton>			   mSoundingBtn;

	InstrumentClefs			 mClefs;
	bool					 mHasTransposition = false;
	PitchMode				 mCurrentPitchMode = PitchMode::Written;
	Clef					 mCurrentClef	   = Clef::Treble;

	ClefChangedCallback		 mClefChangedCallback;
	PitchModeChangedCallback mPitchModeChangedCallback;

	FileManager				 mFileManager;
};
