#ifndef MANUAL_DRIVE_H
#define MANUAL_DRIVE_H

#include "vex.h"
#include "motor_chain.h"

class manual_drive {   
public:
    manual_drive(motor_chain leftDrive, motor_chain rightDrive);

    void control_drive_tasks();

    void control_drivetrain();

public:
    motor_chain leftDrive;
    motor_chain rightDrive;
};


#endif