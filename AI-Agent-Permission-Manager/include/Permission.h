#ifndef PERMISSION_H
#define PERMISSION_H

#include <string>

class Permission {
private:
    std::string role;
    std::string toolName;
    bool allowed;

public:
    Permission();
    Permission(const std::string& role, const std::string& toolName, bool allowed);

    std::string getRole() const;
    std::string getToolName() const;
    bool isAllowed() const;
};

#endif

