#pragma once

#include "vex.h"

class manual_drive {   
public:
    manual_drive(motor_chain leftDrive, motor_chain rightDrive);

    void control_drive_tasks();

    void control_split_arcade(float speedLimiter = 1);
    
public:
    motor_chain leftDrive;
    motor_chain rightDrive;
};