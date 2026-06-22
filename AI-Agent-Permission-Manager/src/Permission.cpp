#include "Permission.h"

Permission::Permission() : role(""), toolName(""), allowed(false) {}

Permission::Permission(const std::string& role, const std::string& toolName, bool allowed)
    : role(role), toolName(toolName), allowed(allowed) {}

std::string Permission::getRole() const {
    return role;
}

std::string Permission::getToolName() const {
    return toolName;
}

bool Permission::isAllowed() const {
    return allowed;
}

