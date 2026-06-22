#include "AccessDecision.h"

std::string decisionToString(DecisionType decision) {
    switch (decision) {
        case DecisionType::ALLOW:
            return "ALLOW";
        case DecisionType::DENY:
            return "DENY";
        case DecisionType::REVIEW_REQUIRED:
            return "REVIEW_REQUIRED";
    }
    return "DENY";
}

DecisionType stringToDecision(const std::string& value) {
    if (value == "ALLOW") {
        return DecisionType::ALLOW;
    }
    if (value == "REVIEW_REQUIRED") {
        return DecisionType::REVIEW_REQUIRED;
    }
    return DecisionType::DENY;
}

AccessDecision::AccessDecision()
    : decision(DecisionType::DENY), reason("No decision made"), riskScore(0) {}

AccessDecision::AccessDecision(DecisionType decision, const std::string& reason, int riskScore)
    : decision(decision), reason(reason), riskScore(riskScore) {}

DecisionType AccessDecision::getDecision() const {
    return decision;
}

std::string AccessDecision::getReason() const {
    return reason;
}

int AccessDecision::getRiskScore() const {
    return riskScore;
}

