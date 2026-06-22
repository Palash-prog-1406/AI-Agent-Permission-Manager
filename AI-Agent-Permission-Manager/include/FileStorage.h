#ifndef FILE_STORAGE_H
#define FILE_STORAGE_H

#include "Agent.h"
#include "AuditLog.h"
#include "Permission.h"
#include "Tool.h"
#include <string>
#include <vector>

class FileStorage {
private:
    std::string dataDirectory;

    std::vector<std::string> split(const std::string& line, char delimiter) const;
    bool fileExists(const std::string& path) const;
    void createFileWithHeader(const std::string& path, const std::string& header) const;

public:
    explicit FileStorage(const std::string& dataDirectory);

    void initializeFiles() const;

    std::vector<Agent> loadAgents() const;
    std::vector<Tool> loadTools() const;
    std::vector<Permission> loadPermissions() const;
    std::vector<AuditLog> loadAuditLogs() const;

    void saveAgents(const std::vector<Agent>& agents) const;
    void saveTools(const std::vector<Tool>& tools) const;
    void savePermissions(const std::vector<Permission>& permissions) const;
    void appendAuditLog(const AuditLog& log) const;

    void appendPendingReview(int requestId, int agentId, int toolId,
                             const std::string& resource, int riskScore,
                             const std::string& status) const;

    void showPendingReviews() const;
    void updatePendingReviewStatus(int requestId, const std::string& status) const;
};

#endif

