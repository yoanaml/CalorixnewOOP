#include "UserFactory.h"

std::unique_ptr<User> UserFactory::createTrainee(
    int id,
    const std::string& username,
    const std::string& password,
    int age,
    double weight,
    double height,
    Gender gender,
    ActivityLevel activityLevel
) {
    return std::make_unique<Trainee>(
        id,
        username,
        password,
        age,
        weight,
        height,
        gender,
        activityLevel
    );
}

std::unique_ptr<User> UserFactory::createAdmin(
    int id,
    const std::string& username,
    const std::string& password,
    const std::string& adminKey
) {
    return std::make_unique<Admin>(
        id,
        username,
        password,
        adminKey
    );
}