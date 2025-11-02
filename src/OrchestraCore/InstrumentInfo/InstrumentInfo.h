/*
  ==============================================================================
	Module			InstrumentInfo
	Description		Class storing information about each instrument
  ==============================================================================
*/

#pragma once

#include "JuceIncludes.h"

#include "Parameters.h"
#include "nlohmann/json.hpp"
#include "Helper.h"


struct Range
{
	Range() = default;
	explicit Range(const std::string &range) : range(range), transposition("") { setRanges(range); }

	explicit Range(const std::string &range, const std::string &displayedRange) : range(range), displayedRange(displayedRange)
	{
		setRanges(range);
		setDisplayedRanges(displayedRange);
	}

	explicit Range(const std::string &range, const std::string &displayedRange, const std::string &transposition)
		: range(range), displayedRange(displayedRange), transposition(transposition)
	{
		setRanges(range);
		setDisplayedRanges(displayedRange);
	}

	std::string getHigherRange() const { return higherRange; }
	std::string getLowerRange() const { return lowerRange; }
	const int	getHigherRangeNoteValue() const { return higherNoteRange; }
	const int	getLowerRangeNoteValue() const { return lowerNoteRange; }

	std::string getDisplayedHigherRange() const { return higherDisplay; }
	std::string getDisplayedLowerRange() const { return lowerDisplay; }
	const int	getDisplayedHigherRangeNoteValue() const { return higherDisplayedRange; }
	const int	getDisplayedLowerRangeNoteValue() const { return lowerDisplayedRange; }

	std::string getTransposition() const { return transposition; }

private:
	void setRanges(const std::string &range)
	{
		higherRange		= splitColonizedStrings(range, false);
		lowerRange		= splitColonizedStrings(range, true);
		higherNoteRange = turnNotenameIntoMidinumber(higherRange);
		lowerNoteRange	= turnNotenameIntoMidinumber(lowerRange);
	}

	void setDisplayedRanges(const std::string &displayedRange)
	{

		higherDisplay		 = splitColonizedStrings(displayedRange, false);
		lowerDisplay		 = splitColonizedStrings(displayedRange, true);
		higherDisplayedRange = turnNotenameIntoMidinumber(higherDisplay);
		lowerDisplayedRange	 = turnNotenameIntoMidinumber(lowerDisplay);
	}

	std::string range;
	std::string displayedRange; // The range that is displayed if it differs from the actual range such as for rhythmic percussion
	std::string transposition;

	std::string higherRange{""};
	std::string lowerRange{""};
	int			higherNoteRange{0};
	int			lowerNoteRange{0};

	std::string higherDisplay{""};
	std::string lowerDisplay{""};
	int			higherDisplayedRange{0};
	int			lowerDisplayedRange{0};

	NLOHMANN_DEFINE_TYPE_INTRUSIVE(Range, range, displayedRange, transposition)
};


struct FamousWork
{
	FamousWork() = default;
	explicit FamousWork(const std::string &t) : work(t) {}

	std::string getWork() const { return work; }

private:
	std::string work;

	NLOHMANN_DEFINE_TYPE_INTRUSIVE(FamousWork, work)
};


struct PlayingTechnique
{
	PlayingTechnique() = default;
	explicit PlayingTechnique(const std::string &technique)
	{
		name		= splitColonizedStrings(technique, true);
		description = splitColonizedStrings(technique, false);
	}

	std::string getName() const { return name; }
	std::string getDescription() const { return description; }

private:
	std::string name;
	std::string description;

	NLOHMANN_DEFINE_TYPE_INTRUSIVE(PlayingTechnique, name, description)
};


struct Quality
{
	Quality() = default;

	explicit Quality(const std::string &quality)
	{
		rangeNotation = splitColonizedStrings(quality, true);
		description	  = splitColonizedStrings(quality, false);

		lowerNote	  = getLowerOrHigherNote(rangeNotation, true);
		higherNote	  = getLowerOrHigherNote(rangeNotation, false);

		if (lowerNote.empty() || higherNote.empty())
		{
			// Single note case: Use the single note as both lower and higher note
			lowerNote  = rangeNotation;
			higherNote = rangeNotation;
		}
	}

	std::string getLowerRange() const { return higherNote; }
	std::string getHigherRange() const { return lowerNote; }
	int			getHigherNoteValue() const { return higherNoteValue; }
	int			getLowerNoteValue() const { return lowerNoteValue; }

	std::string getDescription() const { return description; }

private:
	std::string rangeNotation;

	std::string higherNote{""};
	std::string lowerNote{""};
	int			higherNoteValue{0};
	int			lowerNoteValue{0};

	std::string description;

	NLOHMANN_DEFINE_TYPE_INTRUSIVE(Quality, rangeNotation, description)
};


struct Role
{
	Role() = default;
	explicit Role(const std::string role) : role(role) {}

	std::string getRole() const { return role; }

private:
	std::string role;

	NLOHMANN_DEFINE_TYPE_INTRUSIVE(Role, role)
};


using Qualities	  = std::vector<Quality>;
using Techniques  = std::vector<PlayingTechnique>;
using Roles		  = std::vector<Role>;
using FamousWorks = std::vector<FamousWork>;


/*
 @brief             Struct defining an instrument and it's information (info can be found in InstrumentData.h)
*/
struct InstrumentInfo
{
public:
	InstrumentInfo()  = default;
	~InstrumentInfo() = default;

	InstrumentInfo(const std::string &name,
				   InstrumentID		  key,
				   const Range		 &range,
				   const Qualities	 &qualities,
				   const Roles		 &roles,
				   const FamousWorks &works,
				   const Techniques	 &techniques,
				   bool				  isRhythmicPercussion = false)
		: mName(name), mRange(range), mQualities(qualities), mRoles(roles), mFamousWorks(works), mPlayingTechniques(techniques), mKey(key),
		  mIsRhythmicPercussion(isRhythmicPercussion)
	{
	}

	std::string	 getName() const { return mName; }
	Range		 getRange() const { return mRange; }
	Qualities	 getQualities() const { return mQualities; }
	Roles		 getRoles() const { return mRoles; }
	FamousWorks	 getFamousWorks() const { return mFamousWorks; }
	Techniques	 getTechniques() const { return mPlayingTechniques; }
	InstrumentID getKey() const { return mKey; }
	bool		 isRhythmicPercussion() const { return mIsRhythmicPercussion; }

	bool		 isValid() { return !mName.empty() && mKey != 0; }

private:
	std::string	 mName;							// Name of the instrument
	Range		 mRange;						// Range of notes (lowest to highest playable note)
	Qualities	 mQualities;					// Sound characteristics of each section within the range
	Roles		 mRoles;						// Any useful information of the instrument
	FamousWorks	 mFamousWorks;					// Famous works presenting the qualitiy of the instrument
	Techniques	 mPlayingTechniques;			// Different playing techniques featured within the instrument's family
	bool		 mIsRhythmicPercussion = false; // If the instrument is a rhythmic percussion instrument, it will be set to true

	InstrumentID mKey				   = 0;		// 3 digit key defining the instrument (see Helper.h)

	NLOHMANN_DEFINE_TYPE_INTRUSIVE(InstrumentInfo, mName, mRange, mQualities, mRoles, mFamousWorks, mPlayingTechniques, mIsRhythmicPercussion, mKey)
};
