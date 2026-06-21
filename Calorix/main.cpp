#include <iostream>
#include "../Calorix/Calorix/Calorix.h"
#include "../Calorix/UsersLogic/Admin.h"
#include "../Calorix/UsersLogic/Trainee.h"
#include "../Calorix/FileManager/FileManager.h"
#include "../Calorix/InputParser/InputParser.h"
#include "../Calorix/Session helper functions/Session.h"

int main()
{
    Calorix system;
    std::cout << "Please select an option\n";
    std::cout << "1: login\n";
    std::cout << "2: register\n";
    std::cout << "3: load from file\n";
    std::cout << "4: run test\n";

    std::string input;
    while (std::cin >> input && input != "end")
    {
        if (input == "1")
        {
            std::string user, password;
            std::cout << "Enter your username and password:\n";
            std::cin >> user >> password;
            User* p_logged = system.login(user, password);
            if (!p_logged)
            {
                std::cout << "Wrong credentials\n";
            }
            else
            {
                std::cout << "Welcome back " << user << "!\n";
                if (Admin* p_admin = dynamic_cast<Admin*>(p_logged))
                    runAdminSession(p_admin, system);
                else if (Trainee* p_trainee = dynamic_cast<Trainee*>(p_logged))
                    runTraineeSession(p_trainee, system);
            }
        }
        else if (input == "2")
        {
            std::string type;
            std::cout << "Register as (trainee/admin):\n";
            std::cin >> type;

            std::string username, password;
            std::cout << "Enter username and password:\n";
            std::cin >> username >> password;

            if (type == "admin")
            {
                std::string key;
                std::cout << "Enter admin key:\n";
                std::cin >> key;
                if (!system.registerAdmin(username, password, key))
                    std::cout << "Username '" << username << "' already taken.\n";
                else
                    std::cout << "Admin registered.\n";
            }
            else
            {
                int s8Age;
                double f32Weight, f32Height;
                std::string genderStr, activityStr;
                std::cout << "Enter age, weight (kg), height (m):\n";
                std::cin >> s8Age >> f32Weight >> f32Height;
                std::cout << "Enter gender (MALE/FEMALE/OTHER):\n";
                std::cin >> genderStr;
                std::cout << "Enter activity level (SEDENTARY/LIGHT/MODERATE/ACTIVE/VERY_ACTIVE):\n";
                std::cin >> activityStr;

                if (!system.registerTrainee(username, password, s8Age, f32Weight, f32Height,
                    parseGender(genderStr), parseActivityLevel(activityStr)))
                    std::cout << "Username '" << username << "' already taken.\n";
                else
                    std::cout << "Trainee registered.\n";
            }
        }
        else if (input == "3")
        {
            std::string fname;
            std::cout << "Enter filename to load:\n";
            std::cin >> fname;
            FileManager::load(system, fname);
        }
        else if (input == "4")
        {
            runTest(system);
        }
    }

    std::string saveChoice;
    std::cout << "Save before exit? (y/n):\n";
    std::cin >> saveChoice;
    if (saveChoice == "y" || saveChoice == "Y")
    {
        std::string fname;
        std::cout << "Enter filename:\n";
        std::cin >> fname;
        FileManager::save(system, fname);
    }

    return 0;
}