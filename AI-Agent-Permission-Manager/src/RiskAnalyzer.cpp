#include "RiskAnalyzer.h"
#include <algorithm>
#include <cctype>

int RiskAnalyzer::calculateRisk(const Agent& agent, const Tool& tool, const std::string& resource) const {
    int score = tool.getBaseRisk();
    std::string loweredResource = resource;

    std::transform(loweredResource.begin(), loweredResource.end(), loweredResource.begin(), ::tolower);

    if (!agent.isActive()) {
        return 100;
    }

    if (loweredResource.find("salary") != std::string::npos ||
        loweredResource.find("customer") != std::string::npos ||
        loweredResource.find("password") != std::string::npos ||
        loweredResource.find("private") != std::string::npos) {
        score += 20;
    }

    if (loweredResource.find("@gmail.com") != std::string::npos ||
        loweredResource.find("@yahoo.com") != std::string::npos ||
        loweredResource.find("external") != std::string::npos) {
        score += 15;
    }

    if (score > 100) {
        score = 100;
    }

    return score;
}

std::string RiskAnalyzer::riskLevel(int score) const {
    if (score <= 40) {
        return "LOW";
    }
    if (score <= 75) {
        return "MEDIUM";
    }
    return "HIGH";
}
