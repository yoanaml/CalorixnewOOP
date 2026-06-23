#pragma once
#include <memory>
#include <unordered_map>
#include "../UsersLogic/User.h"
#include "../UsersLogic/Trainee.h"
#include "../UsersLogic/Admin.h"
#include "../Food/Food.h"
#include "../Exercises/Exercise.h"

class FileManager;

class Calorix
{
    friend class FileManager;

    std::unordered_map<std::string, std::unique_ptr<User>> users;
    std::unordered_map<std::string, Food>                  foods;
    std::unordered_map<std::string, Exercise>              exercises;

    Calorix() = default;

public:

    Calorix(const Calorix&) = delete;
    Calorix& operator=(const Calorix&) = delete;

    static Calorix& getInstance();

    bool registerTrainee(
        const std::string& username,
        const std::string& password,
        int s8Age,
        double f32Weight,
        double f32Height,
        Gender gender,
        ActivityLevel activityLevel
    );

    bool registerAdmin(
        const std::string& username,
        const std::string& password,
        const std::string& adminKey
    );

    User* login(const std::string& username, const std::string& password);

    bool addFood(const std::string& name, int s8Cal, int s8Protein, int s8Carbs, int s8Fat);
    bool addExercise(const std::string& name, double f32CalPerHour, MuscleGroup group);
    bool updateFood(const std::string& name, int s8NewCalories);
    bool blockUser(const std::string& username);

    Food* findFood(const std::string& name);
    Exercise* findExercise(const std::string& name);

    const std::unordered_map<std::string, Food>& getFoods()     const;
    const std::unordered_map<std::string, Exercise>& getExercises() const;
    const std::unordered_map<std::string, std::unique_ptr<User>>& getUsers()     const;
};

