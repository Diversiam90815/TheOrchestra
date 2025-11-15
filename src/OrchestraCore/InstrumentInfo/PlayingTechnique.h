/*
  ==============================================================================
	Module			PlayingTechnique
	Description		Struct storing playing technique information
  ==============================================================================
*/


#pragma once

#include "nlohmann/json.hpp"


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
	technique.name		  = j["name"].get<std::string>();
	technique.description = j["description"].get<std::string>();
}

inline void to_json(nlohmann::json &j, const PlayingTechnique &technique)
{
	j["name"]		 = technique.getName();
	j["description"] = technique.getDescription();
}