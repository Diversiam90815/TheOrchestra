/*
  ==============================================================================

	InstrumentInfo.cpp
	Created: 1 Apr 2024 3:50:07pm
	Author:  jerry

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
