#ifndef AUTON_DRIVE_H
#define AUTON_DRIVE_H

#include "654-Template/motor_chain.h"
#include "654-Template/manual_drive.h"
#include "vex.h"
#include "motor_chain.h"

class auton_drive {   
public:
    auton_drive(motor_chain leftDrive, motor_chain rightDrive);

public:
    motor_chain leftDrive;
    motor_chain rightDrive;
};

#endif