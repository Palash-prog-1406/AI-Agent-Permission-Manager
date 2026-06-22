#include "PermissionManager.h"
#include "AuditLog.h"
#include <algorithm>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <limits>
#include <sstream>

PermissionManager::PermissionManager(const std::string& dataDirectory)
    : storage(dataDirectory), nextRequestId(1) {
    policies.push_back(std::make_unique<StatusPolicy>());
    policies.push_back(std::make_unique<RoleBasedPolicy>());
    policies.push_back(std::make_unique<RiskBasedPolicy>());
}

void PermissionManager::loadData() {
    storage.initializeFiles();
    agents = storage.loadAgents();
    tools = storage.loadTools();
    permissions = storage.loadPermissions();
    seedDefaultDataIfEmpty();
}

void PermissionManager::seedDefaultDataIfEmpty() {
    if (agents.empty()) {
        agents.push_back(Agent(1, "ResearchBot", "RESEARCH_AGENT", true));
        agents.push_back(Agent(2, "EmailBot", "EMAIL_AGENT", true));
        agents.push_back(Agent(3, "DataBot", "DATA_AGENT", true));
        agents.push_back(Agent(4, "OldBot", "DATA_AGENT", false));
        storage.saveAgents(agents);
    }

    if (tools.empty()) {
        tools.push_back(Tool(1, "read_file", "Read internal files", 20));
        tools.push_back(Tool(2, "generate_report", "Generate summary reports", 30));
        tools.push_back(Tool(3, "send_email", "Send email to users", 50));
        tools.push_back(Tool(4, "update_database", "Modify database records", 70));
        tools.push_back(Tool(5, "delete_record", "Delete database records", 90));
        storage.saveTools(tools);
    }

    if (permissions.empty()) {
        permissions.push_back(Permission("RESEARCH_AGENT", "read_file", true));
        permissions.push_back(Permission("RESEARCH_AGENT", "generate_report", true));
        permissions.push_back(Permission("RESEARCH_AGENT", "send_email", false));
        permissions.push_back(Permission("EMAIL_AGENT", "send_email", true));
        permissions.push_back(Permission("EMAIL_AGENT", "read_file", false));
        permissions.push_back(Permission("DATA_AGENT", "read_file", true));
        permissions.push_back(Permission("DATA_AGENT", "update_database", true));
        permissions.push_back(Permission("DATA_AGENT", "delete_record", false));
        storage.savePermissions(permissions);
    }
}

Agent* PermissionManager::findAgentById(int id) {
    for (Agent& agent : agents) {
        if (agent.getId() == id) {
            return &agent;
        }
    }
    return nullptr;
}

Tool* PermissionManager::findToolById(int id) {
    for (Tool& tool : tools) {
        if (tool.getId() == id) {
            return &tool;
        }
    }
    return nullptr;
}

int PermissionManager::nextAgentId() const {
    int highest = 0;
    for (const Agent& agent : agents) {
        highest = std::max(highest, agent.getId());
    }
    return highest + 1;
}

int PermissionManager::nextToolId() const {
    int highest = 0;
    for (const Tool& tool : tools) {
        highest = std::max(highest, tool.getId());
    }
    return highest + 1;
}

int PermissionManager::nextLogId() const {
    std::vector<AuditLog> logs = storage.loadAuditLogs();
    int highest = 0;
    for (const AuditLog& log : logs) {
        highest = std::max(highest, log.getLogId());
    }
    return highest + 1;
}

std::string PermissionManager::currentTimestamp() const {
    auto now = std::chrono::system_clock::now();
    std::time_t currentTime = std::chrono::system_clock::to_time_t(now);
    std::tm localTime{};

#ifdef _WIN32
    localtime_s(&localTime, &currentTime);
#else
    localtime_r(&currentTime, &localTime);
#endif

    std::ostringstream stream;
    stream << std::put_time(&localTime, "%Y-%m-%d %H:%M:%S");
    return stream.str();
}

void PermissionManager::addAgent() {
    std::string name;
    std::string role;
    int activeInput;

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Enter agent name: ";
    std::getline(std::cin, name);

    std::cout << "Enter role, example RESEARCH_AGENT / EMAIL_AGENT / DATA_AGENT: ";
    std::getline(std::cin, role);

    std::cout << "Is active? 1 for yes, 0 for no: ";
    std::cin >> activeInput;

    agents.push_back(Agent(nextAgentId(), name, role, activeInput == 1));
    storage.saveAgents(agents);

    std::cout << "Agent added successfully.\n";
}

void PermissionManager::addTool() {
    std::string name;
    std::string description;
    int baseRisk;

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Enter tool name, example read_file: ";
    std::getline(std::cin, name);

    std::cout << "Enter description: ";
    std::getline(std::cin, description);

    std::cout << "Enter base risk score from 0 to 100: ";
    std::cin >> baseRisk;

    tools.push_back(Tool(nextToolId(), name, description, baseRisk));
    storage.saveTools(tools);

    std::cout << "Tool added successfully.\n";
}

void PermissionManager::assignPermission() {
    std::string role;
    std::string toolName;
    int allowedInput;

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Enter role: ";
    std::getline(std::cin, role);

    std::cout << "Enter tool name: ";
    std::getline(std::cin, toolName);

    std::cout << "Allowed? 1 for yes, 0 for no: ";
    std::cin >> allowedInput;

    permissions.push_back(Permission(role, toolName, allowedInput == 1));
    storage.savePermissions(permissions);

    std::cout << "Permission assigned successfully.\n";
}

void PermissionManager::requestAccess() {
    int agentId;
    int toolId;
    std::string resource;
    std::string purpose;

    viewAgents();
    std::cout << "Enter agent ID: ";
    std::cin >> agentId;

    viewTools();
    std::cout << "Enter tool ID: ";
    std::cin >> toolId;

    Agent* agent = findAgentById(agentId);
    Tool* tool = findToolById(toolId);

    if (agent == nullptr || tool == nullptr) {
        std::cout << "Invalid agent or tool ID.\n";
        return;
    }

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Enter resource, example customer_database or market_report.pdf: ";
    std::getline(std::cin, resource);

    std::cout << "Enter purpose: ";
    std::getline(std::cin, purpose);

    AccessRequest request(nextRequestId++, agentId, toolId, resource, purpose);
    AccessDecision finalDecision(DecisionType::ALLOW, "All policies passed", 0);

    for (const std::unique_ptr<Policy>& policy : policies) {
        AccessDecision decision = policy->evaluate(request, *agent, *tool, permissions, riskAnalyzer);

        if (decision.getDecision() == DecisionType::DENY) {
            finalDecision = AccessDecision(DecisionType::DENY,
                                           policy->getPolicyName() + ": " + decision.getReason(),
                                           decision.getRiskScore());
            break;
        }

        if (decision.getDecision() == DecisionType::REVIEW_REQUIRED) {
            finalDecision = AccessDecision(DecisionType::REVIEW_REQUIRED,
                                           policy->getPolicyName() + ": " + decision.getReason(),
                                           decision.getRiskScore());
        } else if (finalDecision.getDecision() == DecisionType::ALLOW) {
            finalDecision = AccessDecision(DecisionType::ALLOW,
                                           policy->getPolicyName() + ": " + decision.getReason(),
                                           decision.getRiskScore());
        }
    }

    AuditLog log(nextLogId(), agentId, toolId, resource,
                 decisionToString(finalDecision.getDecision()),
                 finalDecision.getRiskScore(), currentTimestamp());

    storage.appendAuditLog(log);

    if (finalDecision.getDecision() == DecisionType::REVIEW_REQUIRED) {
        storage.appendPendingReview(request.getRequestId(), agentId, toolId, resource,
                                    finalDecision.getRiskScore(), "PENDING");
    }

    std::cout << "\n--- Access Decision ---\n";
    std::cout << "Agent: " << agent->getName() << "\n";
    std::cout << "Tool: " << tool->getName() << "\n";
    std::cout << "Resource: " << resource << "\n";
    std::cout << "Risk Score: " << finalDecision.getRiskScore()
              << " (" << riskAnalyzer.riskLevel(finalDecision.getRiskScore()) << ")\n";
    std::cout << "Decision: " << decisionToString(finalDecision.getDecision()) << "\n";
    std::cout << "Reason: " << finalDecision.getReason() << "\n";
}

void PermissionManager::viewAgents() const {
    std::cout << "\n--- Agents ---\n";
    for (const Agent& agent : agents) {
        std::cout << "ID: " << agent.getId()
                  << " | Name: " << agent.getName()
                  << " | Role: " << agent.getRole()
                  << " | Active: " << (agent.isActive() ? "Yes" : "No") << "\n";
    }
}

void PermissionManager::viewTools() const {
    std::cout << "\n--- Tools ---\n";
    for (const Tool& tool : tools) {
        std::cout << "ID: " << tool.getId()
                  << " | Name: " << tool.getName()
                  << " | Risk: " << tool.getBaseRisk()
                  << " | Description: " << tool.getDescription() << "\n";
    }
}

void PermissionManager::viewPermissions() const {
    std::cout << "\n--- Permissions ---\n";
    for (const Permission& permission : permissions) {
        std::cout << "Role: " << permission.getRole()
                  << " | Tool: " << permission.getToolName()
                  << " | Allowed: " << (permission.isAllowed() ? "Yes" : "No") << "\n";
    }
}

void PermissionManager::viewAuditLogs() const {
    std::vector<AuditLog> logs = storage.loadAuditLogs();
    std::cout << "\n--- Audit Logs ---\n";

    if (logs.empty()) {
        std::cout << "No audit logs yet.\n";
        return;
    }

    for (const AuditLog& log : logs) {
        std::cout << "Log ID: " << log.getLogId()
                  << " | Agent ID: " << log.getAgentId()
                  << " | Tool ID: " << log.getToolId()
                  << " | Resource: " << log.getResource()
                  << " | Decision: " << log.getDecision()
                  << " | Risk: " << log.getRiskScore()
                  << " | Time: " << log.getTimestamp() << "\n";
    }
}

void PermissionManager::viewPendingReviews() const {
    storage.showPendingReviews();
}

void PermissionManager::reviewPendingRequest() {
    int requestId;
    int choice;

    storage.showPendingReviews();
    std::cout << "Enter request ID to review: ";
    std::cin >> requestId;

    std::cout << "1. Approve\n";
    std::cout << "2. Reject\n";
    std::cout << "Enter choice: ";
    std::cin >> choice;

    if (choice == 1) {
        storage.updatePendingReviewStatus(requestId, "APPROVED");
        std::cout << "Request approved.\n";
    } else if (choice == 2) {
        storage.updatePendingReviewStatus(requestId, "REJECTED");
        std::cout << "Request rejected.\n";
    } else {
        std::cout << "Invalid choice.\n";
    }
}

