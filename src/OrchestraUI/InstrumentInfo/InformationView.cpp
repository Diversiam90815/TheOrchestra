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

	addAndConfigureLabel(mTitle, "InformationTitle", "Useful Information", mTitleX, mTitleY, mTitleWidth, mTitleHeight, juce::Justification::centred);

	addAndConfigureTextEditor(mFirstInformation, mFirstColumX, mFirstRowY, mInfoWidth, mInfoHeight);
	addAndConfigureTextEditor(mSecondInformation, mSecondColumx, mFirstRowY, mInfoWidth, mInfoHeight);
	addAndConfigureTextEditor(mThirdInformation, mFirstColumX, mSecondRowY, mInfoWidth, mInfoHeight);
	addAndConfigureTextEditor(mFourthInformation, mSecondColumx, mSecondRowY, mInfoWidth, mInfoHeight);
}


void InformationView::displayInstrument(InstrumentInfo &instrument)
{
	const auto &roles = instrument.getRoles();

	if (roles.empty())
		return;

	size_t size = roles.size();

	mFirstInformation.setText(roles.at(0).getRole(), juce::dontSendNotification);

	if (size > 1)
		mSecondInformation.setText(roles.at(1).getRole(), juce::dontSendNotification);

	if (size > 2)
		mThirdInformation.setText(roles.at(2).getRole(), juce::dontSendNotification);

	if (size > 3)
		mFourthInformation.setText(roles.at(3).getRole(), juce::dontSendNotification);
}
