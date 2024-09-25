#include "654-Template/manual_drive.h"
#include "654-Template/auton_drive.h"
#include "util.h"
#include "vex.h"

using namespace vex;

motor_chain::motor_chain(int MotorF_port, bool reverseF, int MotorM_port, bool reverseM, int MotorB_port, bool reverseB, 
        vex::gearSetting ratio):
    maxRPM(get_max_rpm(ratio)),
    motorF(MotorF_port, ratio, reverseF),
    motorM(MotorM_port, ratio, reverseM),
    motorB(MotorB_port, ratio, reverseB)
{
}

void motor_chain::spin(vex::directionType direction, float speed, velocity_units velocityUnits)
{
    speed = to_volt(speed, velocityUnits);
    setSpeed = speed;
    motorF.spin(direction, speed, volt);
    motorM.spin(direction, speed, volt);
    motorB.spin(direction, speed, volt);
}

void motor_chain::spin_for_time(vex::directionType direction, int speed, velocity_units velocityUnits, float time, vex::timeUnits timeUnits)
{
    speed = to_volt(speed, velocityUnits);
    setSpeed = speed;
    motorF.spin(direction, speed, volt);
    motorM.spin(direction, speed, volt);
    motorB.spin(direction, speed, volt);
    wait(time, timeUnits);
    stop(brake);
}

void motor_chain::flip_direction()
{
    motorF.spin(fwd, setSpeed * -1, volt);
    motorM.spin(fwd, setSpeed * -1, volt);
    motorB.spin(fwd, setSpeed * -1, volt);
}

void motor_chain::set_position(float position, vex::rotationUnits rotationUnits)
{
    motorF.setPosition(position, rotationUnits);
    motorM.setPosition(position, rotationUnits);
    motorB.setPosition(position, rotationUnits);
}

float motor_chain::get_position(vex::rotationUnits rotationUnits, vex::motor motor)
{
    return motor.position(rotationUnits);
}

float motor_chain::get_position(vex::rotationUnits rotationUnits)
{
    return (motorF.position(rotationUnits) + motorM.position(rotationUnits) + motorB.position(rotationUnits)) / 3;
}

void motor_chain::stop(vex::brakeType brake)
{
    motorF.stop(brake);
    motorM.stop(brake);
    motorB.stop(brake);
}

float motor_chain::get_set_speed(velocity_units velocityUnits)
{
    return from_volt(setSpeed, velocityUnits);
}

float motor_chain::get_max_rpm(vex::gearSetting gearSetting)
{
    switch(gearSetting)
    {
        case vex::gearSetting::ratio6_1:
            return 600.0;
        case vex::gearSetting::ratio18_1:
            return 200.0;
        case vex::gearSetting::ratio36_1:
            return 100.0;
        default:
            return 0.0;
    }
}

float motor_chain::to_volt(float speed, velocity_units velocityUnits)
{
    switch(velocityUnits){
        case velocity_units::normalized:
            return normalize_to_volt(speed);
        case velocity_units::percent:
            return percent_to_volt(speed);
        case velocity_units::rpm:
            return rpm_to_volt(speed, maxRPM);
        default:
            return speed;
    }
}

float motor_chain::from_volt(float volt, velocity_units velocityUnits)
{
    volt = clamp(volt, 0, 12);

    switch(velocityUnits) {
        case velocity_units::normalized:
            return volt_to_normalized(volt);
        case velocity_units::percent:
            return volt_to_percent(volt);
        case velocity_units::rpm:
            return volt_to_rpm(volt, maxRPM);
        default:
            return volt;
    }
}