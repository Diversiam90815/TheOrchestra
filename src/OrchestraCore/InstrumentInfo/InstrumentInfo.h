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
#include "InstrumentRange.h"
#include "InstrumentRegister.h"
#include "PlayingTechnique.h"
#include "OrchestrationRole.h"
#include "SignatureWork.h"


using InstrumentRegisters = std::vector<InstrumentRegister>;
using PlayingTechniques	  = std::vector<PlayingTechnique>;
using OrchestrationRoles  = std::vector<OrchestrationRole>;
using SignatureWorks	  = std::vector<SignatureWork>;


/*
 @brief             Struct defining an instrument and it's information
*/
struct InstrumentProfile
{
public:
	InstrumentProfile()	 = default;
	~InstrumentProfile() = default;

	InstrumentProfile(const std::string			&name,
					  InstrumentID				 id,
					  const InstrumentRange		&range,
					  const InstrumentRegisters &registers,
					  const OrchestrationRoles	&roles,
					  const SignatureWorks		&works,
					  const PlayingTechniques	&techniques,
					  bool						 isRhythmicPercussion = false)
		: mName(name), mRange(range), mRegisters(registers), mRoles(roles), mFamousWorks(works), mPlayingTechniques(techniques), mID(id),
		  mIsRhythmicPercussion(isRhythmicPercussion)
	{
	}

	std::string			getName() const { return mName; }
	InstrumentRange		getRange() const { return mRange; }
	InstrumentRegisters getRegisters() const { return mRegisters; }
	OrchestrationRoles	getRoles() const { return mRoles; }
	SignatureWorks		getFamousWorks() const { return mFamousWorks; }
	PlayingTechniques	getTechniques() const { return mPlayingTechniques; }
	InstrumentID		getInstrumentID() const { return mID; }
	bool				isRhythmicPercussion() const { return mIsRhythmicPercussion; }

	bool				isValid() const { return !mName.empty() && mID != 0; }

	bool				operator==(const InstrumentProfile &other) const { return this->mID == other.mID; }

private:
	std::string			mName;						   // Name of the instrument
	InstrumentRange		mRange;						   // Range of notes (lowest to highest playable note)
	InstrumentRegisters mRegisters;					   // Sound characteristics of each section within the range
	OrchestrationRoles	mRoles;						   // Any useful information of the instrument
	SignatureWorks		mFamousWorks;				   // Famous works presenting the qualitiy of the instrument
	PlayingTechniques	mPlayingTechniques;			   // Different playing techniques featured within the instrument's family
	bool				mIsRhythmicPercussion = false; // If the instrument is a rhythmic percussion instrument, it will be set to true

	InstrumentID		mID					  = 0;	   // 3 digit key defining the instrument (see Helper.h)

	NLOHMANN_DEFINE_TYPE_INTRUSIVE(InstrumentProfile, mName, mRange, mRegisters, mRoles, mFamousWorks, mPlayingTechniques, mIsRhythmicPercussion, mID)
};
