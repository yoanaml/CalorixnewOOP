#pragma once

#include "../Calorix/Calorix.h"
#include "../UsersLogic/Admin.h"
#include "../UsersLogic/Trainee.h"

void runTraineeSession(Trainee* p_trainee, Calorix& system);
void runAdminSession(Admin* p_admin, Calorix& system);
void runTest(Calorix& system);

