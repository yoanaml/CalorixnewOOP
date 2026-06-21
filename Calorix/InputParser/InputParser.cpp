#include "InputParser.h"
#include <unordered_map>

GoalType parseGoalType(const std::string& s)
{
    if (s == "WEIGHT_LOSS") return GoalType::WEIGHT_LOSS;
    if (s == "BULKING")     return GoalType::BULKING;
    return GoalType::MAINTENANCE;
}

Gender parseGender(const std::string& s)
{
    if (s == "MALE")   return Gender::MALE;
    if (s == "FEMALE") return Gender::FEMALE;
    return Gender::OTHER;
}

ActivityLevel parseActivityLevel(const std::string& s)
{
    static const std::unordered_map<std::string, ActivityLevel> table = {
        {"SEDENTARY",   ActivityLevel::SEDENTARY},
        {"LIGHT",       ActivityLevel::LIGHT},
        {"MODERATE",    ActivityLevel::MODERATE},
        {"ACTIVE",      ActivityLevel::ACTIVE},
        {"VERY_ACTIVE", ActivityLevel::VERY_ACTIVE},
    };
    auto it = table.find(s);
    if (it != table.end())
        return it->second;
    return ActivityLevel::SEDENTARY;
}