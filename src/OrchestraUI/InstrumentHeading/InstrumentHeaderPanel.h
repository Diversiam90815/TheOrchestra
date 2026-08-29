/*
  ==============================================================================
	Module			InstrumentHeaderPanel
	Description		Displays instrument name, image, family, clefs (info), transposition
  ==============================================================================
*/

#pragma once

#include "OrchestraPanel.h"
#include "InstrumentImageView.h"
#include "NotationRenderer.h"
#include "FileManager.h"

#include <functional>


using ClefChangedCallback	   = std::function<void(Clef)>;
using PitchModeChangedCallback = std::function<void(PitchMode)>;


class InstrumentHeaderPanel : public OrchestraPanel, public HasPreferredHeight
{
public:
	InstrumentHeaderPanel();
	~InstrumentHeaderPanel() override = default;

	void				 setInstrument(const InstrumentProfile &instrument) override;
	void				 resized() override;

	void				 setClefChangedCallback(ClefChangedCallback callback);
	void				 setPitchModeChangedCallback(PitchModeChangedCallback callback);

	Clef				 getCurrentClef() const { return mCurrentClef; }

	int					 getPreferredHeight(int width) const override;

	static constexpr int kImageWidth   = 100;
	static constexpr int kImageHeight  = 94;
	static constexpr int kNameHeight   = 46;
	static constexpr int kFamilyHeight = 28;
	static constexpr int kTagHeight	   = 32;
	static constexpr int kTagGap	   = Space::s;
	static constexpr int kTagPadX	   = Space::m;
	static constexpr int kMinTagWidth  = 72;

private:
	void										   rebuildMetaTags();
	int											   pillWidth(const juce::String &text) const;

	InstrumentImageView							   mInstrumentImage;
	juce::Label									   mNameLabel;
	juce::Label									   mFamilyLabel;

	std::vector<std::unique_ptr<juce::TextButton>> mClefButtons;
	std::unique_ptr<juce::Label>				   mTranspositionInfoLabel;

	// Written/Sounding toggle buttons (include transposition in text)
	std::unique_ptr<juce::TextButton>			   mWrittenBtn;
	std::unique_ptr<juce::TextButton>			   mSoundingBtn;

	InstrumentClefs								   mClefs;
	juce::String								   mTranspositionText;
	bool										   mHasTransposition = false;
	PitchMode									   mCurrentPitchMode = PitchMode::Written;
	Clef										   mCurrentClef		 = Clef::Treble;

	ClefChangedCallback							   mClefChangedCallback;
	PitchModeChangedCallback					   mPitchModeChangedCallback;

	FileManager									   mFileManager;
};
