/*
  ==============================================================================
	Module			PluginEditor
	Description		Main UI - Three-column layout with header, sidebar, content, and piano roll
  ==============================================================================
*/

#pragma once

#include "PluginProcessor.h"

#include "PianoRoll.h"
#include "HeaderBar.h"
#include "InstrumentSidebar.h"
#include "InstrumentHeaderPanel.h"
#include "RangesPanel.h"
#include "RegisterPanel.h"
#include "TechniquesPanel.h"
#include "RolesPanel.h"
#include "FamousWorksPanel.h"
#include "SamplerPanel.h"


class OrchestraEditor : public juce::AudioProcessorEditor
{
public:
	OrchestraEditor(OrchestraProcessor &);
	~OrchestraEditor() override;

	void paint(juce::Graphics &) override;
	void resized() override;

private:
	void changeFamily(Family family);
	void changeInstrument(InstrumentID key);
	void onSettingsClicked();
	void onClefChanged(Clef clef);
	void onPitchModeChanged(PitchMode mode);

	CoreManager			  *mCoreManager;
	OrchestraProcessor	  &audioProcessor;

	CustomLookAndFeel	   mCustomLookAndFeel;

	// Navigation
	HeaderBar			   mHeaderBar;
	InstrumentSidebar	   mSidebar;

	// Center content panels
	InstrumentHeaderPanel  mInstrumentHeader;
	RangesPanel			   mRangesPanel;
	SamplerPanel		   mSamplerPanel;
	TechniquesPanel		   mTechniquesPanel;

	// Right detail panels
	RegisterPanel		   mRegisterPanel;
	RolesPanel			   mRolesPanel;
	FamousWorksPanel	   mFamousWorksPanel;

	// Piano roll
	PianoRoll			   mPianoRollView;

	// Layout constants
	static constexpr int   kWidth		= 1400;
	static constexpr int   kHeight		= 800;
	static constexpr int   kHeaderH		= 40;
	static constexpr int   kPianoH		= 120;
	static constexpr int   kSidebarW	= 280;
	static constexpr int   kDetailW		= 320;

	InstrumentID		   mCurrentInstrument = 0;
	Family				   mCurrentFamily	  = Family::Strings;

	friend class MainWindow;
};
