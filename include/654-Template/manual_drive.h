#ifndef MANUAL_DRIVE_H
#define MANUAL_DRIVE_H

#include "654-Template/motor_chain.h"
#include "654-Template/auton_drive.h"
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


#endif