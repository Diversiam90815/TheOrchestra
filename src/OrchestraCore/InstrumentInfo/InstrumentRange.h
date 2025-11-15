/*
  ==============================================================================
	Module			InstrumentRange
	Description		Struct storing range information for instruments
  ==============================================================================
*/

#pragma once

#include "Helper.h"
#include "nlohmann/json.hpp"


struct InstrumentRange
{
	InstrumentRange() = default;

	std::string getHigherRange() const { return higherRange; }
	std::string getLowerRange() const { return lowerRange; }
	const int	getHigherRangeNoteValue() const { return higherNoteRange; }
	const int	getLowerRangeNoteValue() const { return lowerNoteRange; }

	std::string getDisplayedHigherRange() const { return higherDisplay; }
	std::string getDisplayedLowerRange() const { return lowerDisplay; }
	const int	getDisplayedHigherRangeNoteValue() const { return higherDisplayedRange; }
	const int	getDisplayedLowerRangeNoteValue() const { return lowerDisplayedRange; }

	std::string getTransposition() const { return transposition; }

	bool		operator==(const InstrumentRange &other) const { return this->lowerRange == other.lowerRange && this->higherRange == other.higherRange; }

	friend void from_json(const nlohmann::json &j, InstrumentRange &range);
	friend void to_json(nlohmann::json &j, const InstrumentRange &range);

private:
	std::string higherRange{""};
	std::string lowerRange{""};
	int			higherNoteRange{0};
	int			lowerNoteRange{0};

	std::string higherDisplay{""};
	std::string lowerDisplay{""};
	int			higherDisplayedRange{0};
	int			lowerDisplayedRange{0};

	std::string transposition{""};
};


inline void from_json(const nlohmann::json &j, InstrumentRange &range)
{
	// Parse written range (required)
	if (j.contains("written"))
	{
		const auto &written	  = j["written"];
		range.lowerRange	  = written["low"].get<std::string>();
		range.higherRange	  = written["high"].get<std::string>();
		range.lowerNoteRange  = turnNotenameIntoMidinumber(range.lowerRange);
		range.higherNoteRange = turnNotenameIntoMidinumber(range.higherRange);
	}

	// Parse displayed range (optional, for rhythmic percussion)
	if (j.contains("displayed"))
	{
		const auto &displayed	   = j["displayed"];
		range.lowerDisplay		   = displayed["low"].get<std::string>();
		range.higherDisplay		   = displayed["high"].get<std::string>();
		range.lowerDisplayedRange  = turnNotenameIntoMidinumber(range.lowerDisplay);
		range.higherDisplayedRange = turnNotenameIntoMidinumber(range.higherDisplay);
	}
	else
	{
		// Default to written range
		range.lowerDisplay		   = range.lowerRange;
		range.higherDisplay		   = range.higherRange;
		range.lowerDisplayedRange  = range.lowerNoteRange;
		range.higherDisplayedRange = range.higherNoteRange;
	}

	// Parse transposition (optional)
	if (j.contains("transposition"))
	{
		range.transposition = j["transposition"].get<std::string>();
	}
}

inline void to_json(nlohmann::json &j, const InstrumentRange &range)
{
	j["written"]["low"]	 = range.getLowerRange();
	j["written"]["high"] = range.getHigherRange();

	if (!range.getTransposition().empty())
	{
		j["transposition"] = range.getTransposition();
	}

	// Only add displayed if different from written
	if (range.getDisplayedLowerRange() != range.getLowerRange() || range.getDisplayedHigherRange() != range.getHigherRange())
	{
		j["displayed"]["low"]  = range.getDisplayedLowerRange();
		j["displayed"]["high"] = range.getDisplayedHigherRange();
	}
}