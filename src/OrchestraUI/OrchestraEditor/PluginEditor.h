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
	void layoutCenterColumn(int availableHeight);
	void layoutRightColumn(int availableHeight);

	CoreManager			  *mCoreManager;
	OrchestraProcessor	  &audioProcessor;

	CustomLookAndFeel	   mCustomLookAndFeel;

	// Navigation
	HeaderBar			   mHeaderBar;
	InstrumentSidebar	   mSidebar;

	// Center content - wrapped in viewport for scrolling
	juce::Viewport		   mCenterViewport;
	juce::Component		   mCenterContent;
	InstrumentHeaderPanel  mInstrumentHeader;
	RangesPanel			   mRangesPanel;
	SamplerPanel		   mSamplerPanel;
	TechniquesPanel		   mTechniquesPanel;

	// Right detail - wrapped in viewport for scrolling
	juce::Viewport		   mRightViewport;
	juce::Component		   mRightContent;
	RegisterPanel		   mRegisterPanel;
	RolesPanel			   mRolesPanel;
	FamousWorksPanel	   mFamousWorksPanel;

	// Piano roll
	PianoRoll			   mPianoRollView;

	// Layout constants
	static constexpr int   kWidth		= 1440;
	static constexpr int   kHeight		= 900;
	static constexpr int   kHeaderH		= 40;
	static constexpr int   kPianoH		= 120;
	static constexpr int   kSidebarW	= 180;
	static constexpr int   kDetailW		= 290;

	InstrumentID		   mCurrentInstrument = 0;
	Family				   mCurrentFamily	  = Family::Strings;

	friend class MainWindow;
};
