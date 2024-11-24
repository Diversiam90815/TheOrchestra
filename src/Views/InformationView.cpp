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
	setSize(mWidth, mHeight);

	// Set the title
	addAndMakeVisible(mTitle);
	mTitle.setName("InformationTitle");
	mTitle.setText("Useful Information", dontSendNotification);
	mTitle.setBounds(mTitleX, mTitleY, mTitleWidth, mTitleHeight);
	mTitle.setJustificationType(Justification::centred);

	// Set the information label's positions
	addAndMakeVisible(&mFirstInformation);
	mFirstInformation.setBounds(mFirstColumX, mFirstRowY, mInfoWidth, mInfoHeight);

	addAndMakeVisible(&mSecondInformation);
	mSecondInformation.setBounds(mSecondColumx, mFirstRowY, mInfoWidth, mInfoHeight);

	addAndMakeVisible(&mThirdInformation);
	mThirdInformation.setBounds(mFirstColumX, mSecondRowY, mInfoWidth, mInfoHeight);

	addAndMakeVisible(&mFourthInformation);
	mFourthInformation.setBounds(mSecondColumx, mSecondRowY, mInfoWidth, mInfoHeight);
}


void InformationView::displayInstrument(InstrumentInfo &instrument)
{
	const StringArray &info = instrument.getInformation();

	mFirstInformation.setText(info[0], dontSendNotification);
	mSecondInformation.setText(info[1], dontSendNotification);
	mThirdInformation.setText(info[2], dontSendNotification);
	mFourthInformation.setText(info[3], dontSendNotification);
}
