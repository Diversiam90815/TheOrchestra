/*
  ==============================================================================

	Module			TechniquesView
	Description		View box containing the various playing techniques of the instrument

  ==============================================================================
*/

#include "TechniquesView.h"


TechniquesView::TechniquesView() {}


TechniquesView::~TechniquesView() {}


void TechniquesView::init()
{
	setSize(mWidth, mHeight);

	addAndConfigureLabel(mTitle, "TechniqueTitle", "Playing Techniques", mTechTitleX, mTechTitleY, mTechTitleWidth, mTechTitleHeight);

	// First row of buttons
	addAndConfigureButton(mTech1, "Tech1", mFirstColumnX, mFirstRowY, mButtonWidth, mButtonHeight, false);
	addAndConfigureButton(mTech2, "Tech2", mSecondColumnX, mFirstRowY, mButtonWidth, mButtonHeight, false);
	addAndConfigureButton(mTech3, "Tech3", mThirdColumnX, mFirstRowY, mButtonWidth, mButtonHeight, false);

	// Second row of buttons
	addAndConfigureButton(mTech4, "Tech4", mFirstColumnX, mSecondRowY, mButtonWidth, mButtonHeight, false);
	addAndConfigureButton(mTech5, "Tech5", mSecondColumnX, mSecondRowY, mButtonWidth, mButtonHeight, false);
	addAndConfigureButton(mTech6, "Tech6", mThirdColumnX, mSecondRowY, mButtonWidth, mButtonHeight, false);

	// Third row of buttons
	addAndConfigureButton(mTech7, "Tech7", mLastRowFirstColumnX, mThirdRowY, mButtonWidth, mButtonHeight, false);
	addAndConfigureButton(mTech8, "Tech8", mLastRowSecondColumnX, mThirdRowY, mButtonWidth, mButtonHeight, false);
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
