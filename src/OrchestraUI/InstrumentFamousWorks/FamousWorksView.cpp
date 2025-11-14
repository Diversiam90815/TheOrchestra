/*
  ==============================================================================
	Module			InformationView
	Description		View box containing the useful additional information of the instrument
  ==============================================================================
*/

#include "FamousWorksView.h"


void FamousWorksView::init()
{
	setSize(mWidth, mHeight);

	addAndConfigureLabel(mTitle, "FamousWorksTitle", "Famous Works", mTitleX, mTitleY, mTitleWidth, mTitleHeight);

	addAndConfigureTextEditor(mFirstWork, mWorkX, mFirstWorkY, mWorkWidth, mWorkHeight);
	addAndConfigureTextEditor(mSecondWork, mWorkX, mSecondWorkY, mWorkWidth, mWorkHeight);
	addAndConfigureTextEditor(mThirdWork, mWorkX, mThirdWorkY, mWorkWidth, mWorkHeight);
}


void FamousWorksView::displayInstrument(InstrumentInfo &instrument)
{
	const auto &works = instrument.getFamousWorks();

	if (works.empty())
		return;

	size_t size = works.size();

	mFirstWork.setText(works.at(0).getWork(), juce::dontSendNotification);

	if (size > 1)
		mSecondWork.setText(works.at(1).getWork(), juce::dontSendNotification);

	if (size > 2)
		mThirdWork.setText(works.at(2).getWork(), juce::dontSendNotification);
}
