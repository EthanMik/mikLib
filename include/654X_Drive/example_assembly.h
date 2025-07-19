#pragma once

#include "vex.h"

using namespace vex;

class Example_Assembly {
public:
    Example_Assembly(
        mik::motor_group intake_motors_5w, 
        mik::motor intake_motor_11w,
        int long_piston_port, 
        int distance_sensor_port
    );
    
    void intake_motor_11w_control();
    void intake_motors_5w_control();
    void long_piston_control();

    bool long_piston_extended = false;
    bool was_long_piston_activated = false;

    mik::motor_group intake_motors_5w;
    mik::motor intake_motor_11w;
    digital_out long_piston;
    distance distance_sensor;

};