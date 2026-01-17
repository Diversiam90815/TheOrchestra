/*
  ==============================================================================
	Module			InstrumentRegister
	Description		Struct storing register quality information
  ==============================================================================
*/

#pragma once

#include "nlohmann/json.hpp"
#include "Helper.h"

constexpr auto REG_QUAL_RANGE	   = "range";
constexpr auto REG_QUAL_RANGE_LOW  = "low";
constexpr auto REG_QUAL_RANGE_HIGH = "high";
constexpr auto REG_QUAL_DESC	   = "description";


struct InstrumentRegister
{
	InstrumentRegister() = default;

	std::string getLowerRange() const { return lowerNote; }
	std::string getHigherRange() const { return higherNote; }
	int			getHigherNoteValue() const { return higherNoteValue; }
	int			getLowerNoteValue() const { return lowerNoteValue; }
	std::string getDescription() const { return description; }

	bool		operator==(const InstrumentRegister &other) const
	{
		return this->lowerNote == other.lowerNote && this->higherNote == other.higherNote && this->description == other.description;
	}

	friend void from_json(const nlohmann::json &j, InstrumentRegister &quality);
	friend void to_json(nlohmann::json &j, const InstrumentRegister &quality);

private:
	std::string higherNote{""};
	std::string lowerNote{""};
	int			higherNoteValue{0};
	int			lowerNoteValue{0};
	std::string description{""};
};


inline void from_json(const nlohmann::json &j, InstrumentRegister &quality)
{
	const auto &range		= j[REG_QUAL_RANGE];
	quality.lowerNote		= range[REG_QUAL_RANGE_LOW].get<std::string>();
	quality.higherNote		= range[REG_QUAL_RANGE_HIGH].get<std::string>();
	quality.lowerNoteValue	= turnNotenameIntoMidinumber(quality.lowerNote);
	quality.higherNoteValue = turnNotenameIntoMidinumber(quality.higherNote);
	quality.description		= j[REG_QUAL_DESC].get<std::string>();
}

inline void to_json(nlohmann::json &j, const InstrumentRegister &quality)
{
	j[REG_QUAL_RANGE][REG_QUAL_RANGE_LOW]  = quality.getLowerRange();
	j[REG_QUAL_RANGE][REG_QUAL_RANGE_HIGH] = quality.getHigherRange();
	j[REG_QUAL_DESC]					   = quality.getDescription();
}