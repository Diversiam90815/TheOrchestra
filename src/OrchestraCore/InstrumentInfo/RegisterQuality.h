/*
  ==============================================================================
	Module			RegisterQuality
	Description		Struct storing register quality information
  ==============================================================================
*/

#pragma once

#include "nlohmann/json.hpp"
#include "Helper.h"


struct RegisterQuality
{
	RegisterQuality() = default;

	std::string getLowerRange() const { return lowerNote; }
	std::string getHigherRange() const { return higherNote; }
	int			getHigherNoteValue() const { return higherNoteValue; }
	int			getLowerNoteValue() const { return lowerNoteValue; }
	std::string getDescription() const { return description; }

	bool		operator==(const RegisterQuality &other) const
	{
		return this->lowerNote == other.lowerNote && this->higherNote == other.higherNote && this->description == other.description;
	}

	friend void from_json(const nlohmann::json &j, RegisterQuality &quality);
	friend void to_json(nlohmann::json &j, const RegisterQuality &quality);

private:
	std::string higherNote{""};
	std::string lowerNote{""};
	int			higherNoteValue{0};
	int			lowerNoteValue{0};
	std::string description{""};
};

inline void from_json(const nlohmann::json &j, RegisterQuality &quality)
{
	const auto &range		= j["range"];
	quality.lowerNote		= range["low"].get<std::string>();
	quality.higherNote		= range["high"].get<std::string>();
	quality.lowerNoteValue	= turnNotenameIntoMidinumber(quality.lowerNote);
	quality.higherNoteValue = turnNotenameIntoMidinumber(quality.higherNote);
	quality.description		= j["description"].get<std::string>();
}

inline void to_json(nlohmann::json &j, const RegisterQuality &quality)
{
	j["range"]["low"]  = quality.getLowerRange();
	j["range"]["high"] = quality.getHigherRange();
	j["description"]   = quality.getDescription();
}