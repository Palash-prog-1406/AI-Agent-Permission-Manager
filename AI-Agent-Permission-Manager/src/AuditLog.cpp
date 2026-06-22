#include "AuditLog.h"

AuditLog::AuditLog()
    : logId(0), agentId(0), toolId(0), resource(""), decision(""), riskScore(0), timestamp("") {}

AuditLog::AuditLog(int logId, int agentId, int toolId, const std::string& resource,
                   const std::string& decision, int riskScore, const std::string& timestamp)
    : logId(logId),
      agentId(agentId),
      toolId(toolId),
      resource(resource),
      decision(decision),
      riskScore(riskScore),
      timestamp(timestamp) {}

int AuditLog::getLogId() const {
    return logId;
}

int AuditLog::getAgentId() const {
    return agentId;
}

int AuditLog::getToolId() const {
    return toolId;
}

std::string AuditLog::getResource() const {
    return resource;
}

std::string AuditLog::getDecision() const {
    return decision;
}

int AuditLog::getRiskScore() const {
    return riskScore;
}

std::string AuditLog::getTimestamp() const {
    return timestamp;
}

