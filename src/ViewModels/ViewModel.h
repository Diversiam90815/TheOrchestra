/*
  ==============================================================================

	Module			ViewModel
	Description		View model managing the info of the instrument

  ==============================================================================
*/

#pragma once
#include "InstrumentController.h"

#include "InstrumentRangesView.h"
#include "QualitiesView.h"
#include "TechniquesView.h"
#include "InformationView.h"
#include "FamousWorksView.h"


class ViewModel
{
public:
	ViewModel();
	~ViewModel();

	void init();

	void deinit();

	void setInstrument(int instrumentKey);

private:
	InstrumentController	 mInstrumentController;

	InstrumentRangesView mRangesView;
	QualitiesView		 mQualitiesView;
	TechniquesView		 mTechniquesView;
	InformationView		 mInfoView;
	FamousWorksView		 mFamousWorksView;
};
