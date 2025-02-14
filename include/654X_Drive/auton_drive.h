#pragma once

#include "vex.h"

class auton_drive {
private:
    float wheel_diameter;
    float wheel_ratio;
    float drive_inch_to_deg_ratio;
    float inertial_scale;

    float forward_tracker_diameter;
    float forward_tracker_center_distance;
    float forward_tracker_inch_to_deg_ratio;

    float sideways_tracker_diameter;
    float sideways_tracker_center_distance;
    float sideways_tracker_inch_to_deg_ratio;

    float desired_heading;

    float idealX;
    float idealY;

public:
    auton_drive(hzn::motor_group left_drive, hzn::motor_group right_drive, int inertial_port, float wheel_diameter, float wheel_ratio, float inertial_scale, int forward_tracker_port, float forward_tracker_diameter, 
        float forward_tracker_center_distance, int sideways_tracker_port, float sideways_tracker_diameter, float sideways_tracker_center_distance);

    //Helper Methods general
    float get_absolute_heading();
    float get_heading();

    //Helper Methods drive
    void drive_with_voltage(float leftVoltage, float rightVoltage);
    void override_brake_type(vex::brakeType brake);
    void stop_drive(vex::brakeType brake);
    float get_left_position_in();
    float get_right_position_in();

    //PID drive methods
    void turn_on_PID(float angle);

    void turn_on_PID(float angle, float turn_max_voltage, float turn_settle_error, float turn_settle_time, 
        float turn_timeout, float turn_kp, float turn_ki, float turn_kd, float turn_starti);
    
    void drive_on_PID(float distance);

    void drive_on_PID(float distance, float heading, float drive_max_voltage, float heading_max_voltage, 
        float drive_settle_error, float drive_settle_time, float drive_timeout, float drive_kp, float drive_ki, 
        float drive_kd, float drive_starti, float heading_kp, float heading_ki, float heading_kd, float heading_starti);

    void left_swing_to_angle(float angle);

    void left_swing_to_angle(float angle, float swing_max_voltage, float swing_settle_error, float swing_settle_time, 
        float swing_timeout, float swing_kp, float swing_ki, float swing_kd, float swing_starti);

    void right_swing_to_angle(float angle);

    void right_swing_to_angle(float angle, float swing_max_voltage, float swing_settle_error, float swing_settle_time, 
        float swing_timeout, float swing_kp, float swing_ki, float swing_kd, float swing_starti);


    //PID Helper methods
    void set_drive_constants(float drive_max_voltage, float drive_kp, float drive_ki, float drive_kd, float drive_starti, float drive_settle_error, float drive_settle_time, float drive_timeout);
    void set_turn_constants(float turn_max_voltage, float turn_kp, float turn_ki, float turn_kd, float turn_starti, float turn_settle_error, float turn_settle_time, float turn_timeout);
    void set_heading_constants(float heading_max_voltage, float heading_kp, float heading_ki, float heading_kd, float heading_starti);
    void set_swing_constants(float swing_max_voltage, float swing_kp, float swing_ki, float swing_kd, float swing_starti, float turn_settle_error, float turn_settle_time, float turn_timeout);

    //Odom Helper methods
    odom odom;
    float get_ForwardTracker_position();
    float get_SidewaysTracker_position();
    void set_coordinates(float X_position, float Y_position, float orientation_deg);
    void set_heading(float orientation_deg);
    void position_track();
    static int position_track_task();
    vex::task odom_task;
    float get_X_position();
    float get_Y_position();

    float ideal_x_position(float x); 
    float ideal_y_position(float y);
    float ideal_x = 0.0;
    float ideal_y = 0.0;

    std::vector<float> get_position_vector();

    //Odom drive methods
    void turn_to_point(float X_position, float Y_position);
    void turn_to_point(float X_position, float Y_position, bool reversed);
    void turn_to_point(float X_position, float Y_position, bool reversed, float turn_max_voltage, float turn_settle_error, float turn_settle_time, float turn_timeout, float turn_kp, float turn_ki, float turn_kd, float turn_starti);

    void drive_to_point(float X_position, float Y_position);
    void drive_to_point(float X_position, float Y_position, float drive_min_voltage, float drive_max_voltage, float heading_max_voltage, float drive_settle_error, float drive_settle_time, float drive_timeout, float drive_kp, float drive_ki, float drive_kd, float drive_starti, float heading_kp, float heading_ki, float heading_kd, float heading_starti);

    void drive_to_pose(float X_position, float Y_position, float angle);
    void drive_to_pose(float X_position, float Y_position, float angle, float lead, float setback, 
        float drive_min_voltage, float drive_max_voltage, float heading_max_voltage, float drive_settle_error, 
        float drive_settle_time, float drive_timeout, float drive_kp, float drive_ki, float drive_kd, 
        float drive_starti, float heading_kp, float heading_ki, float heading_kd, float heading_starti);
    
    //Vector field helper methods

    //Vector field drive methods

    void split_arcade();

public:
    float turn_max_voltage;
    float turn_kp;
    float turn_ki;
    float turn_kd;
    float turn_starti;

    float turn_settle_error;
    float turn_settle_time;
    float turn_timeout;

    float drive_min_voltage;
    float drive_max_voltage;
    float drive_kp;
    float drive_ki;
    float drive_kd;
    float drive_starti;

    float drive_settle_error;
    float drive_settle_time;
    float drive_timeout;

    float heading_max_voltage;
    float heading_kp;
    float heading_ki;
    float heading_kd;
    float heading_starti;

    float swing_max_voltage;
    float swing_kp;
    float swing_ki;
    float swing_kd;
    float swing_starti;

    float swing_settle_error;
    float swing_settle_time;
    float swing_timeout;

    float boomerang_lead;
    float boomerang_setback;

    vex::rotation forward_tracker;
    vex::rotation sideways_tracker;
    vex::inertial inertial;

    hzn::motor_group left_drive;
    hzn::motor_group right_drive; 

    vex::brakeType brake_type;
    bool brake_is_overrided;
};