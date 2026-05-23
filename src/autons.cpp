#include "vex.h"

// voltage = kS + kV * velocity
// y intercept is kS, slope is kV
void velocity_test() {
    chassis.set_coordinates(0, 0, 0);
    for (float v = 1.0; v <= 12.0; v += 1.0) {
        chassis.drive_with_voltage(v, v);
        task::sleep(600);
        float p1 = chassis.get_forward_tracker_position();
        task::sleep(20);
        float p2 = chassis.get_forward_tracker_position();
        float vel = (p2 - p1) / 0.02;
        print(to_string(v) + ", " + to_string(vel));
    }
    chassis.stop_drive(vex::brakeType::hold);
}

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

/* When creating autons with odometry, use a path planner, https://path.jerryio.com/.
If your robot is not lining up with the points, double check you set up your odometry correctly */

std::string blue_left_winpoint(bool calibrate, auto_variation var, bool get_name) {
    if (get_name) return "blue left winpoint";

    // Mirror autons here
    
    if (calibrate) {
        // Run startup sequence that you want in pre-auton, do before field controller plug in
        chassis.set_coordinates(0, 0, 0);

        return "";
    }    

    follow_path_params p = {
        .max_velocity = 58.1,
        .max_accel = 40.1,
        .friction = 0.4,
        .lookahead = 5,
        .kA = .07,
        .kV = .21,
        .kS = 1.2,
        .timeout = 10000,
    };

    // int start = Brain.Timer.systemHighResolution();
    // std::vector<path> path = motion_profile({{0, 0}, {0, 18}, {6, 24}, {24, 24}}, p, 12.5);
    // print("start");
    // // print(Brain.Timer.systemHighResolution() - start);
    // // print("start");
    // for (size_t i = 0; i < path.size(); ++i) {
    //     print(to_string_float(path[i].x, 2) + ", " + to_string_float(path[i].y, 2));
    //     // print(to_string_float(path[i].distance, 5) + ", " + to_string_float(path[i].velocity, 5));
    //     task::sleep(20);
    // }
    // print("end");

    chassis.set_coordinates(0, 0, 0);

    // chassis.follow_path({{0, 0}, {1, 1}, {1, 1}, {0, 24}}, p);
    chassis.follow_path({{1, 0}, {22, 18}, {-19, 12}, {1, 34}}, p);
    chassis.follow_path({{1, 34}, {26, 38}, {27, -7}, {1, 0}}, p);

    return "";
}

std::string blue_left_sawp(bool calibrate, auto_variation var, bool get_name) {
    if (get_name) return "blue left sawp";
    
    // Mirror autons here
    
    // [sawp2]
    if (calibrate) {
        // Run startup sequence that you want in pre-auton, do before field controller plug in
        chassis.set_coordinates(49.58, 23.87, 90);
        return "";
    }
    
    assembly.unjam_intake_task();
    stop_intake();
    color_sort_auton(color_sort::RED);

    float time = Brain.Timer.time(msec);
    assembly.LB_motors.stop(hold);
    assembly.LB_motors.spin(fwd, -12, velocity_units::volt);
    task::sleep(600);
    LB_task(INACTIVE);
    
    chassis.turn_to_point(21.7, 24.3, {.angle_offset = 180});
    constants.drive_max_voltage = 6;
    chassis.drive_to_point(21.7, 24.3, {.min_voltage = 6, .exit_error = 3.5, .wait = false});
    chassis.wait_until_within(3);
    assembly.mogo_clamp_piston.set(true);
    chassis.cancel_motion();

    default_constants();
    task::sleep(200);
    start_intake();
    chassis.turn_to_point(23.59, 44.5);
    chassis.drive_to_point(23.59, 44.5);
    chassis.turn_to_point(47.41, 1.25);
    assembly.lift_piston.set(true);
    chassis.drive_to_point(47.41, 1.25);
    start_intake(false);
    intake_ring_halfway();
    assembly.lift_piston.set(false);
    chassis.drive_distance(-8);
    assembly.mogo_clamp_piston.set(false);
    constants.drive_max_voltage = 12;
    chassis.drive_distance(20.92);

    chassis.turn_to_point(23.64, -23.17, {.angle_offset = 180});
    constants.drive_max_voltage = 6;
    chassis.drive_to_point(23.64, -23.17);
    default_constants();
    assembly.mogo_clamp_piston.set(true);
    task::sleep(200);
    default_constants();
    chassis.turn_to_point(23.59, -44.5);
    start_intake();
    chassis.drive_to_point(23.59, -44.5);
    LB_task(SCORING);
    chassis.turn_to_point(10.81, -33.89);
    chassis.drive_to_point(10.81, -33.89);
    stop_intake();
    chassis.stop_drive(hold);

    Brain.Screen.printAt(30, 30, "%f", Brain.Timer.time(msec) - time);
    // [sawp2]



    return "";
}
std::string blue_left_elim(bool calibrate, auto_variation var, bool get_name) {
    if (get_name) return "blue left elim";

    // Mirror autons here

    if (calibrate) {
        // Run startup sequence that you want in pre-auton, do before field controller plug in
        chassis.set_coordinates(0, 0, 0);

        return "";
    }

    // Place start of autonoumous here

    return "";
}
std::string blue_right_winpoint(bool calibrate, auto_variation var, bool get_name) {
    // [left-elim]
    if (get_name) return "blue right winpoint";

    // Mirror autons here

    if (calibrate) {
        // Run startup sequence that you want in pre-auton, do before field controller plug in
        chassis.set_coordinates(-50.25, -16.37, 90);

        return "";
    }

    // Place start of autonoumous here



    chassis.drive_to_pose(-22.45, -21.99, 140, {.min_voltage = 5, .exit_error = 5, .lead = 0.3});
    chassis.drive_to_point(-7.17, -45.14);
    chassis.drive_to_point(-22.2, -22.14);
    intake();
    chassis.drive_to_point(-46.5, -47.5);
    chassis.turn_to_point(-59.81, -47.53);
    chassis.drive_to_point(-59.81, -47.53);
    chassis.drive_to_point(-31.84, -47.37);
    task::sleep(640);
    // [left-elim]
    return "";
}
std::string blue_right_sawp(bool calibrate, auto_variation var, bool get_name) {
    // [waittest]
    if (get_name) return "blue right sawp";
    
    // Mirror autons here

    if (calibrate) {
        // Run startup sequence that you want in pre-auton, do before field controller plug in

        return "";
    }

    // Place start of autonoumous here
    
    // [waittest]
    return "";
}
std::string blue_right_elim(bool calibrate, auto_variation var, bool get_name) {
    if (get_name) return "blue right elim";

    // Mirror autons here

    if (calibrate) {
        // Run startup sequence that you want in pre-auton, do before field controller plug in
        chassis.set_coordinates(0, 0, 0);

        return "";
    }

    // Place start of autonoumous here

    return "";
}

std::string red_left_winpoint(bool calibrate, auto_variation var, bool get_name) {
    if (get_name) return "red left winpoint";

    // Mirror autons here

    if (calibrate) {
        // Run startup sequence that you want in pre-auton, do before field controller plug in
        chassis.set_coordinates(0, 0, 0);

        return "";
    }

    // Place start of autonoumous here

    return "";
}
std::string red_left_sawp(bool calibrate, auto_variation var, bool get_name) {
    if (get_name) return "red left sawp";

    // Mirror autons here

    if (calibrate) {
        // Run startup sequence that you want in pre-auton, do before field controller plug in
        chassis.set_coordinates(0, 0, 0);

        return "";
    }

    // Place start of autonoumous here

    return "";
}
std::string red_left_elim(bool calibrate, auto_variation var, bool get_name) {
    if (get_name) return "red left elim";

    // Mirror autons here

    if (calibrate) {
        // Run startup sequence that you want in pre-auton, do before field controller plug in
        chassis.set_coordinates(0, 0, 0);

        return "";
    }

    // Place start of autonoumous here

    return "";
}
std::string red_right_winpoint(bool calibrate, auto_variation var, bool get_name) {
    if (get_name) return "red right winpoint";

    // Mirror autons here

    if (calibrate) {
        // Run startup sequence that you want in pre-auton, do before field controller plug in
        chassis.set_coordinates(0, 0, 0);

        return "";
    }

    // Place start of autonoumous here

    return "";
}
std::string red_right_sawp(bool calibrate, auto_variation var, bool get_name) {
    if (get_name) return "red right sawp";

    // Mirror autons here

    if (calibrate) {
        // Run startup sequence that you want in pre-auton, do before field controller plug in
        chassis.set_coordinates(0, 0, 0);

        return "";
    }

    // Place start of autonoumous here

    return "";
}
std::string red_right_elim(bool calibrate, auto_variation var, bool get_name) {
    if (get_name) return "red right elim";

    // Mirror autons here

    if (calibrate) {
        // Run startup sequence that you want in pre-auton, do before field controller plug in
        chassis.set_coordinates(0, 0, 0);

        return "";
    }

    // Place start of autonoumous here

    return "";
}
std::string skills(bool calibrate, auto_variation var, bool get_name) {
    if (get_name) return "skills";

    // Mirror autons here

    if (calibrate) {
        // Run startup sequence that you want in pre-auton, do before field controller plug in

        return "";
    }

    // Place start of autonoumous here

    return "";
}