#include "vex.h"

std::string red_left_elim(bool calibrate, mik::auto_variation var, bool get_name) { 
    if (get_name) { return "red left elim"; }

    // Mirror autons here

    if (calibrate) {
        // Run startup sequence that you want in pre-auton, do before field controller plug in
        chassis.set_coordinates(0, 0, 0);

        return "";
    }

    // Place start of autonoumous here

    return "";
}