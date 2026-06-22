#ifndef ACCESS_REQUEST_H
#define ACCESS_REQUEST_H

#include <string>

class AccessRequest {
private:
    int requestId;
    int agentId;
    int toolId;
    std::string resource;
    std::string purpose;

public:
    AccessRequest();
    AccessRequest(int requestId, int agentId, int toolId, const std::string& resource, const std::string& purpose);

    int getRequestId() const;
    int getAgentId() const;
    int getToolId() const;
    std::string getResource() const;
    std::string getPurpose() const;
};

#endif

