#pragma once

#include "vex.h"

using namespace vex;

// The internals of this class is example code and can be deleted

// This is example code for a push back robot with two 5.5W motors on the lower intake,
// 11W motor on the top intake, a scraper, and wing

class Assembly {
public:
/* Create your devices here */
    static mik::motor_group back_intake_motors;
    static mik::motor transfer_motor;
    static mik::motor front_intake_motor;
    static mik::motor barrel_motor;

/* Examples of other vex devices you may need */
    static mik::piston barrel_lift_piston;
    static mik::piston back_intake_piston;
    static mik::piston rake_piston;

    void init();
    void control();

    void lower_intake_control();
    void upper_intake_control();
    void wing_piston_control();
    void scraper_piston_control();
    
};