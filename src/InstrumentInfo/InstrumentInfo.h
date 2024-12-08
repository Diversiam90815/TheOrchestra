/*
  ==============================================================================

	Module			InstrumentInfo
	Description		Class storing information about each instrument

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

#include "Parameters.h"

/*
 @brief             Struct defining an instrument and it's information (info can be found in InstrumentData.h)
*/
struct InstrumentInfo
{
public:
	InstrumentInfo() = default;

	InstrumentInfo(const String		 &name,
				   const String		 &range,
				   const StringArray &qualities,
				   const StringArray &roles,
				   const StringArray &famousWorks,
				   const String		 &transposition,
				   const StringArray &playingTechniques)
		: mName(name), mRange(range), mQualities(qualities), mUsefulInformation(roles), mFamousWorks(famousWorks), mTransposition(transposition),
		  mPlayingTechniques(playingTechniques)
	{
	}

	~InstrumentInfo() = default;

	String getName() const 
	{
		return mName;
	}

	String getRange() const 
	{
		return mRange;
	}

	StringArray getQualities() const 
	{
		return mQualities;
	}

	StringArray getInformation() const 
	{
		return mUsefulInformation;
	}

	StringArray getFamousWorks() const 
	{
		return mFamousWorks;
	}

	String getTransposition() const 
	{
		return mTransposition;
	}

	StringArray getTechniques() const 
	{
		return mPlayingTechniques;
	}


private:
	String		mName;				// Name of the instrument
	String		mRange;				// Range of notes (lowest to highest playable note)
	StringArray mQualities;			// Sound characteristics of each section within the range
	StringArray mUsefulInformation; // Any useful information of the instrument
	StringArray mFamousWorks;		// Famous works presenting the qualitiy of the instrument
	String		mTransposition;		// Information about the transposition of the instrument, if it applies
	StringArray mPlayingTechniques; // Different playing techniques featured within the instrument's family

	friend class InstrumentController;
	friend class InstrumentInfoView;
};
