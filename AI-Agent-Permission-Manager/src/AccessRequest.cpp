#include "AccessRequest.h"

AccessRequest::AccessRequest() : requestId(0), agentId(0), toolId(0), resource(""), purpose("") {}

AccessRequest::AccessRequest(int requestId, int agentId, int toolId,
                             const std::string& resource, const std::string& purpose)
    : requestId(requestId), agentId(agentId), toolId(toolId), resource(resource), purpose(purpose) {}

int AccessRequest::getRequestId() const {
    return requestId;
}

int AccessRequest::getAgentId() const {
    return agentId;
}

int AccessRequest::getToolId() const {
    return toolId;
}

std::string AccessRequest::getResource() const {
    return resource;
}

std::string AccessRequest::getPurpose() const {
    return purpose;
}

