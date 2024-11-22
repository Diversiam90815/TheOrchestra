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
	setLookAndFeel(&mCustomLookAndFeel);
	setSize(mWidth, mHeight);

	// Set the title
	mTitle.setName("TechniqueTitle");
	mTitle.setText("Playing Techniques", dontSendNotification);
	mTitle.setBounds(mTechTitleX, mTechTitleY, mTechTitleWidth, mTechTitleHeight);

	// Set first row of buttons
	mTech1.setBounds(mFirstColumnX, mFirstRowY, mButtonWidth, mButtonHeight);
	mTech2.setBounds(mSecondColumnX, mFirstRowY, mButtonWidth, mButtonHeight);
	mTech3.setBounds(mThirdColumnX, mFirstRowY, mButtonWidth, mButtonHeight);

	// Set second row of buttons
	mTech4.setBounds(mFirstColumnX, mSecondRowY, mButtonWidth, mButtonHeight);
	mTech5.setBounds(mSecondColumnX, mSecondRowY, mButtonWidth, mButtonHeight);
	mTech6.setBounds(mThirdColumnX, mSecondRowY, mButtonWidth, mButtonHeight);

	// Set third row of buttons
	mTech7.setBounds(mLastRowFirstColumnX, mThirdColumnX, mButtonWidth, mButtonHeight);
	mTech8.setBounds(mLastRowSecondColumnX, mThirdColumnX, mButtonWidth, mButtonHeight);
}


void TechniquesView::deinit()
{
	setLookAndFeel(nullptr);
}
