#include "vex.h"

motor_chain::motor_chain(std::vector<vex::motor> motors) {
    this->motors = motors;
}

void motor_chain::spin(vex::directionType direction, float speed, velocity_units velocityUnits) {
    speed = to_volt(speed, velocityUnits);
    setSpeed = speed;

    for (vex::motor& motor : motors) {
        motor.spin(direction, speed, vex::voltageUnits::volt);
    }
}

void motor_chain::spin_for_time(vex::directionType direction, int speed, velocity_units velocityUnits, float time, vex::timeUnits timeUnits) {
    speed = to_volt(speed, velocityUnits);
    setSpeed = speed;

    for (vex::motor& motor : motors) {
        motor.spin(direction, speed, vex::voltageUnits::volt);
    }

    wait(time, timeUnits);
    stop(brake);
}

void motor_chain::flip_direction() {
    for (vex::motor& motor : motors) {
        motor.spin(fwd, setSpeed * -1, vex::voltageUnits::volt);
    }
}

void motor_chain::set_position(float position, vex::rotationUnits rotationUnits) {
    for (vex::motor& motor : motors) {
        motor.setPosition(position, rotationUnits);
    }   
}

float motor_chain::get_position(vex::rotationUnits rotationUnits, vex::motor motor) {
    return motor.position(rotationUnits);
}

float motor_chain::get_position(vex::rotationUnits rotationUnits) {
    float position = 0;

    for (vex::motor& motor : motors) {
        position += motor.position(rotationUnits);
    }   
    return position / motors.size();
}

void motor_chain::stop(vex::brakeType brake) {
    for (vex::motor& motor : motors) {
        motor.stop(brake);
    }   
}

float motor_chain::get_set_speed(velocity_units velocityUnits) {
    return from_volt(setSpeed, velocityUnits);
}

float motor_chain::to_volt(float speed, velocity_units velocityUnits) {
    switch(velocityUnits){
        case velocity_units::normalized:
            return normalize_to_volt(speed);
        case velocity_units::percent:
            return percent_to_volt(speed);
        default:
            return speed;
    }
}

float motor_chain::from_volt(float volt, velocity_units velocityUnits) {
    volt = clamp(volt, 0, 12);

    switch(velocityUnits) {
        case velocity_units::normalized:
            return volt_to_normalized(volt);
        case velocity_units::percent:
            return volt_to_percent(volt);
        default:
            return volt;
    }
}