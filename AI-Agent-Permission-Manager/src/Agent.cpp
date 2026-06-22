#include "Agent.h"

Agent::Agent() : id(0), name(""), role(""), active(false) {}

Agent::Agent(int id, const std::string& name, const std::string& role, bool active)
    : id(id), name(name), role(role), active(active) {}

int Agent::getId() const {
    return id;
}

std::string Agent::getName() const {
    return name;
}

std::string Agent::getRole() const {
    return role;
}

bool Agent::isActive() const {
    return active;
}

void Agent::setName(const std::string& name) {
    this->name = name;
}

void Agent::setRole(const std::string& role) {
    this->role = role;
}

void Agent::setActive(bool active) {
    this->active = active;
}

