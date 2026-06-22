#include "Tool.h"

Tool::Tool() : id(0), name(""), description(""), baseRisk(0) {}

Tool::Tool(int id, const std::string& name, const std::string& description, int baseRisk)
    : id(id), name(name), description(description), baseRisk(baseRisk) {}

int Tool::getId() const {
    return id;
}

std::string Tool::getName() const {
    return name;
}

std::string Tool::getDescription() const {
    return description;
}

int Tool::getBaseRisk() const {
    return baseRisk;
}

void Tool::setName(const std::string& name) {
    this->name = name;
}

void Tool::setDescription(const std::string& description) {
    this->description = description;
}

void Tool::setBaseRisk(int baseRisk) {
    this->baseRisk = baseRisk;
}

