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

	for (auto &tech : techniques)
	{
		String left	 = splitColonizedStrings(tech, true);
		String right = splitColonizedStrings(tech, false);

		technique.emplace_back(left, right);
	}

	// Set up a lambda to configure buttons
	auto configureButton = [](Button &button, const std::pair<String, String> &tech)
	{
		button.setButtonText(tech.first);
		button.setTooltip(tech.second);
		button.setVisible(true);
	};

	Button *buttons[] = {&mTech1, &mTech2, &mTech3, &mTech4, &mTech5, &mTech6, &mTech7, &mTech8};

	// Iterate and configure available techniques, hide extra buttons
	for (size_t i = 0; i < std::size(buttons); ++i)
	{
		if (i < technique.size())
		{
			configureButton(*buttons[i], technique[i]);
		}
		else
		{
			buttons[i]->setVisible(false);
		}
	}
}
