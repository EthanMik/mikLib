#include "vex.h"

using namespace hzn;

hzn::motor::motor(int port, bool reversed, std::string name) :
    port(port), reversed(reversed), name(name), mtr(port, reversed)
{};

hzn::motor_group::motor_group(const std::vector<hzn::motor>& motor_constructor) :
    motor_constructor(motor_constructor)
{
    for (const auto& motor : motor_constructor) {
        motors.push_back(motor.mtr);
    }
};

vex::motor& hzn::motor_group::get_motor(std::string motor_name) {
    for (auto& motor : motor_constructor) {
        if (motor.name == motor_name) {
            return motor.mtr;
        }
    }
    Brain.Screen.printAt(30, 30, (motor_name + " NOT FOUND").c_str());
    exit(1);
}

void hzn::motor_group::spin(vex::directionType direction, float speed, velocity_units velocityUnits) {
    speed = to_volt(speed, velocityUnits);
    setSpeed = speed;

    for (vex::motor& motor : motors) {
        motor.spin(direction, speed, vex::voltageUnits::volt);
    }
}

void hzn::motor_group::spin_for_time(vex::directionType direction, int speed, velocity_units velocityUnits, float time, vex::timeUnits timeUnits) {
    speed = to_volt(speed, velocityUnits);
    setSpeed = speed;

    for (vex::motor& motor : motors) {
        motor.spin(direction, speed, vex::voltageUnits::volt);
    }

    wait(time, timeUnits);
    stop(vex::brake);
}

void hzn::motor_group::flip_direction() {
    for (vex::motor& motor : motors) {
        motor.spin(vex::fwd, setSpeed * -1, vex::voltageUnits::volt);
    }
}

void hzn::motor_group::set_position(float position, vex::rotationUnits rotationUnits) {
    for (vex::motor& motor : motors) {
        motor.setPosition(position, rotationUnits);
    }   
}

float hzn::motor_group::get_position(vex::rotationUnits rotationUnits) {
    float position = 0;

    for (vex::motor& motor : motors) {
        position += motor.position(rotationUnits);
    }   
    return position / motors.size();
}

void hzn::motor_group::stop(vex::brakeType brake) {
    for (vex::motor& motor : motors) {
        motor.stop(brake);
    }   
}

float hzn::motor_group::get_set_speed(velocity_units velocityUnits) {
    return from_volt(setSpeed, velocityUnits);
}

float hzn::motor_group::to_volt(float speed, velocity_units velocityUnits) {
    switch (velocityUnits) {
        case velocity_units::normalized:
            return normalize_to_volt(speed);
        case velocity_units::percent:
            return percent_to_volt(speed);
        default:
            return speed;
    }
}

float hzn::motor_group::from_volt(float volt, velocity_units velocityUnits) {
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