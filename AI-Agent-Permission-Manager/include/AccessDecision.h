#ifndef ACCESS_DECISION_H
#define ACCESS_DECISION_H

#include <string>

enum class DecisionType {
    ALLOW,
    DENY,
    REVIEW_REQUIRED
};

std::string decisionToString(DecisionType decision);
DecisionType stringToDecision(const std::string& value);

class AccessDecision {
private:
    DecisionType decision;
    std::string reason;
    int riskScore;

public:
    AccessDecision();
    AccessDecision(DecisionType decision, const std::string& reason, int riskScore);

    DecisionType getDecision() const;
    std::string getReason() const;
    int getRiskScore() const;
};

#endif

