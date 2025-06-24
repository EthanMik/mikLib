#include "vex.h"

using namespace mik;

mik::motor::motor(int port, bool reversed, std::string name) :
    port(port), reversed(reversed), name(name), mtr(port, reversed)
{};

mik::motor_group::motor_group(const std::vector<mik::motor>& motors) :
    motors(motors)
{
    for (const auto& motor : motors) {
        vex_motors.push_back(motor.mtr);
    }
};

vex::motor& mik::motor_group::get_motor(std::string motor_name) {
    for (auto& motor : motors) {
        if (motor.name == motor_name) {
            return motor.mtr;
        }
    }
    Brain.Screen.printAt(30, 30, (motor_name + " NOT FOUND").c_str());
    print((motor_name + " NOT FOUND").c_str());
    std::abort();
}

void mik::motor_group::spin(vex::directionType direction, float speed, velocity_units velocityUnits) {
    speed = to_volt(speed, velocityUnits);
    setSpeed = speed;

    for (vex::motor& motor : vex_motors) {
        motor.spin(direction, speed, vex::voltageUnits::volt);
    }
}

void mik::motor_group::spin_for_time(vex::directionType direction, int speed, velocity_units velocityUnits, float time, vex::timeUnits timeUnits) {
    speed = to_volt(speed, velocityUnits);
    setSpeed = speed;

    for (vex::motor& motor : vex_motors) {
        motor.spin(direction, speed, vex::voltageUnits::volt);
    }

    wait(time, timeUnits);
    stop(vex::brake);
}

void mik::motor_group::flip_direction() {
    for (vex::motor& motor : vex_motors) {
        motor.spin(vex::fwd, setSpeed * -1, vex::voltageUnits::volt);
    }
}

void mik::motor_group::set_position(float position, vex::rotationUnits rotationUnits) {
    for (vex::motor& motor : vex_motors) {
        motor.setPosition(position, rotationUnits);
    }   
}

float mik::motor_group::get_position(vex::rotationUnits rotationUnits) {
    float position = 0;

    for (vex::motor& motor : vex_motors) {
        position += motor.position(rotationUnits);
    }   
    return position / vex_motors.size();
}

float mik::motor_group::get_wattage() {
    float position = 0;

    for (vex::motor& motor : vex_motors) {
        position += motor.power();
    }   
    return position / vex_motors.size();
}

float mik::motor_group::get_temp() {
    float position = 0;

    for (vex::motor& motor : vex_motors) {
        position += motor.temperature(vex::temperatureUnits::fahrenheit);
    }   
    return position / vex_motors.size();
}

void mik::motor_group::stop(vex::brakeType brake) {
    for (vex::motor& motor : vex_motors) {
        motor.stop(brake);
    }   
}

void mik::motor_group::set_stopping(vex::brakeType brake) {
    for (vex::motor& motor : vex_motors) {
        motor.setStopping(brake);
    }   
}

float mik::motor_group::get_set_speed(velocity_units velocityUnits) {
    return from_volt(setSpeed, velocityUnits);
}

float mik::motor_group::to_volt(float speed, velocity_units velocityUnits) {
    switch (velocityUnits) {
        case velocity_units::NORM:
            return normalize_to_volt(speed);
        case velocity_units::PERCENT:
            return percent_to_volt(speed);
        default:
            return speed;
    }
}

float mik::motor_group::from_volt(float volt, velocity_units velocityUnits) {
    volt = clamp(volt, 0, 12);

    switch(velocityUnits) {
        case velocity_units::NORM:
            return volt_to_normalized(volt);
        case velocity_units::PERCENT:
            return volt_to_percent(volt);
        default:
            return volt;
    }
}