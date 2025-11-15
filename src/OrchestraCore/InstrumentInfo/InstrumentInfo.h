/*
  ==============================================================================
	Module			InstrumentProfile
	Description		Class storing information about each instrument
  ==============================================================================
*/

#pragma once

#include "JuceIncludes.h"

#include "Parameters.h"
#include "nlohmann/json.hpp"
#include "Helper.h"


struct InstrumentRange
{
	InstrumentRange() = default;
	explicit InstrumentRange(const std::string &range) : range(range), transposition("") { setRanges(range); }

	explicit InstrumentRange(const std::string &range, const std::string &displayedRange) : range(range), displayedRange(displayedRange)
	{
		setRanges(range);
		setDisplayedRanges(displayedRange);
	}

	explicit InstrumentRange(const std::string &range, const std::string &displayedRange, const std::string &transposition)
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

	bool		operator==(const InstrumentRange &other) const { return this->range == other.range; }

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


	NLOHMANN_DEFINE_TYPE_INTRUSIVE(InstrumentRange, range, displayedRange, transposition)
};


struct SignatureWork
{
	SignatureWork() = default;
	explicit SignatureWork(const std::string &t) : work(t) {}

	std::string getWork() const { return work; }

private:
	std::string work;

	NLOHMANN_DEFINE_TYPE_INTRUSIVE(SignatureWork, work)
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


struct RegisterQuality
{
	RegisterQuality() = default;

	explicit RegisterQuality(const std::string &quality)
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

		higherNoteValue = turnNotenameIntoMidinumber(higherNote);
		lowerNoteValue	= turnNotenameIntoMidinumber(lowerNote);
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

	NLOHMANN_DEFINE_TYPE_INTRUSIVE(RegisterQuality, rangeNotation, description)
};


struct OrchestrationRole
{
	OrchestrationRole() = default;
	explicit OrchestrationRole(const std::string role) : role(role) {}

	std::string getRole() const { return role; }

private:
	std::string role;

	NLOHMANN_DEFINE_TYPE_INTRUSIVE(OrchestrationRole, role)
};


using RegisterQualities	 = std::vector<RegisterQuality>;
using PlayingTechniques	 = std::vector<PlayingTechnique>;
using OrchestrationRoles = std::vector<OrchestrationRole>;
using SignatureWorks	 = std::vector<SignatureWork>;


/*
 @brief             Struct defining an instrument and it's information
*/
struct InstrumentProfile
{
public:
	InstrumentProfile()	 = default;
	~InstrumentProfile() = default;

	InstrumentProfile(const std::string		   &name,
					  InstrumentID				key,
					  const InstrumentRange	   &range,
					  const RegisterQualities  &qualities,
					  const OrchestrationRoles &roles,
					  const SignatureWorks	   &works,
					  const PlayingTechniques  &techniques,
					  bool						isRhythmicPercussion = false)
		: mName(name), mRange(range), mQualities(qualities), mRoles(roles), mFamousWorks(works), mPlayingTechniques(techniques), mKey(key),
		  mIsRhythmicPercussion(isRhythmicPercussion)
	{
	}

	std::string		   getName() const { return mName; }
	InstrumentRange	   getRange() const { return mRange; }
	RegisterQualities  getQualities() const { return mQualities; }
	OrchestrationRoles getRoles() const { return mRoles; }
	SignatureWorks	   getFamousWorks() const { return mFamousWorks; }
	PlayingTechniques  getTechniques() const { return mPlayingTechniques; }
	InstrumentID	   getKey() const { return mKey; }
	bool			   isRhythmicPercussion() const { return mIsRhythmicPercussion; }

	bool			   isValid() { return !mName.empty() && mKey != 0; }

private:
	std::string		   mName;						  // Name of the instrument
	InstrumentRange	   mRange;						  // Range of notes (lowest to highest playable note)
	RegisterQualities  mQualities;					  // Sound characteristics of each section within the range
	OrchestrationRoles mRoles;						  // Any useful information of the instrument
	SignatureWorks	   mFamousWorks;				  // Famous works presenting the qualitiy of the instrument
	PlayingTechniques  mPlayingTechniques;			  // Different playing techniques featured within the instrument's family
	bool			   mIsRhythmicPercussion = false; // If the instrument is a rhythmic percussion instrument, it will be set to true

	InstrumentID	   mKey					 = 0;	  // 3 digit key defining the instrument (see Helper.h)

	NLOHMANN_DEFINE_TYPE_INTRUSIVE(InstrumentProfile, mName, mRange, mQualities, mRoles, mFamousWorks, mPlayingTechniques, mIsRhythmicPercussion, mKey)
};
