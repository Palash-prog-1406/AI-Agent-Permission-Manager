#include "FileStorage.h"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>

FileStorage::FileStorage(const std::string& dataDirectory) : dataDirectory(dataDirectory) {}

std::vector<std::string> FileStorage::split(const std::string& line, char delimiter) const {
    std::vector<std::string> parts;
    std::stringstream stream(line);
    std::string item;

    while (std::getline(stream, item, delimiter)) {
        parts.push_back(item);
    }

    return parts;
}

bool FileStorage::fileExists(const std::string& path) const {
    std::ifstream file(path);
    return file.good();
}

void FileStorage::createFileWithHeader(const std::string& path, const std::string& header) const {
    if (!fileExists(path)) {
        std::ofstream file(path);
        file << header << "\n";
    }
}

void FileStorage::initializeFiles() const {
    std::filesystem::create_directories(dataDirectory);

    createFileWithHeader(dataDirectory + "/agents.csv", "id,name,role,active");
    createFileWithHeader(dataDirectory + "/tools.csv", "id,name,description,baseRisk");
    createFileWithHeader(dataDirectory + "/permissions.csv", "role,toolName,allowed");
    createFileWithHeader(dataDirectory + "/audit_logs.csv", "logId,agentId,toolId,resource,decision,riskScore,timestamp");
    createFileWithHeader(dataDirectory + "/pending_reviews.csv", "requestId,agentId,toolId,resource,riskScore,status");
}

std::vector<Agent> FileStorage::loadAgents() const {
    std::vector<Agent> agents;
    std::ifstream file(dataDirectory + "/agents.csv");
    std::string line;
    bool header = true;

    while (std::getline(file, line)) {
        if (header) {
            header = false;
            continue;
        }

        std::vector<std::string> parts = split(line, ',');
        if (parts.size() == 4) {
            agents.emplace_back(std::stoi(parts[0]), parts[1], parts[2], parts[3] == "1");
        }
    }

    return agents;
}

std::vector<Tool> FileStorage::loadTools() const {
    std::vector<Tool> tools;
    std::ifstream file(dataDirectory + "/tools.csv");
    std::string line;
    bool header = true;

    while (std::getline(file, line)) {
        if (header) {
            header = false;
            continue;
        }

        std::vector<std::string> parts = split(line, ',');
        if (parts.size() == 4) {
            tools.emplace_back(std::stoi(parts[0]), parts[1], parts[2], std::stoi(parts[3]));
        }
    }

    return tools;
}

std::vector<Permission> FileStorage::loadPermissions() const {
    std::vector<Permission> permissions;
    std::ifstream file(dataDirectory + "/permissions.csv");
    std::string line;
    bool header = true;

    while (std::getline(file, line)) {
        if (header) {
            header = false;
            continue;
        }

        std::vector<std::string> parts = split(line, ',');
        if (parts.size() == 3) {
            permissions.emplace_back(parts[0], parts[1], parts[2] == "1");
        }
    }

    return permissions;
}

std::vector<AuditLog> FileStorage::loadAuditLogs() const {
    std::vector<AuditLog> logs;
    std::ifstream file(dataDirectory + "/audit_logs.csv");
    std::string line;
    bool header = true;

    while (std::getline(file, line)) {
        if (header) {
            header = false;
            continue;
        }

        std::vector<std::string> parts = split(line, ',');
        if (parts.size() == 7) {
            logs.emplace_back(std::stoi(parts[0]), std::stoi(parts[1]), std::stoi(parts[2]),
                              parts[3], parts[4], std::stoi(parts[5]), parts[6]);
        }
    }

    return logs;
}

void FileStorage::saveAgents(const std::vector<Agent>& agents) const {
    std::ofstream file(dataDirectory + "/agents.csv");
    file << "id,name,role,active\n";

    for (const Agent& agent : agents) {
        file << agent.getId() << ","
             << agent.getName() << ","
             << agent.getRole() << ","
             << (agent.isActive() ? "1" : "0") << "\n";
    }
}

void FileStorage::saveTools(const std::vector<Tool>& tools) const {
    std::ofstream file(dataDirectory + "/tools.csv");
    file << "id,name,description,baseRisk\n";

    for (const Tool& tool : tools) {
        file << tool.getId() << ","
             << tool.getName() << ","
             << tool.getDescription() << ","
             << tool.getBaseRisk() << "\n";
    }
}

void FileStorage::savePermissions(const std::vector<Permission>& permissions) const {
    std::ofstream file(dataDirectory + "/permissions.csv");
    file << "role,toolName,allowed\n";

    for (const Permission& permission : permissions) {
        file << permission.getRole() << ","
             << permission.getToolName() << ","
             << (permission.isAllowed() ? "1" : "0") << "\n";
    }
}

void FileStorage::appendAuditLog(const AuditLog& log) const {
    std::ofstream file(dataDirectory + "/audit_logs.csv", std::ios::app);
    file << log.getLogId() << ","
         << log.getAgentId() << ","
         << log.getToolId() << ","
         << log.getResource() << ","
         << log.getDecision() << ","
         << log.getRiskScore() << ","
         << log.getTimestamp() << "\n";
}

void FileStorage::appendPendingReview(int requestId, int agentId, int toolId,
                                      const std::string& resource, int riskScore,
                                      const std::string& status) const {
    std::ofstream file(dataDirectory + "/pending_reviews.csv", std::ios::app);
    file << requestId << ","
         << agentId << ","
         << toolId << ","
         << resource << ","
         << riskScore << ","
         << status << "\n";
}

void FileStorage::showPendingReviews() const {
    std::ifstream file(dataDirectory + "/pending_reviews.csv");
    std::string line;
    bool header = true;

    std::cout << "\n--- Pending Reviews ---\n";

    while (std::getline(file, line)) {
        if (header) {
            header = false;
            continue;
        }

        std::vector<std::string> parts = split(line, ',');
        if (parts.size() == 6 && parts[5] == "PENDING") {
            std::cout << "Request ID: " << parts[0]
                      << " | Agent ID: " << parts[1]
                      << " | Tool ID: " << parts[2]
                      << " | Resource: " << parts[3]
                      << " | Risk: " << parts[4]
                      << " | Status: " << parts[5] << "\n";
        }
    }
}

void FileStorage::updatePendingReviewStatus(int requestId, const std::string& status) const {
    std::ifstream input(dataDirectory + "/pending_reviews.csv");
    std::vector<std::string> lines;
    std::string line;
    bool header = true;

    while (std::getline(input, line)) {
        if (header) {
            lines.push_back(line);
            header = false;
            continue;
        }

        std::vector<std::string> parts = split(line, ',');
        if (parts.size() == 6 && std::stoi(parts[0]) == requestId) {
            parts[5] = status;
            line = parts[0] + "," + parts[1] + "," + parts[2] + "," + parts[3] + "," + parts[4] + "," + parts[5];
        }
        lines.push_back(line);
    }

    std::ofstream output(dataDirectory + "/pending_reviews.csv");
    for (const std::string& savedLine : lines) {
        output << savedLine << "\n";
    }
}

