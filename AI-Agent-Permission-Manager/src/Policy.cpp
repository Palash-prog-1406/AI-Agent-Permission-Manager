#include "Policy.h"

AccessDecision StatusPolicy::evaluate(const AccessRequest& request,
                                      const Agent& agent,
                                      const Tool& tool,
                                      const std::vector<Permission>& permissions,
                                      const RiskAnalyzer& riskAnalyzer) const {
    (void)permissions;

    int riskScore = riskAnalyzer.calculateRisk(agent, tool, request.getResource());

    if (!agent.isActive()) {
        return AccessDecision(DecisionType::DENY, "Agent is inactive", riskScore);
    }

    return AccessDecision(DecisionType::ALLOW, "Agent is active", riskScore);
}

std::string StatusPolicy::getPolicyName() const {
    return "StatusPolicy";
}

AccessDecision RoleBasedPolicy::evaluate(const AccessRequest& request,
                                         const Agent& agent,
                                         const Tool& tool,
                                         const std::vector<Permission>& permissions,
                                         const RiskAnalyzer& riskAnalyzer) const {
    int riskScore = riskAnalyzer.calculateRisk(agent, tool, request.getResource());

    for (const Permission& permission : permissions) {
        if (permission.getRole() == agent.getRole() && permission.getToolName() == tool.getName()) {
            if (permission.isAllowed()) {
                return AccessDecision(DecisionType::ALLOW, "Role has permission for this tool", riskScore);
            }
            return AccessDecision(DecisionType::DENY, "Role is not allowed to use this tool", riskScore);
        }
    }

    return AccessDecision(DecisionType::DENY, "No permission rule found for this role and tool", riskScore);
}

std::string RoleBasedPolicy::getPolicyName() const {
    return "RoleBasedPolicy";
}

AccessDecision RiskBasedPolicy::evaluate(const AccessRequest& request,
                                         const Agent& agent,
                                         const Tool& tool,
                                         const std::vector<Permission>& permissions,
                                         const RiskAnalyzer& riskAnalyzer) const {
    (void)permissions;

    int riskScore = riskAnalyzer.calculateRisk(agent, tool, request.getResource());

    if (riskScore > 75) {
        return AccessDecision(DecisionType::REVIEW_REQUIRED, "High-risk request requires admin review", riskScore);
    }

    if (riskScore > 40) {
        return AccessDecision(DecisionType::REVIEW_REQUIRED, "Medium-risk request requires review", riskScore);
    }

    return AccessDecision(DecisionType::ALLOW, "Risk level is acceptable", riskScore);
}

std::string RiskBasedPolicy::getPolicyName() const {
    return "RiskBasedPolicy";
}
