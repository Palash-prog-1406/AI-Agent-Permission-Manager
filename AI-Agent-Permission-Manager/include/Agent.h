#ifndef AGENT_H
#define AGENT_H

#include <string>

class Agent {
private:
    int id;
    std::string name;
    std::string role;
    bool active;

public:
    Agent();
    Agent(int id, const std::string& name, const std::string& role, bool active);

    int getId() const;
    std::string getName() const;
    std::string getRole() const;
    bool isActive() const;

    void setName(const std::string& name);
    void setRole(const std::string& role);
    void setActive(bool active);
};

#endif

