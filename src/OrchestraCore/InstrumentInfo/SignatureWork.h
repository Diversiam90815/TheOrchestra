/*
  ==============================================================================
	Module			SignatureWork
	Description		Struct storing signature work information
  ==============================================================================
*/

#pragma once

#include "nlohmann/json.hpp"

constexpr auto SIG_WORK_COMPOSER = "composer";
constexpr auto SIG_WORK_TITLE	 = "title";


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
	work.composer = j[SIG_WORK_COMPOSER].get<std::string>();
	work.title	  = j[SIG_WORK_TITLE].get<std::string>();
}

inline void to_json(nlohmann::json &j, const SignatureWork &work)
{
	j[SIG_WORK_COMPOSER] = work.getComposer();
	j[SIG_WORK_TITLE]	 = work.getTitle();
}