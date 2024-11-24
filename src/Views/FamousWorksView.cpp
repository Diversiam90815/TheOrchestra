/*
  ==============================================================================

	Module			InformationView
	Description		View box containing the useful additional information of the instrument

  ==============================================================================
*/

#include "FamousWorksView.h"


FamousWorksView::FamousWorksView()
{
}


FamousWorksView::~FamousWorksView()
{
}


void FamousWorksView::init()
{
	setSize(mWidth, mHeight);

	// Set the title
	addAndMakeVisible(&mTitle);
	mTitle.setName("FamousWorksTitle");
	mTitle.setText("Famous Works", dontSendNotification);
	mTitle.setBounds(mTitleX, mTitleY, mTitleWidth, mTitleHeight);

	addAndMakeVisible(&mFirstWork);
	mFirstWork.setBounds(mWorkX, mFirstWorkY, mWorkWidth, mWorkHeight);
	addAndMakeVisible(&mSecondWork);
	mSecondWork.setBounds(mWorkX, mSecondWorkY, mWorkWidth, mWorkHeight);
	addAndMakeVisible(&mThirdWork);
	mThirdWork.setBounds(mWorkX, mThirdWorkY, mWorkWidth, mWorkHeight);
}


void FamousWorksView::displayInstrument(InstrumentInfo &instrument)
{
	const StringArray &works = instrument.getFamousWorks();

	mFirstWork.setText(works[0], dontSendNotification);
	mSecondWork.setText(works[1], dontSendNotification);
	mThirdWork.setText(works[2], dontSendNotification);
}
