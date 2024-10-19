#ifndef TEST_H
#define TEST_H

#include "654-Template/motor_chain.h"
#include "654-Template/manual_drive.h"
#include "654-Template/auton_drive.h"
#include "654-Template/auton_drive_methods.h"
#include "robot-config.h"
#include "vex.h"

void spin_motors(std::vector<motor_chain> motor_chains);

#endif