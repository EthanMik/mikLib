#ifndef AUTON_DRIVE_H
#define AUTON_DRIVE_H

#include "654-Template/motor_chain.h"
#include "654-Template/manual_drive.h"
#include "654-Template/odom.h"
#include "vex.h"
#include "motor_chain.h"
#include <vector>


class auton_drive {
private:
    float Wheel_diameter;
    float Wheel_ratio;
    float Drive_in_to_deg_ratio;

    float ForwardTracker_diameter;
    float ForwardTracker_center_distance;
    float ForwardTracker_in_to_deg_ratio;

    float SidewaysTracker_diameter;
    float SidewaysTracker_center_distance;
    float SidewaysTracker_in_to_deg_ratio;

    float desired_heading;
    bool track_pid = false;

public:
    auton_drive(motor_chain leftDrive, motor_chain rightDrive, float Wheel_diamteter, float Wheel_ratio, int ForwardTracker_port, float ForwardTracker_diameter, 
        float ForwardTracker_center_distance, int SidewaysTracker_port, float SidewaysTracker_diameter, float SidewaysTracker_center_distance);

    //Helper Methods general
    float get_absolute_heading();

    //Helper Methods drive
    void drive_with_voltage(float leftVoltage, float rightVoltage);
    void stop_drive(vex::brakeType brake);
    float get_left_position_in();
    float get_right_position_in();

    //PID drive methods
    void turn_on_PID(float angle, float turn_max_voltage, float turn_settle_error, float turn_settle_time, 
        float turn_timeout, float turn_kp, float turn_ki, float turn_kd, float turn_starti);
        
    void drive_on_PID(float distance, float heading, float drive_max_voltage, float heading_max_voltage, 
        float drive_settle_error, float drive_settle_time, float drive_timeout, float drive_kp, float drive_ki, 
        float drive_kd, float drive_starti, float heading_kp, float heading_ki, float heading_kd, float heading_starti);

    //Odom Helper methods
    Odom odom;
    float get_ForwardTracker_position();
    float get_SidewaysTracker_position();
    void set_coordinates(float X_position, float Y_position, float orientation_deg);
    void set_heading(float orientation_deg);
    void position_track();
    static int position_track_task();
    vex::task odom_task;
    float get_X_position();
    float get_Y_position();
    std::vector<float> get_position_vector();

    //Odom drive methods
    void drive_to_pose(float X_position, float Y_position, float angle, float lead, float setback, 
        float drive_min_voltage, float drive_max_voltage, float heading_max_voltage, float drive_settle_error, 
        float drive_settle_time, float drive_timeout, float drive_kp, float drive_ki, float drive_kd, 
        float drive_starti, float heading_kp, float heading_ki, float heading_kd, float heading_starti);
    //Vector field helper methods

    //Vector field drive methods

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

    motor_chain leftDrive;
    motor_chain rightDrive; 

    rotation forwardTracker;
    rotation sidewaysTracker;

};

#endif