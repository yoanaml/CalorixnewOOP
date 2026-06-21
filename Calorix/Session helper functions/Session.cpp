#include "Session.h"
#include "../InputParser/InputParser.h"
#include "../FileManager/FileManager.h"
#include <iostream>

void runTraineeSession(Trainee* p_trainee, Calorix& system)
{
    p_trainee->help();
    std::string cmd;
    while (std::cin >> cmd && cmd != "logout")
    {
        if (cmd == "log-food")
            p_trainee->logFood(system);
        else if (cmd == "log-exercise")
            p_trainee->logExercise(system);
        else if (cmd == "view-daily-summary")
            p_trainee->viewDailySummary();
        else if (cmd == "view-progress")
            p_trainee->viewProgress();
        else if (cmd == "calculate-bmi")
            p_trainee->calculateBMI();
        else if (cmd == "calculate-bmr")
            p_trainee->calculateBMR();
        else if (cmd == "add-to-favorites")
            p_trainee->addToFavorites(system);
        else if (cmd == "view-favorites")
            p_trainee->viewFavorites();
        else if (cmd == "set-goals")
        {
            std::string typeStr;
            double f32Target;
            int sd, sm, sy, dd, dm, dy;
            std::cout << "Enter goal type (WEIGHT_LOSS/BULKING/MAINTENANCE), target value, "
                "start date (dd mm yyyy), deadline (dd mm yyyy):\n";
            std::cin >> typeStr >> f32Target >> sd >> sm >> sy >> dd >> dm >> dy;
            p_trainee->addGoal(FitnessGoal(parseGoalType(typeStr), f32Target,
                Date(sd, sm, sy), Date(dd, dm, dy)));
            std::cout << "Goal added.\n";
        }
        else if (cmd == "generate-workout-plan")
            std::cout << "Not yet implemented.\n";
        else
            std::cout << "Unknown command. Type 'logout' to exit.\n";
    }
    std::cout << "Logged out.\n";
}

void runAdminSession(Admin* p_admin, Calorix& system)
{
    p_admin->help();
    std::string cmd;
    while (std::cin >> cmd && cmd != "logout")
    {
        if (cmd == "add-food")
            p_admin->addFood(system);
        else if (cmd == "add-exercise")
            p_admin->addExercise(system);
        else if (cmd == "update-food")
            p_admin->updateFood(system);
        else if (cmd == "block-user")
        {
            std::string username;
            std::cin >> username;
            p_admin->blockUser(username, system);
        }
        else
            std::cout << "Unknown command. Type 'logout' to exit.\n";
    }
    std::cout << "Logged out.\n";
}

void runTest(Calorix& system)
{
    std::cout << "=== Running test ===\n\n";

    bool adminOk = system.registerAdmin("admin1", "adminpass", "SECRET");
    std::cout << "Register admin1: " << (adminOk ? "OK" : "FAIL") << "\n";

    User* p_adminUser = system.login("admin1", "adminpass");
    std::cout << "Login admin1: " << (p_adminUser ? "OK" : "FAIL") << "\n";

    Admin* p_admin = dynamic_cast<Admin*>(p_adminUser);
    (void)p_admin;

    system.addFood("Chicken", 165, 31, 0, 4);
    system.addFood("Rice", 130, 3, 28, 1);
    system.addExercise("Running", 600.0, MuscleGroup::CARDIO);
    system.addExercise("Squats", 400.0, MuscleGroup::LEGS);
    std::cout << "Admin added 2 foods and 2 exercises.\n";

    bool dupFood = system.addFood("Chicken", 165, 31, 0, 4);
    std::cout << "Add duplicate Chicken: " << (!dupFood ? "correctly rejected" : "FAIL") << "\n";

    bool updated = system.updateFood("Rice", 140);
    std::cout << "Update Rice calories: " << (updated ? "OK" : "FAIL") << "\n";

    bool traineeOk = system.registerTrainee(
        "trainee1", "pass123",
        25, 80.0, 1.80,
        Gender::MALE, ActivityLevel::MODERATE
    );
    std::cout << "Register trainee1: " << (traineeOk ? "OK" : "FAIL") << "\n";

    bool dupUser = system.registerTrainee(
        "trainee1", "other",
        20, 70.0, 1.75,
        Gender::FEMALE, ActivityLevel::LIGHT
    );
    std::cout << "Register duplicate trainee1: " << (!dupUser ? "correctly rejected" : "FAIL") << "\n";

    User* p_traineeUser = system.login("trainee1", "pass123");
    std::cout << "Login trainee1: " << (p_traineeUser ? "OK" : "FAIL") << "\n";

    Trainee* p_trainee = dynamic_cast<Trainee*>(p_traineeUser);

    User* p_badLogin = system.login("trainee1", "wrongpass");
    std::cout << "Login with wrong password: " << (!p_badLogin ? "correctly rejected" : "FAIL") << "\n";

    Food* p_chicken = system.findFood("Chicken");
    Food* p_rice = system.findFood("Rice");
    Exercise* p_running = system.findExercise("Running");
    Exercise* p_squats = system.findExercise("Squats");

    p_trainee->addFoodEntry(FoodEntry(*p_chicken, 200.0, Date::today()));
    p_trainee->addFoodEntry(FoodEntry(*p_rice, 150.0, Date::today()));
    p_trainee->addExerciseEntry(ExerciseEntry(*p_running, 30, Date::today()));
    p_trainee->addExerciseEntry(ExerciseEntry(*p_squats, 20, Date::today()));
    std::cout << "\nLogged food and exercise entries.\n";

    p_trainee->addFavoriteExercise(*p_running);
    p_trainee->addFavoriteExercise(*p_squats);

    std::cout << "\n";
    p_trainee->viewDailySummary();

    std::cout << "\n";
    p_trainee->viewProgress();

    std::cout << "\n";
    p_trainee->viewFavorites();

    std::cout << "\n";
    p_trainee->calculateBMI();
    p_trainee->calculateBMR();

    std::cout << "\n";
    bool blocked = system.blockUser("trainee1");
    std::cout << "Block trainee1: " << (blocked ? "OK" : "FAIL") << "\n";

    User* p_afterBlock = system.login("trainee1", "pass123");
    std::cout << "Login after block: " << (!p_afterBlock ? "correctly rejected" : "FAIL") << "\n";

    std::cout << "\n=== Test complete ===\n\n";
}