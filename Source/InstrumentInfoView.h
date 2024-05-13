/*
  ==============================================================================

	InstrumentInfoView.h
	Created: 8 Apr 2024 6:24:22pm
	Author:  Jens.Langenberg

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "InstrumentInfoModel.h"
#include "CustomPianoRoll.h"
#include "CustomLookAndFeel.h"


class InstrumentInfoView : public Component, public MenuBarModel
{
public:
	InstrumentInfoView(CustomPianoRoll &piano);
	~InstrumentInfoView();

private:
	void								displayLabels();

	void								resized() override;

	void								showInstrumentInfo(int key);

	void								displayText(Label &label, String text);

	void								setupHeading(Label &labelToSetup, const String &title);

	StringArray							getMenuBarNames() override;

	PopupMenu							getMenuForIndex(int topLevelMenuIndex, const String &menuName) override;

	void								menuItemSelected(int menuItemID, int topLevelMenuIndex) override;

	void								clearLabels(std::vector<std::unique_ptr<Label>> &labels);

	void								displayLabelsForCategory(const StringArray &texts, std::vector<std::unique_ptr<Label>> &labelsContainer, const int category);


	int									mCurrentSelectedInstrument = defaultInstrument; // Default value out of reach of different enums

	int									mCurrentFamily;

	MenuBarComponent					menuBar;

	InstrumentInfoModel					mInstrumentModel;

	Label								mInstrument;
	Label								mRangeTitle;
	Label								mUsefulInformationTitle;
	Label								mQualitiesTitle;
	Label								mTranspositionTitle;
	Label								mPlayingTechniquesTitle;
	Label								mFamousWorksTitle;

	std::vector<std::unique_ptr<Label>> mQualityLabels;
	std::vector<std::unique_ptr<Label>> mPlayingTechniqueLabels;
	std::vector<std::unique_ptr<Label>> mFamousWorksLabels;
	std::vector<std::unique_ptr<Label>> mUsefulInformationLabels;

	Label								mRange;

	Label								mTransposition;


	CustomPianoRoll					   &mCustomPianoRoll;

	CustomLookAndFeel					mCustomLookAndFeel;
};