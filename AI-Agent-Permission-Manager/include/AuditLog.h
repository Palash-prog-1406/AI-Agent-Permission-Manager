#ifndef AUDIT_LOG_H
#define AUDIT_LOG_H

#include <string>

class AuditLog {
private:
    int logId;
    int agentId;
    int toolId;
    std::string resource;
    std::string decision;
    int riskScore;
    std::string timestamp;

public:
    AuditLog();
    AuditLog(int logId, int agentId, int toolId, const std::string& resource,
             const std::string& decision, int riskScore, const std::string& timestamp);

    int getLogId() const;
    int getAgentId() const;
    int getToolId() const;
    std::string getResource() const;
    std::string getDecision() const;
    int getRiskScore() const;
    std::string getTimestamp() const;
};

#endif

