/*
  ==============================================================================

	Module			TechniquesView
	Description		View box containing the various playing techniques of the instrument

  ==============================================================================
*/

#include "TechniquesView.h"


TechniquesView::TechniquesView()
{
}


TechniquesView::~TechniquesView()
{
}


void TechniquesView::init()
{
	setSize(mWidth, mHeight);

	// Set the title
	addAndMakeVisible(&mTitle);
	mTitle.setName("TechniqueTitle");
	mTitle.setText("Playing Techniques", dontSendNotification);
	mTitle.setBounds(mTechTitleX, mTechTitleY, mTechTitleWidth, mTechTitleHeight);

	// Set first row of buttons
	addAndMakeVisible(&mTech1);
	mTech1.setBounds(mFirstColumnX, mFirstRowY, mButtonWidth, mButtonHeight);
	addAndMakeVisible(&mTech2);
	mTech2.setBounds(mSecondColumnX, mFirstRowY, mButtonWidth, mButtonHeight);
	addAndMakeVisible(&mTech3);
	mTech3.setBounds(mThirdColumnX, mFirstRowY, mButtonWidth, mButtonHeight);

	// Set second row of buttons
	addAndMakeVisible(&mTech4);
	mTech4.setBounds(mFirstColumnX, mSecondRowY, mButtonWidth, mButtonHeight);
	addAndMakeVisible(&mTech5);
	mTech5.setBounds(mSecondColumnX, mSecondRowY, mButtonWidth, mButtonHeight);
	addAndMakeVisible(&mTech6);
	mTech6.setBounds(mThirdColumnX, mSecondRowY, mButtonWidth, mButtonHeight);

	// Set third row of buttons
	addAndMakeVisible(&mTech7);
	mTech7.setBounds(mLastRowFirstColumnX, mThirdRowY, mButtonWidth, mButtonHeight);
	addAndMakeVisible(&mTech8);
	mTech8.setBounds(mLastRowSecondColumnX, mThirdRowY, mButtonWidth, mButtonHeight);
}


void TechniquesView::displayInstrument(InstrumentInfo &instrument)
{
	StringArray							   techniques = instrument.getTechniques();

	std::vector<std::pair<String, String>> technique;
	technique.reserve(8);

	for (auto &tech : techniques)
	{
		String left	 = splitColonizedStrings(tech, true);
		String right = splitColonizedStrings(tech, false);

		technique.emplace_back(left, right);
	}

	auto &technique1 = technique.at(0);
	auto &technique2 = technique.at(1);
	auto &technique3 = technique.at(2);		// last one when selecting Marimba
	auto &technique4 = technique.at(3);
	auto &technique5 = technique.at(4);
	auto &technique6 = technique.at(5);
	auto &technique7 = technique.at(6);
	auto &technique8 = technique.at(7);

	mTech1.setButtonText(technique1.first);
	mTech1.setTooltip(technique1.second);
	mTech2.setButtonText(technique2.first);
	mTech2.setTooltip(technique2.second);
	mTech3.setButtonText(technique3.first);
	mTech3.setTooltip(technique3.second);
	mTech4.setButtonText(technique4.first);
	mTech4.setTooltip(technique4.second);
	mTech5.setButtonText(technique5.first);
	mTech5.setTooltip(technique5.second);
	mTech6.setButtonText(technique6.first);
	mTech6.setTooltip(technique6.second);
	mTech7.setButtonText(technique7.first);
	mTech7.setTooltip(technique7.second);
	mTech8.setButtonText(technique8.first);
	mTech8.setTooltip(technique8.second);
}
