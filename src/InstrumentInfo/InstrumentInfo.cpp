/*
  ==============================================================================

	Module			InstrumentInfo
	Description		Class storing information about each instrument

  ==============================================================================
*/


#include "InstrumentInfo.h"

InstrumentInfo::InstrumentInfo()
{
}

InstrumentInfo::InstrumentInfo(const String		 &name,
							   const String		 &range,
							   const StringArray &qualities,
							   const StringArray &roles,
							   const StringArray &famousWorks,
							   const String		 &transposition,
							   const StringArray &playingTechniques)
	: mName(name), mRange(range), mQualities(qualities), mUsefulInformation(roles), mFamousWorks(famousWorks), mTransposition(transposition), mPlayingTechniques(playingTechniques)
{
}

InstrumentInfo::~InstrumentInfo()
{
}
