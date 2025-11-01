/*
  ==============================================================================
	Module			InstrumentInfo
	Description		Class storing information about each instrument
  ==============================================================================
*/

#pragma once

#include "JuceIncludes.h"

#include "Parameters.h"


struct Range
{
	Range() = default;
	explicit Range(const std::string &range) : range(range), transposition("") {}
	explicit Range(const std::string &range, const std::string displayedRange) : range(range), displayedRange(displayedRange) {}
	explicit Range(const std::string &range, const std::string displayedRange, const std::string &transposition)
		: range(range), displayedRange(displayedRange), transposition(transposition)
	{
	}

	std::string getHigherRange() const { return range; } // TODO: split
	std::string getLowerRange() const { return range; }	 // TODO: split
	std::string getDisplayRange() const { return displayedRange; }
	std::string getTransposition() const { return transposition; }

private:
	std::string range;
	std::string displayedRange; // The range that is displayed if it differs from the actual range such as for rhythmic percussion
	std::string transposition;
};


struct FamousWork
{
	FamousWork() = default;
	explicit FamousWork(const std::string &t) : work(t) {}

	std::string getWork() const { return work; }

private:
	std::string work;
};


struct PlayingTechnique
{
	PlayingTechnique() = default;
	explicit PlayingTechnique(const std::string &technique)
	{
		int colonPos = technique.find(":");
		if (colonPos == std::string::npos)
		{
			name = technique;
			return;
		}
		name		= technique.substr(0, colonPos);
		description = technique.substr(colonPos + 1);
	}

	std::string getName() const { return name; }
	std::string getDescription() const { return description; }

	//		String		left  = splitColonizedStrings(tech, true);
	//String		right = splitColonizedStrings(tech, false);

private:
	std::string name;
	std::string description;
};


struct Quality
{
	Quality() = default;

	explicit Quality(const std::string &quality)
	{
		int colonPos = quality.find(":");
		if (colonPos > 0)
		{
			rangeNotation = quality.substr(0, colonPos);
			description	  = quality.substr(colonPos + 1);
		}
	}

	std::string getLowerRange() const { return rangeNotation; }	 // TODO: split
	std::string getHigherRange() const { return rangeNotation; } // TODO: split
	std::string getDescription() const { return description; }

	//		if (range.contains("-"))									 // Ranges are divided with a '-'
	//{
	//	lowerNote  = getLowerOrHigherNote(range, true);
	//	higherNote = getLowerOrHigherNote(range, false);
	//}
	//else
	//{
	//	// Single note case: Use the single note as both lower and higher note
	//	lowerNote  = range.trim();
	//	higherNote = range.trim();
	//}

private:
	std::string rangeNotation;
	std::string description;
};


struct Role
{
	Role() = default;
	explicit Role(const std::string role) : role(role) {}

	std::string getRole() const { return role; }

private:
	std::string role;
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
				   const Range		 &range,
				   const Qualities	 &qualities,
				   const Roles		 &roles,
				   const FamousWorks &works,
				   const Techniques	 &techniques,
				   InstrumentID		  key,
				   bool				  isRhythmicPercussion = false,
				   std::string		  displayedRange	   = std::string(""))
		: mName(name), mRange(range), mQualities(qualities), mUsefulInformation(roles), mFamousWorks(works), mPlayingTechniques(techniques), mKey(key),
		  mIsRhythmicPercussion(isRhythmicPercussion)
	{
	}

	std::string	 getName() const { return mName; }
	Range		 getRange() const { return mRange; }
	Qualities	 getQualities() const { return mQualities; }
	Roles		 getRoles() const { return mUsefulInformation; }
	FamousWorks	 getFamousWorks() const { return mFamousWorks; }
	Techniques	 getTechniques() const { return mPlayingTechniques; }
	InstrumentID getKey() const { return mKey; }
	bool		 isRhythmicPercussion() const { return mIsRhythmicPercussion; }

	bool		 isValid() { return !mName.empty() && mKey != 0; }

private:
	std::string	 mName;							// Name of the instrument
	Range		 mRange;						// Range of notes (lowest to highest playable note)
	Qualities	 mQualities;					// Sound characteristics of each section within the range
	Roles		 mUsefulInformation;			// Any useful information of the instrument
	FamousWorks	 mFamousWorks;					// Famous works presenting the qualitiy of the instrument
	Techniques	 mPlayingTechniques;			// Different playing techniques featured within the instrument's family
	bool		 mIsRhythmicPercussion = false; // If the instrument is a rhythmic percussion instrument, it will be set to true

	InstrumentID mKey				   = 0;		// 3 digit key defining the instrument (see Helper.h)

	friend class InstrumentController;
	friend class InstrumentInfoView;
};
