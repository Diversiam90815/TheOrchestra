/*
  ==============================================================================
	Module			InstrumentRange
	Description		Struct storing range information for instruments
  ==============================================================================
*/

#pragma once

#include "Helper.h"
#include "nlohmann/json.hpp"

constexpr auto RANGE_WRITTEN   = "written";
constexpr auto RANGE_DISPLAYED = "displayed";
constexpr auto RANGE_SOUNDING  = "sounding";
constexpr auto RANGE_LOW	   = "low";
constexpr auto RANGE_HIGH	   = "high";


struct InstrumentRange
{
	InstrumentRange() = default;

	const std::string &getWrittenHighNote() const { return writtenHigh; }
	const std::string &getWrittenLowNote() const { return writtenLow; }
	int				   getWrittenHighNoteAsMidiValue() const { return writtenHighNoteValue; }
	int				   getWrittenLowNoteAsMidiValue() const { return writtenLowNoteValue; }

	const std::string &getSoundingHighNote() const { return soundingHigh; }
	const std::string &getSoundingLowNote() const { return soundingLow; }
	int				   getSoundingHighNoteAsMidiValue() const { return soundingHighNoteValue; }
	int				   getSoundingLowNoteAsMidiValue() const { return soundingLowNoteValue; }

	bool			   operator==(const InstrumentRange &other) const { return this->writtenLow == other.writtenLow && this->writtenHigh == other.writtenHigh; }

	friend void		   from_json(const nlohmann::json &j, InstrumentRange &range);
	friend void		   to_json(nlohmann::json &j, const InstrumentRange &range);

private:
	std::string writtenHigh{""};
	std::string writtenLow{""};
	int			writtenHighNoteValue{0};
	int			writtenLowNoteValue{0};

	std::string soundingHigh{""};
	std::string soundingLow{""};
	int			soundingHighNoteValue{0};
	int			soundingLowNoteValue{0};
};


inline void from_json(const nlohmann::json &j, InstrumentRange &range)
{
	// Parse written range (required)
	if (j.contains(RANGE_WRITTEN))
	{
		const auto &written		   = j[RANGE_WRITTEN];
		range.writtenLow		   = written[RANGE_LOW].get<std::string>();
		range.writtenHigh		   = written[RANGE_HIGH].get<std::string>();
		range.writtenLowNoteValue  = turnNotenameIntoMidinumber(range.writtenLow);
		range.writtenHighNoteValue = turnNotenameIntoMidinumber(range.writtenHigh);
	}

	// Parse sounding/displayed range (optional - used for transposing instruments and rhythmic percussion)
	// JSON data may use either "sounding" or "displayed" as the key
	const char *soundingKey = nullptr;
	if (j.contains(RANGE_SOUNDING))
		soundingKey = RANGE_SOUNDING;
	else if (j.contains(RANGE_DISPLAYED))
		soundingKey = RANGE_DISPLAYED;

	if (soundingKey != nullptr)
	{
		const auto &sounding		= j[soundingKey];
		range.soundingLow			= sounding[RANGE_LOW].get<std::string>();
		range.soundingHigh			= sounding[RANGE_HIGH].get<std::string>();
		range.soundingLowNoteValue	= turnNotenameIntoMidinumber(range.soundingLow);
		range.soundingHighNoteValue = turnNotenameIntoMidinumber(range.soundingHigh);
	}
	else
	{
		// Default to written range (non-transposing instruments)
		range.soundingLow			= range.writtenLow;
		range.soundingHigh			= range.writtenHigh;
		range.soundingLowNoteValue	= range.writtenLowNoteValue;
		range.soundingHighNoteValue = range.writtenHighNoteValue;
	}
}

inline void to_json(nlohmann::json &j, const InstrumentRange &range)
{
	j[RANGE_WRITTEN][RANGE_LOW]	 = range.getWrittenLowNote();
	j[RANGE_WRITTEN][RANGE_HIGH] = range.getWrittenHighNote();

	// Only add displayed if different from written
	if (range.getSoundingLowNote() != range.getWrittenLowNote() || range.getSoundingHighNote() != range.getWrittenHighNote())
	{
		j[RANGE_DISPLAYED][RANGE_LOW]  = range.getSoundingLowNote();
		j[RANGE_DISPLAYED][RANGE_HIGH] = range.getSoundingHighNote();
	}
}