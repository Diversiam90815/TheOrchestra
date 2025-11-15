/*
  ==============================================================================
	Module			PlayingTechnique
	Description		Struct storing playing technique information
  ==============================================================================
*/

#pragma once

#include "nlohmann/json.hpp"

constexpr auto TECHNIQUE_NAME = "name";
constexpr auto TECHNIQUE_DESC = "description";


struct PlayingTechnique
{
	PlayingTechnique() = default;

	std::string getName() const { return name; }
	std::string getDescription() const { return description; }

	bool		operator==(const PlayingTechnique &other) const { return this->name == other.name && this->description == other.description; }

	friend void from_json(const nlohmann::json &j, PlayingTechnique &technique);
	friend void to_json(nlohmann::json &j, const PlayingTechnique &technique);

private:
	std::string name{""};
	std::string description{""};
};


inline void from_json(const nlohmann::json &j, PlayingTechnique &technique)
{
	technique.name		  = j[TECHNIQUE_NAME].get<std::string>();
	technique.description = j[TECHNIQUE_DESC].get<std::string>();
}

inline void to_json(nlohmann::json &j, const PlayingTechnique &technique)
{
	j[TECHNIQUE_NAME] = technique.getName();
	j[TECHNIQUE_DESC] = technique.getDescription();
}