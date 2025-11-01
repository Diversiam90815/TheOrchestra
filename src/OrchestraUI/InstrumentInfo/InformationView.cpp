/*
  ==============================================================================
	Module			InformationView
	Description		View box containing the useful additional information of the instrument
  ==============================================================================
*/

#include "InformationView.h"


void InformationView::init()
{
	setSize(mWidth, mHeight);

	addAndConfigureLabel(mTitle, "InformationTitle", "Useful Information", mTitleX, mTitleY, mTitleWidth, mTitleHeight, Justification::centred);

	addAndConfigureTextEditor(mFirstInformation, mFirstColumX, mFirstRowY, mInfoWidth, mInfoHeight);
	addAndConfigureTextEditor(mSecondInformation, mSecondColumx, mFirstRowY, mInfoWidth, mInfoHeight);
	addAndConfigureTextEditor(mThirdInformation, mFirstColumX, mSecondRowY, mInfoWidth, mInfoHeight);
	addAndConfigureTextEditor(mFourthInformation, mSecondColumx, mSecondRowY, mInfoWidth, mInfoHeight);
}


void InformationView::displayInstrument(InstrumentInfo &instrument)
{
	const StringArray &info = instrument.getInformation();

	mFirstInformation.setText(info[0], dontSendNotification);
	mSecondInformation.setText(info[1], dontSendNotification);
	mThirdInformation.setText(info[2], dontSendNotification);
	mFourthInformation.setText(info[3], dontSendNotification);
}
