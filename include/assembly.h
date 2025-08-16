#pragma once

#include "vex.h"

using namespace vex;

enum lift_positions : int { IDLE = 229, LOADING = 206, SCORING = 99 };

class Assembly {
public:
    Assembly(
        mik::motor_group lift_arm_motors,
        mik::motor intake_motor, 
        vex::rotation lift_arm_encoder,
        mik::piston long_piston
    );
    
    void init();
    void control();

    void move_lift_arm();
    void lift_arm_control();
    void intake_motors_control();
    void long_piston_control();

    int lift_arm_position = IDLE;
    vex::task lift_task;
    
    mik::motor_group lift_arm_motors;
    mik::motor intake_motor;
    vex::rotation lift_arm_encoder;
    mik::piston long_piston;
};