#ifndef RISK_ANALYZER_H
#define RISK_ANALYZER_H

#include "Agent.h"
#include "Tool.h"
#include <string>

class RiskAnalyzer {
public:
    int calculateRisk(const Agent& agent, const Tool& tool, const std::string& resource) const;
    std::string riskLevel(int score) const;
};

#endif

