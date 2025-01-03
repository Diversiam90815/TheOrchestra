/*
  ==============================================================================

	Module			PluginEditor
	Description		User Interface

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


OrchestraEditor::OrchestraEditor(OrchestraProcessor &proc) : AudioProcessorEditor(&proc), audioProcessor(proc), mPianoRollView()
{
	init();
	showUI();
	setLookAndFeel(&mCustomLookAndFeel);
}


OrchestraEditor::~OrchestraEditor()
{
	setLookAndFeel(nullptr);
}


void OrchestraEditor::showUI()
{
	addAndMakeVisible(mPianoRollView);

	mMenuBar.setModel(&mCustomMenuBarModel);
	addAndMakeVisible(mMenuBar);


	addAndMakeVisible(mInstrumentView);
	addAndMakeVisible(mRangesView);
	addAndMakeVisible(mQualitiesView);
	addAndMakeVisible(mTechniquesView);
	addAndMakeVisible(mInfoView);
	addAndMakeVisible(mFamousWorksView);

	setSize(mWidth, mHeight);
}


void OrchestraEditor::init()
{
	mInstrumentView.init();
	mRangesView.init();
	mQualitiesView.init();
	mTechniquesView.init();
	mInfoView.init();
	mFamousWorksView.init();

	mCustomMenuBarModel.setInstrumentSelectedCallback([this](int key) { changeInstrument(key); });
}


void OrchestraEditor::changeInstrument(int key)
{
	auto instrument = mController.getInstrument(key);

	mInstrumentView.displayInstrument(instrument);
	mRangesView.displayInstrument(instrument);
	mQualitiesView.displayInstrument(instrument);
	mTechniquesView.displayInstrument(instrument);
	mFamousWorksView.displayInstrument(instrument);
	mInfoView.displayInstrument(instrument);

	bool result = mPianoRollView.mPianoRoll->setMidiRanges(instrument.getQualities());
	if (!result)
	{
		mPianoRollView.mPianoRoll->setMidiRanges(instrument.getRange());
	}
	mPianoRollView.repaint();
	resized();
}


void OrchestraEditor::paint(Graphics &g)
{
	g.fillAll(getLookAndFeel().findColour(ResizableWindow::backgroundColourId));
}


void OrchestraEditor::resized()
{
	mQualitiesView.setBounds(mQualitiesViewX, mQualitiesViewY, mQualitiesView.getWidth(), mQualitiesView.getHeight());
	mRangesView.setBounds(mRangesViewX, mRangesViewY, mRangesView.getWidth(), mRangesView.getHeight());
	mInstrumentView.setBounds(mInstrumentViewX, mInstrumentViewY, mInstrumentView.getWidth(), mInstrumentView.getHeight());
	mTechniquesView.setBounds(mTechniquesViewX, mTechniquesViewY, mTechniquesView.getWidth(), mTechniquesView.getHeight());
	mInfoView.setBounds(mInfoViewX, mInfoViewY, mInfoView.getWidth(), mInfoView.getHeight());
	mFamousWorksView.setBounds(mFamousWorksViewX, mFamousWorksViewY, mFamousWorksView.getWidth(), mFamousWorksView.getHeight());

	mPianoRollView.setBounds(mPianoRollX, mPianoRollY, mWidth, mPianoRollHeight);
	mMenuBar.setBounds(mMenuBarX, mMenuBarY, mWidth, mMenuBarHeight);
}
