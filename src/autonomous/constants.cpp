#include "vex.h"

using namespace vex;
using namespace mik;

void default_constants() {
    // Each controller constant in the form of throttle, turn (deadband, min_output, curve_gain), desaturate_bias.
    chassis.set_control_constants(5, 10, 1.019, 5, 10, 1.019, 0.5);

    // Each constant set is in the form of (maxVoltage, kP, kI, kD, startI, slew).
    chassis.set_drive_constants(8, 1.5, 0, 10, 0, 2);
    chassis.set_heading_constants(10, .4, 0, 1, 0, 0);
    chassis.set_turn_constants(12, .4, .03, 3, 15, 0);
    chassis.set_swing_constants(12, .4, .01, 2, 15, 0);

    // Each exit condition set is in the form of (settle_error, settle_time, timeout).
    chassis.set_turn_exit_conditions(1, 200, 3000);
    chassis.set_drive_exit_conditions(2, 200, 5000);
    chassis.set_swing_exit_conditions(1, 200, 3000);

    constants.boomerang_lead = .5;
    constants.boomerang_drift = 2;
}

// When using motor encoders, it's best to 
// have a high drive slew to prevent wheel slip.
void no_tracker_constants() {
    default_constants();
    constants.drive_slew = 1;
}

// Motion chaining constants are used to chain multiple movements together with minimal pause in between,
// make sure to add a chassis.stop_drive(hold) at the end of you auton if you are using min speed.
void motion_chaining_constants() {
    default_constants();

    constants.drive_min_voltage = 3;
    constants.turn_min_voltage = 3;
    constants.swing_min_voltage = 3;

    constants.drive_exit_error = 2;
    constants.turn_exit_error = 10;
    constants.swing_exit_error = 10;
}
