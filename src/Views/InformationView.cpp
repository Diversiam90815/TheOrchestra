/*
  ==============================================================================

	Module			InformationView
	Description		View box containing the useful additional information of the instrument

  ==============================================================================
*/

#include "InformationView.h"


InformationView::InformationView()
{
}


InformationView::~InformationView()
{
}


void InformationView::init()
{
	setLookAndFeel(&mCustomLookAndFeel);
	setSize(mWidth, mHeight);

	// Set the title
	mTitle.setName("InformationTitle");
	mTitle.setText("Useful Information", dontSendNotification);
	mTitle.setBounds(mTitleX, mTitleY, mTitleWidth, mTitleHeight);

	// Set the information label's positions
	mFirstInformation.setBounds(mFirstColumX, mFirstRowY, mInfoWidth, mInfoHeight);
	mSecondInformation.setBounds(mSecondColumx, mFirstRowY, mInfoWidth, mInfoHeight);
	mThirdInformation.setBounds(mFirstColumX, mSecondRowY, mInfoWidth, mInfoHeight);
	mFourthInformation.setBounds(mSecondColumx, mSecondRowY, mInfoWidth, mInfoHeight);
}


void InformationView::deinit()
{
	setLookAndFeel(nullptr);
}
