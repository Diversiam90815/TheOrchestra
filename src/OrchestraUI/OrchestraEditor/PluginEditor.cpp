/*
  ==============================================================================
	Module			PluginEditor
	Description		Main UI - Three-column layout with header, sidebar, content, and piano roll
  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


OrchestraEditor::OrchestraEditor(OrchestraProcessor &proc) : juce::AudioProcessorEditor(&proc), audioProcessor(proc)
{
	mCoreManager = &proc.getCoreManager();

	setLookAndFeel(&mCustomLookAndFeel);

	// Setup piano roll
	mPianoRollView.setKeyboardState(mCoreManager->getMidiKeyboardState());
	mPianoRollView.init();

	// Setup navigation callbacks
	mHeaderBar.setFamilySelectedCallback([this](Family family) { changeFamily(family); });

	mHeaderBar.setSettingsClickedCallback([this]() { onSettingsClicked(); });

	mSidebar.setInstrumentSelectedCallback([this](InstrumentID key) { changeInstrument(key); });

	// Setup instrument header callbacks
	mInstrumentHeader.setClefChangedCallback([this](Clef clef) { onClefChanged(clef); });
	mInstrumentHeader.setPitchModeChangedCallback([this](PitchMode mode) { onPitchModeChanged(mode); });

	// Setup sampler callback
	mSamplerPanel.setArticulationChangedCallback([this](Articulation articulation) { mCoreManager->changeArticulation(mCurrentInstrument, articulation); });

	// Add all components
	addAndMakeVisible(mHeaderBar);
	addAndMakeVisible(mSidebar);
	addAndMakeVisible(mInstrumentHeader);
	addAndMakeVisible(mRangesPanel);
	addAndMakeVisible(mSamplerPanel);
	addAndMakeVisible(mTechniquesPanel);
	addAndMakeVisible(mRegisterPanel);
	addAndMakeVisible(mRolesPanel);
	addAndMakeVisible(mFamousWorksPanel);
	addAndMakeVisible(mPianoRollView);

	setSize(kWidth, kHeight);

	// Load default instrument (Violin)
	changeFamily(Family::Strings);
}


OrchestraEditor::~OrchestraEditor()
{
	setLookAndFeel(nullptr);
}


void OrchestraEditor::changeFamily(Family family)
{
	mCurrentFamily = family;
	mHeaderBar.setActiveFamily(family);

	// Populate sidebar - this will auto-select the first instrument
	auto instrumentList = mCoreManager->getInstrumentsForFamily(family);

	// We need to give the sidebar access to the instrument list
	// The sidebar calls back with the selected instrument
	mSidebar.setFamily(family, instrumentList);
}


void OrchestraEditor::changeInstrument(InstrumentID key)
{
	mCurrentInstrument = key;
	auto instrument	   = mCoreManager->getInstrument(key);

	if (!instrument.isValid())
		return;

	// Update all panels
	mInstrumentHeader.setInstrument(instrument);
	mRangesPanel.setInstrument(instrument);
	mTechniquesPanel.setInstrument(instrument);
	mRegisterPanel.setInstrument(instrument);
	mRolesPanel.setInstrument(instrument);
	mFamousWorksPanel.setInstrument(instrument);
	mPianoRollView.displayInstrument(instrument);

	// Sampler uses available articulations
	auto availableSamples = mCoreManager->getAvailableArticulations(key);
	mSamplerPanel.setAvailableArticulations(availableSamples);

	resized();
}


void OrchestraEditor::onSettingsClicked()
{
	auto chooser = std::make_shared<juce::FileChooser>("Select Samples Folder", juce::File(), "*");

	chooser->launchAsync(juce::FileBrowserComponent::openMode | juce::FileBrowserComponent::canSelectDirectories,
						 [this, chooser](const juce::FileChooser &fc)
						 {
							 auto result = fc.getResult();
							 if (result.exists())
							 {
								 std::string directory = result.getFullPathName().toStdString();
								 mCoreManager->changeSamplesFolder(directory);

								 juce::AlertWindow::showMessageBoxAsync(juce::MessageBoxIconType::InfoIcon, "Samples folder updated",
																		 "The samples folder has been set to:\n" + result.getFullPathName(), "OK");
							 }
						 });
}


void OrchestraEditor::onClefChanged(Clef clef)
{
	mRangesPanel.setClef(clef);
}


void OrchestraEditor::onPitchModeChanged(PitchMode mode)
{
	mRangesPanel.setPitchMode(mode);
}


void OrchestraEditor::paint(juce::Graphics &g)
{
	g.fillAll(mCustomLookAndFeel.getBackgroundColour());
}


void OrchestraEditor::resized()
{
	const int contentX = kSidebarW;
	const int contentW = getWidth() - kSidebarW - kDetailW;
	const int contentH = getHeight() - kHeaderH - kPianoH;
	const int detailX  = getWidth() - kDetailW;
	const int gap	   = 12;
	const int pad	   = 12;

	// Header bar
	mHeaderBar.setBounds(0, 0, getWidth(), kHeaderH);

	// Left sidebar
	mSidebar.setBounds(0, kHeaderH, kSidebarW, contentH);

	// Piano roll
	mPianoRollView.setBounds(0, getHeight() - kPianoH, getWidth(), kPianoH);

	// Center content area
	int cx = contentX + pad;
	int cy = kHeaderH + pad;
	int cw = contentW - pad * 2;

	// Instrument header: ~100px
	const int headerPanelH = 100;
	mInstrumentHeader.setBounds(cx, cy, cw, headerPanelH);
	cy += headerPanelH + gap;

	// Ranges: ~120px (compact)
	const int rangesPanelH = 120;
	mRangesPanel.setBounds(cx, cy, cw, rangesPanelH);
	cy += rangesPanelH + gap;

	// Sampler: ~110px
	const int samplerPanelH = 110;
	mSamplerPanel.setBounds(cx, cy, cw, samplerPanelH);
	cy += samplerPanelH + gap;

	// Techniques: remaining space
	int techniquesH = (kHeaderH + contentH) - cy - pad;
	if (techniquesH < 100)
		techniquesH = 100;
	mTechniquesPanel.setBounds(cx, cy, cw, techniquesH);

	// Right detail panel
	int dx = detailX + pad;
	int dy = kHeaderH + pad;
	int dw = kDetailW - pad * 2;

	// Registers: flexible based on count, ~300px
	const int registerH = 300;
	mRegisterPanel.setBounds(dx, dy, dw, registerH);
	dy += registerH + gap;

	// Roles: ~150px
	const int rolesH = 150;
	mRolesPanel.setBounds(dx, dy, dw, rolesH);
	dy += rolesH + gap;

	// Famous Works: remaining
	int worksH = (kHeaderH + contentH) - dy - pad;
	if (worksH < 100)
		worksH = 100;
	mFamousWorksPanel.setBounds(dx, dy, dw, worksH);
}
