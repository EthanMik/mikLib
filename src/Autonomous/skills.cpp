#include "vex.h"

using namespace vex;
using namespace mik;

enum LB_state : int { active = 206, inactive = 229, holding = 170, scoring = 43, hang = 345 };

std::string skills(bool calibrate, mik::auto_variation var, bool get_name) {
    if (get_name) { return "skills"; }
    if (calibrate) {
        chassis.set_coordinates(-54.5, 0, 270);

        return "";
    }

    // Score alliance ring
    move_lift(hang);
    wait(.4, sec);
    
    // Drive into and clamp goal, idle lift
    chassis.drive_distance(-13);
    clamp_goal();
    move_lift(inactive);

    // Collect ring
    chassis.turn_to_point(-24.5, -24); 
    intake_forward();
    chassis.drive_to_point(-24.5, -24); 
    
    // Collect and stage ring into lift
    chassis.turn_to_point(50.752, -61.884); 
    chassis.drive_to_point(50.752, -61.884); 
    move_lift(active);
    chassis.drive_to_point(-0.284, -43); 
    
    // Turn and move to wallstake, intake ring halfway
    stop_intake();
    move_lift(holding - 30);
    chassis.turn_to_point(-0.284, -62.694); 
    intake_ring_halfway();
    chassis.drive_to_point(-0.284, -62.694); 
    chassis.drive_distance(30, {.max_voltage = 8, .timeout = 1000}); 

    // Score first ring
    move_lift(scoring);
    wait(.5, sec);

    // Stage lift for next ring
    move_lift(active);
    wait(.4, sec);
    
    // Move ring into lift
    chassis.drive_with_voltage(4, 4);
    intake_forward();
    wait(.25, sec);

    // Score next ring
    move_lift(scoring);
    wait(.5, sec);

    // Reset odom X coordinate
    chassis.reset_axis(front_sensor, right_wall, 5);

    // Back up from wallstake, idle lift
    chassis.drive_distance(-13); 
    move_lift(inactive);
    
    // Collect three rings
    chassis.turn_to_point(-60.516, -46.973); 
    intake_forward();
    chassis.drive_to_point(-40.299, -46.973); 
    chassis.drive_to_point(-60.516, -46.973, {.max_voltage = 6}); 

    // Turn and collect one ring
    chassis.turn_to_point(-47.818, -57.727); 
    chassis.drive_to_point(-47.818, -57.727, {.max_voltage = 8}); 
    
    // Drop mogo off
    chassis.turn_to_point(-58, -61, {.angle_offset = 180}); 
    chassis.drive_distance(-10, {.timeout = 400}); 
    unclamp_goal();
    
    // Leave corner
    chassis.drive_distance(10); 
    stop_intake();
    
    return "";
}