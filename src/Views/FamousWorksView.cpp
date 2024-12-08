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

	addAndConfigureLabel(mTitle, "FamousWorksTitle", "Famous Works", mTitleX, mTitleY, mTitleWidth, mTitleHeight);

	addAndConfigureTextEditor(mFirstWork, mWorkX, mFirstWorkY, mWorkWidth, mWorkHeight);
	addAndConfigureTextEditor(mSecondWork, mWorkX, mSecondWorkY, mWorkWidth, mWorkHeight);
	addAndConfigureTextEditor(mThirdWork, mWorkX, mThirdWorkY, mWorkWidth, mWorkHeight);
}


void FamousWorksView::displayInstrument(InstrumentInfo &instrument)
{
	const StringArray &works = instrument.getFamousWorks();

	mFirstWork.setText(works[0], dontSendNotification);
	mSecondWork.setText(works[1], dontSendNotification);
	mThirdWork.setText(works[2], dontSendNotification);
}
