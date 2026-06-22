#ifndef POLICY_H
#define POLICY_H

#include "AccessDecision.h"
#include "AccessRequest.h"
#include "Agent.h"
#include "Permission.h"
#include "RiskAnalyzer.h"
#include "Tool.h"
#include <string>
#include <vector>

class Policy {
public:
    virtual AccessDecision evaluate(const AccessRequest& request,
                                    const Agent& agent,
                                    const Tool& tool,
                                    const std::vector<Permission>& permissions,
                                    const RiskAnalyzer& riskAnalyzer) const = 0;

    virtual std::string getPolicyName() const = 0;
    virtual ~Policy() = default;
};

class StatusPolicy : public Policy {
public:
    AccessDecision evaluate(const AccessRequest& request,
                            const Agent& agent,
                            const Tool& tool,
                            const std::vector<Permission>& permissions,
                            const RiskAnalyzer& riskAnalyzer) const override;

    std::string getPolicyName() const override;
};

class RoleBasedPolicy : public Policy {
public:
    AccessDecision evaluate(const AccessRequest& request,
                            const Agent& agent,
                            const Tool& tool,
                            const std::vector<Permission>& permissions,
                            const RiskAnalyzer& riskAnalyzer) const override;

    std::string getPolicyName() const override;
};

class RiskBasedPolicy : public Policy {
public:
    AccessDecision evaluate(const AccessRequest& request,
                            const Agent& agent,
                            const Tool& tool,
                            const std::vector<Permission>& permissions,
                            const RiskAnalyzer& riskAnalyzer) const override;

    std::string getPolicyName() const override;
};

#endif

