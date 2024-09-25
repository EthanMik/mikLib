#ifndef AUTON_DRIVE_H
#define AUTON_DRIVE_H

#include "654-Template/motor_chain.h"
#include "654-Template/manual_drive.h"
#include "vex.h"
#include "motor_chain.h"
#include <vector>


class auton_drive {   
public:
    auton_drive(motor_chain leftDrive, motor_chain rightDrive);

public:
    void turn_on_PID(float angle, float turn_max_voltage, float turn_settle_error, float turn_settle_time, float turn_timeout, float turn_kp, float turn_ki, float turn_kd, float turn_starti);

private:
    void drive_with_voltage(float leftVoltage, float rightVoltage);
    void printMatrix(std::vector<std::vector<float>> matrix) const;

public:
    motor_chain leftDrive;
    motor_chain rightDrive;
};

#endif