#include "vex.h"

std::string red_right_winpoint(bool calibrate, mik::auto_variation var, bool get_name) { 
    if (get_name) { return "red right winpoint"; }

    // Mirror autons here

    if (calibrate) {
        // Run startup sequence that you want in pre-auton, do before field controller plug in
        chassis.set_coordinates(-40, 0, 90);

        return "";
    }

    // Place start of autonoumous here

    return "";
}