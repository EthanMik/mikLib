#include "vex.h"

using namespace vex;
using namespace mik;

void default_constants() {
    // Each controller constant in the form of throttle, turn (deadband, min_output, curve_gain).
    chassis.set_control_constants(5, 10, 1.019, 5, 10, 1.019);

    // Each constant set is in the form of (maxVoltage, kP, kI, kD, startI, slew).
    chassis.set_turn_constants(12, .4, .03, 3, 15, 0);
    chassis.set_drive_constants(10, 1.5, 0, 10, 0, 0);
    chassis.set_heading_constants(6, .4, 0, 3, 0, 0);
    chassis.set_swing_constants(12, .4, .01, 2, 15, 0);

    // Each exit condition set is in the form of (settle_error, settle_time, timeout).
    chassis.set_turn_exit_conditions(1, 200, 3000);
    chassis.set_drive_exit_conditions(1.5, 200, 5000);
    chassis.set_swing_exit_conditions(1, 200, 3000);
}

// Odometry constants perform better with these drive constants, 
// make sure to call odom_constants() at the start of auto if you are using odometry!
void odom_constants() {
    default_constants();
    chassis.heading_max_voltage = 10;
    chassis.drive_max_voltage = 8;
    chassis.drive_settle_error = 3;
    chassis.boomerang_lead = .5;
    chassis.boomerang_setback = 2;  
    chassis.boomerang_drift = 2;  // Change to 8 if you are not running all omni wheels
}

// When using motor encoders, it's best to 
// have a high drive slew to prevent wheel slip.
void no_tracker_constants() {
    default_constants();
    chassis.drive_slew = 2;
}

// Motion chaining constants are used to chain multiple movements together with minimal pause in between,
// make sure to add a chassis.stop_drive(hold) at the end of you auton if you are using min speed.
void motion_chaining_constants() {
    odom_constants();
    chassis.drive_settle_error = 6;
    chassis.drive_min_voltage = 3;
    chassis.drive_settle_time = 0;
}
