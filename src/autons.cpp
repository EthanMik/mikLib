#include "vex.h"

using namespace vex;
using namespace mik;

void default_constants() {
    // Each controller constant in the form of throttle, turn (deadband, min_output, curve_gain).
    chassis.set_control_constants(5, 10, 1.019, 5, 10, 1.019);

    // Each constant set is in the form of (maxVoltage, kP, kI, kD, startI, slew).
    chassis.set_turn_constants(12, .35, .01, 2.1, 15, 0);
    chassis.set_drive_constants(10, 1.1, 0, 12, 0, 0);
    chassis.set_heading_constants(10, .4, 0, 1, 0, 0);
    chassis.set_swing_constants(12, .4, .01, 2, 15, 0);

    // Each exit condition set is in the form of (settle_error, settle_time, timeout).
    chassis.set_turn_exit_conditions(1, 200, 3000);
    chassis.set_drive_exit_conditions(1.5, 200, 5000);
    chassis.set_swing_exit_conditions(1, 200, 3000);

    chassis.heading_max_voltage = 10;
    chassis.drive_max_voltage = 8;
    chassis.drive_settle_error = 3;
    chassis.boomerang_lead = .5;
    chassis.boomerang_setback = 2;  
    chassis.boomerang_drift = 2;  // Change to 8 if you are not running all omni wheels
}

std::string skills(bool calibrate, auto_variation var, bool get_name) {
    if (get_name) { return "skills"; }
    if (calibrate) {
        
        return "";
    }
    print("new skills run");
    // skills_2();
    // return "";

    chassis.set_coordinates(-46, 0, 90);
    assembly.rake_piston.open();
    task::sleep(200);
    chassis.drive_to_point(-35, 0, {.max_voltage = 2});
    task::sleep(800);
    assembly.rake_piston.close();
    task::sleep(300);

    chassis.drive_distance(6);

    chassis.turn_to_angle(180);

    chassis.drive_to_pose(-56.25, 47, 270, { .heading_k.p = .3, .heading_k.d = 3, .min_voltage = 1, .settle_time = 0 });    
    
    chassis.drive_distance(-12, { .timeout = 700, .max_voltage = 4 });

    matchload();
    chassis.drive_distance(-1.5, {.settle_time = 300});
    // chassis.drive_with_voltage(-2, -2);
    task::sleep(3000);
    stop_matchload();

    chassis.drive_distance(10, {.settle_time = 0, .settle_error = 5});
    chassis.drive_to_pose(-22.37, 59.59, 90, {.heading_k.p = .3, .heading_k.d = 3, .min_voltage = 1, .settle_time = 0});
    
    intake();
    chassis.drive_to_point(23.55, 59.99, { .settle_time = 0, .settle_error = 5, .min_voltage = 1});
    chassis.drive_to_pose(47, 47, 180, {.heading_k.p = .3, .heading_k.d = 3, .wait = false});
    chassis.wait_until(5);
    lift_barrel();
    chassis.wait();

    chassis.drive_distance(4, { .settle_error = 1 });
    chassis.turn_to_angle(270);
    // chassis.turn_to_point(31.5, 47);
    chassis.drive_distance(15, { .max_voltage = 4, .timeout = 1000});
    chassis.reset_axis(rear_sensor, 8);
    chassis.reset_axis(right_sensor, 8);

    repeat({
        score();
        task::sleep(1000);
    }, 3);

    stop_intake();

    chassis.drive_to_point(53, 47);
    drop_barrel();

    chassis.turn_to_point(68.5, 47, { .angle_offset = 180 });
    chassis.drive_distance(-10, {.max_voltage = 4, .timeout = 1000});

    matchload();
    // chassis.drive_with_voltage(-2, -2);
    chassis.drive_distance(-1.5, { .settle_time = 300});
    task::sleep(3000);
    stop_matchload();

    intake();
    chassis.drive_to_pose(34.5, 47, 270);
    lift_barrel();

    chassis.turn_to_point(21, 47);

    chassis.drive_distance(10, { .timeout = 500, .max_voltage = 4 });

    repeat({
        score();
        task::sleep(1000);
    }, 3);

    chassis.drive_to_point(47, 47);
    drop_barrel();

    // chassis.turn_to_point(47, 61.25);
    chassis.turn_to_angle(0);
    intake();
    chassis.drive_distance(12, { .timeout = 1500, .max_voltage = 4 });
    task::sleep(200);
    chassis.drive_distance(-7);


    chassis.drive_to_pose(44.39, 0, 90, { .heading_k.p = .3, .heading_k.d = 3, .lead = 0.6, .wait = false});
    chassis.wait_until(10);
    stop_intake();
    chassis.wait();

    chassis.drive_distance(-5, {.settle_error = 1, .timeout = 1200});

    // Lockdown skills part 2

    skills_2();

    return "";
}

void skills_2() {
    chassis.set_coordinates(46.25, 0, 270);
    chassis.reset_axis(rear_sensor, 8);
    chassis.reset_axis(right_sensor, 8);

    assembly.rake_piston.open();
    task::sleep(200);
    chassis.drive_distance(7, { .max_voltage = 2});
    task::sleep(800);
    assembly.rake_piston.close();
    task::sleep(500);
    chassis.drive_to_point(28, 0);
    chassis.turn_to_angle(180);
    chassis.drive_distance(15);
    intake();
    chassis.right_swing_to_angle(0, { .max_voltage = 9, .turn_direction = ccw, .min_voltage = 1, .opposite_voltage = 0.5 });
    chassis.drive_distance(16, { .max_voltage = 3 });
    
    chassis.right_swing_to_point(8.21, 19.81);
    chassis.drive_to_pose(6, 21, 300, {.heading_k.p = .3, .heading_k.d = 3});
    chassis.turn_to_point(17.21, 17.21, {.angle_offset = 180});
    chassis.drive_to_point(17.21, 17.21);
    chassis.turn_to_angle(45);
    chassis.drive_distance(-6.5, { .settle_error = 1, .max_voltage = 2});
    outtake_rear(8);
    task::sleep(2000);
    override_barrel = true;
    assembly.barrel_motor.spin(reverse, 4, volt);
    task::sleep(7000);
}

std::string blue_left_winpoint(bool calibrate, auto_variation var, bool get_name) {
    if (get_name) { return "blue left winpoint"; }
    if (calibrate) {
        // chassis.set_coordinates(0, 0, 0);
        chassis.set_coordinates(47.125, 47.125, 0);

        chassis.wait_until(100, percent);
        assembly.barrel_motor.spin(fwd, 0, volt);
        chassis.wait();

        return "";
    }


    // chassis.turn_to_angle(180, { .max_voltage = 6 });

    return "";
}
std::string blue_left_sawp(bool calibrate, auto_variation var, bool get_name) { 
    if (get_name) { return "blue left sawp"; }
    if (calibrate) {
        chassis.set_coordinates(0, 0, 0);

        return "";
    }

    return "";
}
std::string blue_left_elim(bool calibrate, auto_variation var, bool get_name) {   
    if (get_name) { return "blue left elim"; }
    if (calibrate) {
        chassis.set_coordinates(0, 0, 0);

        return "";
    }

    return "";
}
std::string blue_right_winpoint(bool calibrate, auto_variation var, bool get_name) {
    if (get_name) { return "blue right winpoint"; }
    if (calibrate) {
        chassis.set_coordinates(0, 0, 0);

        return "";
    }

    return "";
}
std::string blue_right_sawp(bool calibrate, auto_variation var, bool get_name) { 
    if (get_name) { return "blue right sawp"; }
    if (calibrate) {
        chassis.set_coordinates(0, 0, 0);

        return "";
    }

    return "";
}
std::string blue_right_elim(bool calibrate, auto_variation var, bool get_name) {
    if (get_name) { return "blue right elim"; }
    if (calibrate) {
        chassis.set_coordinates(0, 0, 0);

        return "";
    }

    return "";
}

std::string red_left_winpoint(bool calibrate, auto_variation var, bool get_name) { 
    if (get_name) { return "red left winpoint"; }
    if (calibrate) {
        chassis.set_coordinates(0, 0, 0);

        return "";
    }
    
    return "";
}
std::string red_left_sawp(bool calibrate, auto_variation var, bool get_name) { 
    if (get_name) { return "red left sawp"; }
    if (calibrate) {
        chassis.set_coordinates(0, 0, 0);

        return "";
    }

    return "";
}
std::string red_left_elim(bool calibrate, auto_variation var, bool get_name) { 
    if (get_name) { return "red left elim"; }
    if (calibrate) {
        chassis.set_coordinates(0, 0, 0);
        
        return "";
    }
    
    return "";
}
std::string red_right_winpoint(bool calibrate, auto_variation var, bool get_name) { 
    if (get_name) { return "red right winpoint"; }
    if (calibrate) {
        chassis.set_coordinates(0, 0, 0);
        
        return "";
    }

    return "";
}
std::string red_right_sawp(bool calibrate, auto_variation var, bool get_name) {
    if (get_name) { return "red right sawp"; }
    if (calibrate) {
        chassis.set_coordinates(0, 0, 0);
        
        return "";
    }

    return "";
}
std::string red_right_elim(bool calibrate, auto_variation var, bool get_name) {   
    if (get_name) { return "red right elim"; }
    if (calibrate) {
        chassis.set_coordinates(0, 0, 0);

        return "";
    }

    return "";
}