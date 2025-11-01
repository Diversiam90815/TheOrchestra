/*
  ==============================================================================
	Module			PluginEditor
	Description		User Interface
  ==============================================================================
*/
#pragma once

#include "PluginProcessor.h"

#include "PianoRoll.h"
#include "MenuBar.h"
#include "InstrumentRangesView.h"
#include "QualitiesView.h"
#include "TechniquesView.h"
#include "InformationView.h"
#include "FamousWorksView.h"
#include "InstrumentView.h"
#include "SamplerView.h"


class OrchestraEditor : public AudioProcessorEditor
{
public:
	OrchestraEditor(OrchestraProcessor &);
	~OrchestraEditor() override;

	void paint(Graphics &) override;
	void resized() override;

	void init();
	void showUI();

private:
	void				 changeInstrument(InstrumentID key);

	CoreManager			*mCoreManager;

	OrchestraProcessor	&audioProcessor;

	PianoRoll			 mPianoRollView;
	MenuBar				 mMenuBar;

	MenuBarComponent	 mMenuBarComponent;

	CustomLookAndFeel	 mCustomLookAndFeel;

	InstrumentView		 mInstrumentView;
	InstrumentRangesView mRangesView;
	QualitiesView		 mQualitiesView;
	TechniquesView		 mTechniquesView;
	InformationView		 mInfoView;
	FamousWorksView		 mFamousWorksView;
	SamplerView			 mSamplerView;

	const int			 mInstrumentViewX	= 443;
	const int			 mInstrumentViewY	= 49;

	const int			 mRangesViewX		= 16;
	const int			 mRangesViewY		= 145;

	const int			 mQualitiesViewX	= 325;
	const int			 mQualitiesViewY	= 145;

	const int			 mTechniquesViewX	= 650;
	const int			 mTechniquesViewY	= 145;

	const int			 mInfoViewX			= 654;
	const int			 mInfoViewY			= 389;

	const int			 mFamousWorksViewX	= 962;
	const int			 mFamousWorksViewY	= 145;

	const int			 mSamplerViewX		= 335;
	const int			 mSamplerViewY		= 459;

	const int			 mPianoRollX		= 0;
	const int			 mPianoRollY		= 586;
	const int			 mPianoRollHeight	= 114;

	const int			 mMenuBarX			= 0;
	const int			 mMenuBarY			= 0;
	const int			 mMenuBarHeight		= 30;

	const int			 mWidth				= 1200;
	const int			 mHeight			= 700;

	InstrumentID		 mCurrentInstrument = 0;

	friend class MainWindow;
};
