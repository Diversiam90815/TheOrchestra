/*
  ==============================================================================
	Module			InstrumentInfo
	Description		Class storing information about each instrument
  ==============================================================================
*/

#pragma once

#include "JuceIncludes.h"

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
				   const StringArray &playingTechniques,
				   InstrumentID		  key,
				   bool				  isRhythmicPercussion = false,
				   String			  displayedRange	   = juce::String(""))
		: mName(name), mRange(range), mQualities(qualities), mUsefulInformation(roles), mFamousWorks(famousWorks), mTransposition(transposition),
		  mPlayingTechniques(playingTechniques), mKey(key), mIsRhythmicPercussion(isRhythmicPercussion), mDisplayedRange(displayedRange)
	{
	}

	~InstrumentInfo() = default;

	String		 getName() const { return mName; }
	String		 getRange() const { return mRange; }
	StringArray	 getQualities() const { return mQualities; }
	StringArray	 getInformation() const { return mUsefulInformation; }
	StringArray	 getFamousWorks() const { return mFamousWorks; }
	String		 getTransposition() const { return mTransposition; }
	StringArray	 getTechniques() const { return mPlayingTechniques; }
	InstrumentID getKey() const { return mKey; }
	String		 getDisplayedRange() const { return mDisplayedRange; }
	bool		 isRhythmicPercussion() const { return mIsRhythmicPercussion; }

	bool		 isValid() { return !mName.isEmpty() && mKey != 0; }

private:
	String		 mName;							// Name of the instrument
	String		 mRange;						// Range of notes (lowest to highest playable note)
	StringArray	 mQualities;					// Sound characteristics of each section within the range
	StringArray	 mUsefulInformation;			// Any useful information of the instrument
	StringArray	 mFamousWorks;					// Famous works presenting the qualitiy of the instrument
	String		 mTransposition;				// Information about the transposition of the instrument, if it applies
	StringArray	 mPlayingTechniques;			// Different playing techniques featured within the instrument's family
	bool		 mIsRhythmicPercussion = false; // If the instrument is a rhythmic percussion instrument, it will be set to true
	String		 mDisplayedRange;				// The range that is displayed if it differs from the actual range such as for rhythmic percussion

	InstrumentID mKey = 0;						// 3 digit key defining the instrument (see Helper.h)

	friend class InstrumentController;
	friend class InstrumentInfoView;
};
