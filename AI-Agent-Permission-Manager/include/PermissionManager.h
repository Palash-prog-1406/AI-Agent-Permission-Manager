#ifndef PERMISSION_MANAGER_H
#define PERMISSION_MANAGER_H

#include "AccessRequest.h"
#include "Agent.h"
#include "FileStorage.h"
#include "Permission.h"
#include "Policy.h"
#include "RiskAnalyzer.h"
#include "Tool.h"
#include <memory>
#include <vector>

class PermissionManager {
private:
    std::vector<Agent> agents;
    std::vector<Tool> tools;
    std::vector<Permission> permissions;
    std::vector<std::unique_ptr<Policy>> policies;
    RiskAnalyzer riskAnalyzer;
    FileStorage storage;
    int nextRequestId;

    Agent* findAgentById(int id);
    Tool* findToolById(int id);
    int nextAgentId() const;
    int nextToolId() const;
    int nextLogId() const;
    std::string currentTimestamp() const;

public:
    explicit PermissionManager(const std::string& dataDirectory);

    void loadData();
    void seedDefaultDataIfEmpty();

    void addAgent();
    void addTool();
    void assignPermission();
    void requestAccess();
    void viewAgents() const;
    void viewTools() const;
    void viewPermissions() const;
    void viewAuditLogs() const;
    void viewPendingReviews() const;
    void reviewPendingRequest();
};

#endif

