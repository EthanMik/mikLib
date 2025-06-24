#pragma once

#include "vex.h"

enum direction : int { DEFAULT = 0, CW = 1, CCW = 2};
enum class drive_mode { SPLIT_ARCADE, SPLIT_ARCADE_SQUARED, ARCADE_RIGHT, ARCADE_LEFT, TANK, TANK_SQUARED };

class Chassis {
public:
    Chassis(mik::motor_group left_drive, mik::motor_group right_drive, int inertial_port, float wheel_diameter, float wheel_ratio, float inertial_scale, int forward_tracker_port, float forward_tracker_diameter, float forward_tracker_center_distance, int sideways_tracker_port, float sideways_tracker_diameter, float sideways_tracker_center_distance);

    void set_drive_constants(float drive_max_voltage, float drive_kp, float drive_ki, float drive_kd, float drive_starti, float drive_settle_error, float drive_settle_time, float drive_timeout);
    void set_turn_constants(float turn_max_voltage, float turn_kp, float turn_ki, float turn_kd, float turn_starti, float turn_settle_error, float turn_tolerance, float turn_settle_time, float turn_timeout);
    void set_heading_constants(float heading_max_voltage, float heading_kp, float heading_ki, float heading_kd, float heading_starti);
    void set_swing_constants(float swing_max_voltage, float swing_kp, float swing_ki, float swing_kd, float swing_starti, float turn_settle_error, float turn_tolerance, float turn_settle_time, float turn_timeout);
    void set_brake_type(vex::brakeType brake);

    void wait();
    void wait(float units);
    
    void drive_with_voltage(float leftVoltage, float rightVoltage);
    void stop_drive(vex::brakeType brake);

    float get_absolute_heading();
    float get_heading();

    float get_left_position_in();
    float get_right_position_in();
    
    void turn(float angle, bool wait = true);
    void turn(float angle, float turn_max_voltage, bool wait = true);
    void turn(float angle, direction dir, bool wait = true);
    void turn(float angle, float turn_max_voltage, float turn_settle_error, float turn_settle_time, float turn_timeout, bool wait = true);
    void turn(float angle, direction dir, float turn_max_voltage, float turn_settle_error, float turn_settle_time, float turn_timeout, float turn_kp, float turn_ki, float turn_kd, float turn_starti, bool wait = true);

    void drive(float distance, bool wait = true);
    void drive(float distance, float heading, bool wait = true);
    void drive(float distance, float heading, float drive_max_voltage, bool wait = true);
    void drive(float distance, float drive_max_voltage, float drive_settle_error, float drive_settle_time, float drive_timeout, bool wait = true);
    void drive(float distance, float heading, float drive_max_voltage, float heading_max_voltage, float drive_settle_error, float drive_settle_time, float drive_timeout, float drive_kp, float drive_ki, float drive_kd, float drive_starti, float heading_kp, float heading_ki, float heading_kd, float heading_starti, bool wait = true);

    void left_swing(float angle, bool wait = true);
    void left_swing(float angle, float swing_max_voltage, bool wait = true);
    void left_swing(float angle, direction dir, bool wait = true);
    void left_swing(float angle, float swing_max_voltage, float swing_settle_error, float swing_settle_time, float swing_timeout, bool wait = true);
    void left_swing(float angle, direction dir, float swing_max_voltage, float swing_settle_error, float swing_settle_time, float swing_timeout, float swing_kp, float swing_ki, float swing_kd, float swing_starti, bool wait = true);

    void right_swing(float angle, bool wait = true);
    void right_swing(float angle, float swing_max_voltage, bool wait = true);
    void right_swing(float angle, direction dir, bool wait = true);
    void right_swing(float angle, float swing_max_voltage, float swing_settle_error, float swing_settle_time, float swing_timeout, bool wait = true);
    void right_swing(float angle, direction dir, float swing_max_voltage, float swing_settle_error, float swing_settle_time, float swing_timeout, float swing_kp, float swing_ki, float swing_kd, float swing_starti, bool wait = true);

    void enable_motion_chaining();
    void disable_motion_chaining();
    float get_ForwardTracker_position();
    float get_SidewaysTracker_position();
    void set_coordinates(float X_position, float Y_position, float orientation_deg);
    void set_heading(float orientation_deg);
    void position_track();
    static int position_track_task();
    float get_X_position();
    float get_Y_position();
    
    void turn_to_point(float X_position, float Y_position, bool wait = true);
    void turn_to_point(float X_position, float Y_position, direction dir, bool wait = true);
    void turn_to_point(float X_position, float Y_position, float angle_offset, bool wait = true);
    void turn_to_point(float X_position, float Y_position, float angle_offset, float turn_max_voltage, float turn_settle_error, float turn_settle_time, float turn_timeout, bool wait = true);
    void turn_to_point(float X_position, float Y_position, float angle_offset, direction dir, float turn_max_voltage, float turn_settle_error, float turn_settle_time, float turn_timeout, float turn_kp, float turn_ki, float turn_kd, float turn_starti, bool wait = true);
    
    void drive_to_point(float X_position, float Y_position, bool wait = true);
    void drive_to_point(float X_position, float Y_position, float drive_min_voltage, float drive_max_voltage, float heading_max_voltage, bool wait = true);
    void drive_to_point(float X_position, float Y_position, float drive_min_voltage, float drive_max_voltage, float heading_max_voltage, float drive_settle_error, float drive_settle_time, float drive_timeout, bool wait = true);
    void drive_to_point(float X_position, float Y_position, float drive_min_voltage, float drive_max_voltage, float heading_max_voltage, float drive_settle_error, float drive_settle_time, float drive_timeout, float drive_kp, float drive_ki, float drive_kd, float drive_starti, float heading_kp, float heading_ki, float heading_kd, float heading_starti, bool wait = true);
    
    void drive_to_pose(float X_position, float Y_position, float angle, bool wait = true);
    void drive_to_pose(float X_position, float Y_position, float angle, float lead, float setback, float drive_min_voltage, bool wait = true);
    void drive_to_pose(float X_position, float Y_position, float angle, float lead, float setback, float drive_min_voltage, float drive_max_voltage, float heading_max_voltage, bool wait = true);
    void drive_to_pose(float X_position, float Y_position, float angle, float lead, float setback, float drive_min_voltage, float drive_max_voltage, float heading_max_voltage, float drive_settle_error, float drive_settle_time, float drive_timeout, bool wait = true);
    void drive_to_pose(float X_position, float Y_position, float angle, float lead, float setback, float drive_min_voltage, float drive_max_voltage, float heading_max_voltage, float drive_settle_error, float drive_settle_time, float drive_timeout, float drive_kp, float drive_ki, float drive_kd, float drive_starti, float heading_kp, float heading_ki, float heading_kd, float heading_starti, bool wait = true);
    
    void disable_control();
    void enable_control();

    void split_arcade();
    void split_arcade_squared();
    void arcade_left();
    void arcade_right();
    void tank();
    void tank_squared();
    
    void control(drive_mode dm);
        
    float turn_max_voltage;
    float turn_kp;
    float turn_ki;
    float turn_kd;
    float turn_starti;
    
    float turn_settle_error;
    float turn_tolerance;
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
    float swing_tolerance;
    float swing_settle_time;
    float swing_timeout;
    
    float boomerang_lead;
    float boomerang_setback;
    
    int forward_tracker_port;
    int sideways_tracker_port;
    int inertial_port;
    
    vex::rotation forward_tracker;
    vex::rotation sideways_tracker;
    vex::inertial inertial;
    
    mik::motor_group left_drive;
    mik::motor_group right_drive; 
    
    float desired_heading;
    float desired_distance;
    float desired_X;
    float desired_Y;
    float angle_offset;
    direction dir;

    bool motion_chaining = false;

    bool motion_running;
    float distance_traveled;
    
    bool position_tracking;
    bool control_disabled;
  
    drive_mode selected_drive_mode = drive_mode::SPLIT_ARCADE;

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

    PID pid;
    PID pid_2;
    odom odom;
    vex::task drive_task;
    vex::task odom_task;
};