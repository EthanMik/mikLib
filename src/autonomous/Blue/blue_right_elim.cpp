#include "vex.h"

std::string blue_right_elim(bool calibrate, mik::auto_variation var, bool get_name) {
    if (get_name) { return "blue right elim"; }

    // Mirror autons here

    if (calibrate) {
        // Run startup sequence that you want in pre-auton, do before field controller plug in
        chassis.set_coordinates(0, 0, 0);

        return "";
    }

    // Place start of autonoumous here

    return "";
}
