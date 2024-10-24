/*
  ==============================================================================

	InstrumentInfoView.cpp
	Created: 8 Apr 2024 6:24:22pm
	Author:  Jens.Langenberg

  ==============================================================================
*/

#include "InstrumentInfoView.h"


InstrumentInfoView::InstrumentInfoView(CustomPianoRoll &piano, Sampler &sampler) : mCustomPianoRoll(piano), mOrchestraSampler(sampler)
{
	setLookAndFeel(&mCustomLookAndFeel);
	displayLabels();
}


InstrumentInfoView::~InstrumentInfoView()
{
	setLookAndFeel(nullptr);
}


void InstrumentInfoView::displayLabels()
{
	setupHeading(mInstrument, "Instrument");
	setupHeading(mRangeTitle, "Ranges");
	setupHeading(mQualitiesTitle, "Qualities");
	setupHeading(mFamousWorksTitle, "Famous Works");
	setupHeading(mPlayingTechniquesTitle, "Playing Techniques");
	setupHeading(mUsefulInformationTitle, "Useful Information");
	setupHeading(mTranspositionTitle, "Transposition");
}

void InstrumentInfoView::resized()
{
	float titleLabelHeight		 = 0.1f;																			 // Main title at the top
	float titleHeightPercentage	 = 0.05f;																			 // Height for each title label
	float spacingBetweenRows	 = 0.05f;																			 // Additional spacing between rows to avoid cramping
	float availableHeight		 = 1.0f - titleLabelHeight - (titleHeightPercentage * 6) - (spacingBetweenRows * 2); // Adjust for spacing
	float textEditorHeight		 = availableHeight / 3;																 // Dividing remaining space by 3 rows
	float minimumInfoLabelHeight = textEditorHeight / 5;

	mInstrument.setBoundsRelative(0.25f, 0.0f, 0.5f, titleLabelHeight);

	// Defining 3 rows
	float firstRowTitlesY  = titleLabelHeight;
	float firstRowYStart   = firstRowTitlesY + titleHeightPercentage;

	float secondRowTitlesY = firstRowYStart + textEditorHeight + spacingBetweenRows;
	float secondRowYStart  = secondRowTitlesY + titleHeightPercentage;

	float thirdRowTitlesY  = secondRowYStart + textEditorHeight + spacingBetweenRows;
	float thirdRowYStart   = thirdRowTitlesY + titleHeightPercentage;

	// Titles
	mRangeTitle.setBoundsRelative(0.0f, firstRowTitlesY, 0.5f, titleHeightPercentage);
	mQualitiesTitle.setBoundsRelative(0.5f, firstRowTitlesY, 0.5f, titleHeightPercentage);
	mRange.setBoundsRelative(0.0f, firstRowYStart, 0.5f, textEditorHeight);
	mUsefulInformationTitle.setBoundsRelative(0.0f, secondRowTitlesY, 0.5f, titleHeightPercentage);
	mTranspositionTitle.setBoundsRelative(0.5f, secondRowTitlesY, 0.5f, titleHeightPercentage);
	mTransposition.setBoundsRelative(0.5f, secondRowYStart, 0.5f, textEditorHeight);
	mPlayingTechniquesTitle.setBoundsRelative(0.0f, thirdRowTitlesY, 0.5f, titleHeightPercentage);
	mFamousWorksTitle.setBoundsRelative(0.5f, thirdRowTitlesY, 0.5f, titleHeightPercentage);


	// Dynamically setting labels for

	// mQualities
	float labelHeightQuality = std::min(textEditorHeight / mQualityLabels.size(), minimumInfoLabelHeight);
	float labelYStart		 = firstRowYStart;
	for (size_t i = 0; i < mQualityLabels.size(); ++i)
	{
		mQualityLabels[i]->setBoundsRelative(0.5f, labelYStart, 0.5f, labelHeightQuality);
		labelYStart += labelHeightQuality;
	}

	// mUsefulInformation
	labelYStart						   = secondRowYStart;
	float labelHeightUsefulInformation = std::min(textEditorHeight / mUsefulInformationLabels.size(), minimumInfoLabelHeight);
	for (size_t i = 0; i < mUsefulInformationLabels.size(); ++i)
	{
		mUsefulInformationLabels[i]->setBoundsRelative(0.0f, labelYStart, 0.5f, labelHeightUsefulInformation);
		labelYStart += labelHeightUsefulInformation;
	}

	// mPlayingTechniques
	float labelHeightPlayingTech = std::min(textEditorHeight / mPlayingTechniqueLabels.size(), minimumInfoLabelHeight);
	labelYStart					 = thirdRowYStart;
	for (size_t i = 0; i < mPlayingTechniqueLabels.size(); ++i)
	{
		mPlayingTechniqueLabels[i]->setBoundsRelative(0.0f, labelYStart, 0.5f, labelHeightPlayingTech);
		labelYStart += labelHeightPlayingTech;
	}

	// mFamousWorks
	labelYStart					 = thirdRowYStart;
	float labelHeightFamousWorks = std::min(textEditorHeight / mFamousWorksLabels.size(), minimumInfoLabelHeight);
	for (size_t i = 0; i < mFamousWorksLabels.size(); ++i)
	{
		mFamousWorksLabels[i]->setBoundsRelative(0.5f, labelYStart, 0.5f, labelHeightFamousWorks);
		labelYStart += labelHeightFamousWorks;
	}
}


StringArray InstrumentInfoView::getMenuBarNames()
{
	return {"Woodwinds", "Brass", "Strings", "Percussion"};
}


PopupMenu InstrumentInfoView::getMenuForIndex(int topLevelMenuIndex, const String &menuName)
{
	PopupMenu menu;

	if (topLevelMenuIndex == 0) // Woodwinds
	{
		menu.addItem(Woodwinds::Piccolo, PiccoloName);
		menu.addItem(Woodwinds::Flute, FluteName);
		menu.addItem(Woodwinds::Oboe, OboeName);
		menu.addItem(Woodwinds::CorAnglais, CorAnglaisName);
		menu.addItem(Woodwinds::Clarinet, ClarinetName);
		menu.addItem(Woodwinds::BassClarinet, BassClarinetName);
		menu.addItem(Woodwinds::Bassoon, BassoonName);
		menu.addItem(Woodwinds::Contrabassoon, ContrabassoonName);
	}
	else if (topLevelMenuIndex == 1) // Brass
	{
		menu.addItem(Brass::FrenchHorn, FrenchHornName);
		menu.addItem(Brass::Trumpet, TrumpetName);
		menu.addItem(Brass::TenorTrombone, TenorTromboneName);
		menu.addItem(Brass::BassTrombone, BassTromboneName);
		menu.addItem(Brass::Cimbasso, CimbassoName);
		menu.addItem(Brass::Tuba, TubaName);
	}
	else if (topLevelMenuIndex == 2) // Strings
	{
		menu.addItem(Strings::Violin, ViolinName);
		menu.addItem(Strings::Viola, ViolaName);
		menu.addItem(Strings::Violoncello, VioloncelloName);
		menu.addItem(Strings::DoubleBass, DoubleBassName);
	}
	else if (topLevelMenuIndex == 3) // Percussion
	{
		menu.addItem(Percussion::Celeste, CelesteName);
		menu.addItem(Percussion::Harp, HarpName);
		menu.addItem(Percussion::Timpani, TimpaniName);
		menu.addItem(Percussion::Marimba, MarimbaName);
	}

	return menu;
}


void InstrumentInfoView::menuItemSelected(int menuItemID, int topLevelMenuIndex)
{
	int key = (topLevelMenuIndex + 1) * 100 + menuItemID;
	showInstrumentInfo(key);
	mOrchestraSampler.addSoundsFromInstrumentToSampler(key);
}


void InstrumentInfoView::showInstrumentInfo(int key)
{
	auto info = mInstrumentModel.getInstrument(key);
	mInstrument.setText(info.mName, dontSendNotification);

	displayText(mRange, info.mRange);
	displayText(mTransposition, info.mTransposition);
	displayLabelsForCategory(info.mQualities, mQualityLabels, labelType::qualities);
	displayLabelsForCategory(info.mUsefulInformation, mUsefulInformationLabels, labelType::usefulinformation);
	displayLabelsForCategory(info.mFamousWorks, mFamousWorksLabels, labelType::famousworks);
	displayLabelsForCategory(info.mPlayingTechniques, mPlayingTechniqueLabels, labelType::playingtechnique);

	bool result = mCustomPianoRoll.setMidiRanges(info.mQualities);
	if (!result)
	{
		mCustomPianoRoll.setMidiRanges(info.mRange);
	}
	mCustomPianoRoll.repaint();
	resized();

	
}


void InstrumentInfoView::clearLabels(std::vector<std::unique_ptr<Label>> &labels)
{
	for (auto &label : labels)
	{
		removeChildComponent(label.get());
	}
	labels.clear();
}


void InstrumentInfoView::displayLabelsForCategory(const StringArray &texts, std::vector<std::unique_ptr<Label>> &labelsContainer, const int category)
{
	clearLabels(labelsContainer);
	String cat = String(category);

	for (const auto &text : texts)
	{
		auto label = std::make_unique<Label>();
		label->setName(cat);
		label->setText(text, dontSendNotification);
		label->setJustificationType(Justification::centredLeft);
		label->setMinimumHorizontalScale(0.0f);

		addAndMakeVisible(label.get());
		labelsContainer.push_back(std::move(label));
	}
}


void InstrumentInfoView::displayText(Label &label, String text)
{
	addAndMakeVisible(label);
	label.setText(text, dontSendNotification);
}


void InstrumentInfoView::setupHeading(Label &labelToSetup, const String &title)
{
	setLookAndFeel(&mCustomLookAndFeel);
	String category = String("Title");
	labelToSetup.setName(category);

	labelToSetup.setText(title, dontSendNotification);
	addAndMakeVisible(&labelToSetup);
}
