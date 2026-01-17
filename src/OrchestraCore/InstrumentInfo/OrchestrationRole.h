/*
  ==============================================================================
	Module			OrchestrationRole
	Description		Struct storing orchestration role information
  ==============================================================================
*/

#pragma once

#include "nlohmann/json.hpp"


struct OrchestrationRole
{
	OrchestrationRole() = default;
	explicit OrchestrationRole(const std::string role) : role(role) {}

	std::string getRole() const { return role; }

	bool		operator==(const OrchestrationRole &other) const { return this->role == other.role; }

	friend void from_json(const nlohmann::json &j, OrchestrationRole &r);
	friend void to_json(nlohmann::json &j, const OrchestrationRole &r);

private:
	std::string role{""};
};


inline void from_json(const nlohmann::json &j, OrchestrationRole &role)
{
	role.role = j.get<std::string>();
}

inline void to_json(nlohmann::json &j, const OrchestrationRole &role)
{
	j = role.getRole();
}