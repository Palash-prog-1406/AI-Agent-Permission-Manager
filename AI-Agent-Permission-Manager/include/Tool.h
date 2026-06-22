#ifndef TOOL_H
#define TOOL_H

#include <string>

class Tool {
private:
    int id;
    std::string name;
    std::string description;
    int baseRisk;

public:
    Tool();
    Tool(int id, const std::string& name, const std::string& description, int baseRisk);

    int getId() const;
    std::string getName() const;
    std::string getDescription() const;
    int getBaseRisk() const;

    void setName(const std::string& name);
    void setDescription(const std::string& description);
    void setBaseRisk(int baseRisk);
};

#endif

