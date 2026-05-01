#include "vex.h"

using namespace vex;
using namespace mik;

std::string skills(bool calibrate, mik::auto_variation var, bool get_name) {
    if (get_name) { return "skills"; }

    // Mirror autons here

    if (calibrate) {
        // Run startup sequence that you want in pre-auton, do before field controller plug in
        chassis.set_coordinates(0, 0, 0);

        return "";
    }

    // Place start of autonoumous here

    return "";
}


// Example auton template, you can delete this

std::string template_auto(bool calibrate, auto_variation var, bool get_name) {
    /* The first variation will be this auto */
    if (var == one) {}

    /* We declare and allow a second variation of this auto; 
    You may want this if you want a different movements in the same starting configuration */
    if (var == two) { return template_auto_other_variation(calibrate, get_name); }

    if (get_name) { /* Give a description of your auto */ return "template auto 1 (3 objs)"; }
    if (calibrate) {

        /* Initialize robots starting position "https://path.jerryio.com/" and/or add extra movements to line up robots 
        starting position **IF MOVING DURING CALIBRATION DO BEFORE FIELD CONTROLLER PLUG IN** */
        chassis.set_coordinates(55, 23.5, 90);
    
        /* Example of turning before auto is ran */
        chassis.turn_to_angle(45, { .max_voltage = 6 });

        return "";
    }
    
    /* We now run the auto */ 
    chassis.drive_distance(10);
    chassis.drive_distance(-10);

    return "";
}
std::string template_auto_other_variation(bool calibrate, bool get_name) {
    if (get_name) { return "template auto 2 (4 objs)"; }
    
    // Mirror template_auto() from the y-axis
    chassis.mirror_all_auton_y_pos();
    
    if (calibrate) {
        // Coordinates will be set to (55, -23.5) as y_pos is mirrored
        template_auto(calibrate, one, get_name);
        return "";
    }
    
    // Run auto, make sure to pass in one as var.
    template_auto(calibrate, one, get_name);

    return "";
}