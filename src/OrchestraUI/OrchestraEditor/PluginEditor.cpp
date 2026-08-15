/*
  ==============================================================================
	Module			PluginEditor
	Description		Main UI - view router between the family switcher and the instrument detail view
  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


OrchestraEditor::OrchestraEditor(OrchestraProcessor &proc) : juce::AudioProcessorEditor(&proc), audioProcessor(proc)
{
	mCoreManager = &proc.getCoreManager();

	setLookAndFeel(&mCustomLookAndFeel);

	// --- Family switcher (View A) ---
	mFamilySwitcher.onFamilySelected = [this](Family family)
	{
		changeFamily(family);
		showInstrumentDetail();
	};
	mFamilySwitcher.onSettings = [this]() { onSettingsClicked(); };

	// --- Instrument detail (View B) ---
	mDetailView.setInstrumentSelectedCallback([this](InstrumentID key) { changeInstrument(key); });
	mDetailView.setBackToFamiliesCallback([this]() { showFamilySwitcher(); });
	mDetailView.setArticulationChangedCallback([this](Articulation articulation) { return mCoreManager->changeArticulation(mCurrentInstrument, articulation); });

	// Piano roll wiring: keyboard state + CC send/reflect.
	mDetailView.initPianoRoll(mCoreManager->getMidiKeyboardState());
	mDetailView.setPianoRollCcCallbacks([this](int cc, int value) { mCoreManager->sendControllerChange(cc, value); },
										[this](int cc) { return mCoreManager->getLastControllerValue(cc); });

	addChildComponent(mFamilySwitcher);
	addChildComponent(mDetailView);

	populateFamilyCounts();

	// Resize limits live on the hosting window (see applyViewSize) so there is
	// only ever one constrainer in play.
	setResizable(true, true);

	// Start on the family switcher, at the family switcher's size.
	mFamilySwitcher.setSelectedFamily(mCurrentFamily);
	showFamilySwitcher();
}


bool OrchestraEditor::hasUserResized() const
{
	return mAppliedSize != juce::Point<int>(0, 0) && mAppliedSize != juce::Point<int>(getWidth(), getHeight());
}


void OrchestraEditor::applyViewSize(int width, int height, int minWidth, int minHeight)
{
	if (hasUserResized())
		return;

	// The window's constrainer works in window coordinates, so the content
	// minimum has to be widened by the frame and title bar.
	if (auto *window = dynamic_cast<juce::ResizableWindow *>(getTopLevelComponent()))
	{
		const auto border = window->getContentComponentBorder();

		window->setResizeLimits(minWidth + border.getLeftAndRight(), minHeight + border.getTopAndBottom(), 2560, 1600);
	}

	setSize(width, height);
	mAppliedSize = {width, height};
}


OrchestraEditor::~OrchestraEditor()
{
	setLookAndFeel(nullptr);
}


void OrchestraEditor::populateFamilyCounts()
{
	for (auto family : {Family::Woodwinds, Family::Brass, Family::Strings, Family::Percussion})
	{
		const int count = (int)mCoreManager->getInstrumentsForFamily(family).size();
		mFamilySwitcher.setFamilyCount(family, count);
	}
}


void OrchestraEditor::changeFamily(Family family)
{
	mCurrentFamily = family;
	mFamilySwitcher.setSelectedFamily(family);

	// Populate the detail sidebar; this auto-selects the first instrument (fires changeInstrument).
	auto instrumentList = mCoreManager->getInstrumentsForFamily(family);
	mDetailView.setFamily(family, instrumentList);
}


void OrchestraEditor::changeInstrument(InstrumentID key)
{
	auto instrument = mCoreManager->getInstrument(key);

	if (!instrument.isValid())
		return;

	mCurrentInstrument = key;

	// Resets the sampler (clears loaded sounds) before the new instrument's
	// articulation is loaded. Without this, switching instruments left the
	// previous instrument's samples loaded and still playable.
	mCoreManager->changeInstrument(key);

	mDetailView.setInstrument(instrument);

	auto availableSamples = mCoreManager->getAvailableArticulations(key);
	mDetailView.setAvailableArticulations(availableSamples);
}


void OrchestraEditor::showFamilySwitcher()
{
	mDetailView.setVisible(false);
	mFamilySwitcher.setVisible(true);

	applyViewSize(kFamilyWidth, kFamilyHeight, kFamilyMinWidth, kFamilyMinHeight);
	resized();
}


void OrchestraEditor::showInstrumentDetail()
{
	mFamilySwitcher.setVisible(false);
	mDetailView.setVisible(true);

	applyViewSize(kDetailWidth, kDetailHeight, kDetailMinWidth, kDetailMinHeight);
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


void OrchestraEditor::paint(juce::Graphics &g)
{
	g.fillAll(mCustomLookAndFeel.getTheme().background);
}


void OrchestraEditor::resized()
{
	mFamilySwitcher.setBounds(getLocalBounds());
	mDetailView.setBounds(getLocalBounds());
}
