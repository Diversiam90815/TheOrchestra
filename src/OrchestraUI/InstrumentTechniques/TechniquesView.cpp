/*
  ==============================================================================
	Module			TechniquesView
	Description		View box containing the various playing techniques of the instrument
  ==============================================================================
*/

#include "TechniquesView.h"


void TechniquesView::init()
{
	setSize(mWidth, mHeight);

	addAndConfigureLabel(mTitle, "TechniqueTitle", "Playing PlayingTechniques", mTechTitleX, mTechTitleY, mTechTitleWidth, mTechTitleHeight);

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


void TechniquesView::displayInstrument(InstrumentProfile &instrument)
{
	const auto &techniques		= instrument.getTechniques();

	// Set up a lambda to configure buttons
	auto		configureButton = [](juce::Button &button, const std::string &name, const std::string &description)
	{
		button.setButtonText(name);
		button.setTooltip(description);
		button.setVisible(true);
	};

	juce::Button *buttons[] = {&mTech1, &mTech2, &mTech3, &mTech4, &mTech5, &mTech6, &mTech7, &mTech8};

	// Iterate and configure available techniques, hide extra buttons
	for (size_t i = 0; i < std::size(buttons); ++i)
	{
		if (i < techniques.size())
		{
			configureButton(*buttons[i], techniques.at(i).getName(), techniques.at(i).getDescription());
		}
		else
		{
			buttons[i]->setVisible(false);
		}
	}
}
