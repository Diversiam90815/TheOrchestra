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

	// Setup center viewport (scrollable column for center panels)
	mCenterViewport.setViewedComponent(&mCenterContent, false);
	mCenterViewport.setScrollBarsShown(true, false);
	mCenterViewport.setScrollBarThickness(6);

	// Setup right viewport (scrollable column for detail panels)
	mRightViewport.setViewedComponent(&mRightContent, false);
	mRightViewport.setScrollBarsShown(true, false);
	mRightViewport.setScrollBarThickness(6);

	// Add center panels to the center content container
	mCenterContent.addAndMakeVisible(mInstrumentHeader);
	mCenterContent.addAndMakeVisible(mRangesPanel);
	mCenterContent.addAndMakeVisible(mSamplerPanel);
	mCenterContent.addAndMakeVisible(mTechniquesPanel);

	// Add right panels to the right content container
	mRightContent.addAndMakeVisible(mRegisterPanel);
	mRightContent.addAndMakeVisible(mRolesPanel);
	mRightContent.addAndMakeVisible(mFamousWorksPanel);

	// Add top-level components
	addAndMakeVisible(mHeaderBar);
	addAndMakeVisible(mSidebar);
	addAndMakeVisible(mCenterViewport);
	addAndMakeVisible(mRightViewport);
	addAndMakeVisible(mPianoRollView);

	setSize(kWidth, kHeight);
	setResizable(true, true);
	setResizeLimits(900, 500, 2560, 1600);

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


void OrchestraEditor::layoutCenterColumn(int availableHeight)
{
	const int gap = 12;
	const int cw  = mCenterViewport.getWidth() - 8; // account for scrollbar

	const int headerPanelH	   = 140;
	const int rangesPanelH	   = 140;
	const int samplerPanelH	   = 110;
	const int techniquesPanelH = 280; // generous default for techniques

	int totalNeeded = headerPanelH + gap + rangesPanelH + gap + samplerPanelH + gap + techniquesPanelH;
	int contentH	= juce::jmax(totalNeeded, availableHeight);

	mCenterContent.setSize(cw, contentH);

	int cy = 0;

	mInstrumentHeader.setBounds(0, cy, cw, headerPanelH);
	cy += headerPanelH + gap;

	mRangesPanel.setBounds(0, cy, cw, rangesPanelH);
	cy += rangesPanelH + gap;

	mSamplerPanel.setBounds(0, cy, cw, samplerPanelH);
	cy += samplerPanelH + gap;

	// Techniques gets remaining space, minimum 280px
	int techniquesH = juce::jmax(techniquesPanelH, contentH - cy);
	mTechniquesPanel.setBounds(0, cy, cw, techniquesH);
}


void OrchestraEditor::layoutRightColumn(int availableHeight)
{
	const int gap = 12;
	const int dw  = mRightViewport.getWidth() - 8; // account for scrollbar

	// Calculate register panel height dynamically based on register count
	int registerCount = static_cast<int>(mRegisterPanel.getRegisterCount());
	if (registerCount < 1)
		registerCount = 4; // default assumption

	const int registerCardH = 64;
	const int registerGap	= 8;
	const int registerPad	= 16 * 2 + 24; // kPadding*2 + kTitleHeight
	int registerH = registerPad + registerCount * registerCardH + (registerCount - 1) * registerGap;

	const int rolesH = 170;
	const int worksH = 200;

	int totalNeeded = registerH + gap + rolesH + gap + worksH;
	int contentH	= juce::jmax(totalNeeded, availableHeight);

	mRightContent.setSize(dw, contentH);

	int dy = 0;

	mRegisterPanel.setBounds(0, dy, dw, registerH);
	dy += registerH + gap;

	mRolesPanel.setBounds(0, dy, dw, rolesH);
	dy += rolesH + gap;

	// Famous Works gets remaining space
	int worksHActual = juce::jmax(worksH, contentH - dy);
	mFamousWorksPanel.setBounds(0, dy, dw, worksHActual);
}


void OrchestraEditor::resized()
{
	const int contentW = getWidth() - kSidebarW - kDetailW;
	const int contentH = getHeight() - kHeaderH - kPianoH;
	const int detailX  = getWidth() - kDetailW;
	const int pad	   = 12;

	// Header bar
	mHeaderBar.setBounds(0, 0, getWidth(), kHeaderH);

	// Left sidebar
	mSidebar.setBounds(0, kHeaderH, kSidebarW, contentH);

	// Piano roll
	mPianoRollView.setBounds(0, getHeight() - kPianoH, getWidth(), kPianoH);

	// Center viewport
	mCenterViewport.setBounds(kSidebarW + pad, kHeaderH + pad, contentW - pad * 2, contentH - pad * 2);
	layoutCenterColumn(contentH - pad * 2);

	// Right detail viewport
	mRightViewport.setBounds(detailX + pad, kHeaderH + pad, kDetailW - pad * 2, contentH - pad * 2);
	layoutRightColumn(contentH - pad * 2);
}
