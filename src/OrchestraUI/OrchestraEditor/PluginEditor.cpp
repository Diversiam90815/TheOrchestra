/*
  ==============================================================================
	Module			PluginEditor
	Description		User Interface
  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


OrchestraEditor::OrchestraEditor(OrchestraProcessor &proc) : juce::AudioProcessorEditor(&proc), audioProcessor(proc)
{
	mCoreManager = &proc.getCoreManager();

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
	mMenuBarComponent.setModel(&mMenuBar);
	addAndMakeVisible(mMenuBarComponent);

	addAndMakeVisible(mPianoRollView);
	addAndMakeVisible(mInstrumentView);
	addAndMakeVisible(mRangesView);
	addAndMakeVisible(mQualitiesView);
	addAndMakeVisible(mTechniquesView);
	addAndMakeVisible(mInfoView);
	addAndMakeVisible(mFamousWorksView);
	addAndMakeVisible(mSamplerView);

	setSize(mWidth, mHeight);
}


void OrchestraEditor::init()
{
	mPianoRollView.setKeyboardState(mCoreManager->getMidiKeyboardState());

	mPianoRollView.init();
	mInstrumentView.init();
	mRangesView.init();
	mQualitiesView.init();
	mTechniquesView.init();
	mInfoView.init();
	mFamousWorksView.init();
	mSamplerView.init();

	mMenuBar.setInstrumentSelectedCallback([this](InstrumentID key) { changeInstrument(key); });

	mMenuBar.setSampleFolderChangedCallback(
		[this](const juce::File &folder)
		{
			if (mCoreManager)
			{
				std::string directory = folder.getFullPathName().toStdString();
				mCoreManager->changeSamplesFolder(directory);

				// Show confirmation to user
				juce::AlertWindow::showMessageBoxAsync(juce::MessageBoxIconType::InfoIcon, "Samples folder updated",
													   "The samples folder has been set to:\n" + folder.getFullPathName(), "OK");
			}
		});

	mSamplerView.setArticulationChangedCallback([this](Articulation articulation) { mCoreManager->changeArticulation(mCurrentInstrument, articulation); });
}


void OrchestraEditor::changeInstrument(InstrumentID key)
{
	mCurrentInstrument = key;
	auto instrument	   = mCoreManager->getInstrument(key);

	if (!instrument.isValid())
	{
		LOG_ERROR("Instrument is not valid! We won't change the instrument now..");
		return;
	}

	auto availableSamples = mCoreManager->getAvailableArticulations(key);
	mSamplerView.displayInstrument(availableSamples);

	mInstrumentView.displayInstrument(instrument);
	mRangesView.displayInstrument(instrument);
	mQualitiesView.displayInstrument(instrument);
	mTechniquesView.displayInstrument(instrument);
	mFamousWorksView.displayInstrument(instrument);
	mInfoView.displayInstrument(instrument);
	mPianoRollView.displayInstrument(instrument);

	resized();
}


void OrchestraEditor::paint(juce::Graphics &g)
{
	g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));
}


void OrchestraEditor::resized()
{
	mQualitiesView.setBounds(mQualitiesViewX, mQualitiesViewY, mQualitiesView.getWidth(), mQualitiesView.getHeight());
	mRangesView.setBounds(mRangesViewX, mRangesViewY, mRangesView.getWidth(), mRangesView.getHeight());
	mInstrumentView.setBounds(mInstrumentViewX, mInstrumentViewY, mInstrumentView.getWidth(), mInstrumentView.getHeight());
	mTechniquesView.setBounds(mTechniquesViewX, mTechniquesViewY, mTechniquesView.getWidth(), mTechniquesView.getHeight());
	mInfoView.setBounds(mInfoViewX, mInfoViewY, mInfoView.getWidth(), mInfoView.getHeight());
	mFamousWorksView.setBounds(mFamousWorksViewX, mFamousWorksViewY, mFamousWorksView.getWidth(), mFamousWorksView.getHeight());
	mSamplerView.setBounds(mSamplerViewX, mSamplerViewY, mSamplerView.getWidth(), mSamplerView.getHeight());
	mPianoRollView.setBounds(mPianoRollX, mPianoRollY, mWidth, mPianoRollHeight);
	mMenuBarComponent.setBounds(mMenuBarX, mMenuBarY, mWidth, mMenuBarHeight);
}
