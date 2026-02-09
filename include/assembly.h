#pragma once

#include "vex.h"

using namespace vex;

// The internals of this class is example code and can be deleted

class Assembly {
public:
    // Make sure assembly.cpp matches the order of the devices
    Assembly(
        mik::motor_group lower_intake_motors,
        mik::motor upper_intake_motor, 
        mik::piston scraper_piston,
        mik::piston wing_piston
    );
    
    void init();
    void control();

    void lower_intake_control();
    void upper_intake_control();
    void wing_piston_control();
    void scraper_piston_control();
    
    mik::motor_group lower_intake_motors;
    mik::motor upper_intake_motor;
    mik::piston scraper_piston;
    mik::piston wing_piston;
};