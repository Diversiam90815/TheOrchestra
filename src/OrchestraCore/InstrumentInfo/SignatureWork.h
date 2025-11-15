/*
  ==============================================================================
	Module			SignatureWork
	Description		Struct storing signature work information
  ==============================================================================
*/

#pragma once

#include "nlohmann/json.hpp"


struct SignatureWork
{
	SignatureWork() = default;

	std::string getComposer() const { return composer; }
	std::string getTitle() const { return title; }
	std::string getWork() const { return composer + " - " + title; }

	bool		operator==(const SignatureWork &other) const { return this->composer == other.composer && this->title == other.title; }

	friend void from_json(const nlohmann::json &j, SignatureWork &work);
	friend void to_json(nlohmann::json &j, const SignatureWork &work);

private:
	std::string composer{""};
	std::string title{""};
};


inline void from_json(const nlohmann::json &j, SignatureWork &work)
{
	work.composer = j["composer"].get<std::string>();
	work.title	  = j["title"].get<std::string>();
}

inline void to_json(nlohmann::json &j, const SignatureWork &work)
{
	j["composer"] = work.getComposer();
	j["title"]	  = work.getTitle();
}