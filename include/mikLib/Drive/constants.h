#pragma once

#include "mikLib/drive.h"

struct Constants {
    // Drive constants, heading constants are used to keep robot facing toward target while driving

    float drive_min_voltage = 0; // Minimum voltage on the drive, used for chaining movements.
    float drive_max_voltage; // Max voltage out of 12.

    float drive_kp; // Proportional constant.
    float drive_ki; // Integral constant.
    float drive_kd; // Derivative constant.
    float drive_starti; // Minimum distance in inches for integral to begin
    float drive_slew;  // Limits drive acceleration in volt per 10 ms.

    float drive_exit_error = 0; // Error to exit drive motion in inches.
    float drive_settle_error; // Error to be considered settled in inches.
    float drive_settle_time; // Time to be considered settled in milliseconds.
    float drive_large_settle_error; // Error to be considered large settled in inches.
    float drive_large_settle_time; // Time to be considered large settled in milliseconds.
    float drive_timeout; // Time before quitting and move on in milliseconds.

    float heading_max_voltage; // Max voltage out of 12.
    float heading_kp; // Proportional constant.
    float heading_ki; // Integral constant.
    float heading_kd; // Derivative constant.
    float heading_starti; // Minimum distance in degrees for integral to begin
    float heading_slew; // Limits heading correction acceleration in volt per 10 ms.

    // Turn constants

    float turn_min_voltage = 0; // Minimum voltage for turning out of 12.
    float turn_max_voltage; // Max voltage out of 12.

    float turn_kp; // Proportional constant.
    float turn_ki; // Integral constant.
    float turn_kd; // Derivative constant.
    float turn_starti; // Minimum angle in degrees for integral to begin.
    float turn_slew; // Limits turning acceleration in volt per 10 ms.

    float turn_exit_error = 0; // Error to exit turn motion in inches.
    float turn_settle_error; // Error to be considered settled in degrees.
    float turn_settle_time; // Time to be considered settled in milliseconds.
    float turn_large_settle_error; // Error to be considered large settled in inches.
    float turn_large_settle_time; // Time to be considered settled by large error in milliseconds.
    float turn_timeout; // Time before quitting and move on in milliseconds.

    // Swing constants, turning with one side of drivetrain

    float swing_min_voltage = 0; // Minimum voltage for swinging out of 12.
    float swing_opposite_voltage = 0; // Voltage on the opposite swung drivetrain side out of 12.
    float swing_max_voltage; // Max voltage out of 12.

    float swing_kp; // Proportional constant.
    float swing_ki; // Integral constant.
    float swing_kd; // Derivative constant.
    float swing_starti; // Minimum distance in degrees for integral to begin
    float swing_slew; // Limits swinging acceleration in volt per 10 ms.

    float swing_exit_error; // Error to exit swing motion in inches.
    float swing_settle_error; // Error to be considered settled in degrees.
    float swing_settle_time; // Time to be considered settled in milliseconds.
    float swing_large_settle_error; // Error to be considered large settled in degrees.
    float swing_large_settle_time; // Time to be considered large settled in milliseconds.
    float swing_timeout; // Time before quitting and move on in milliseconds.
    
    // Drive to pose constants, (boomerang controller).

    float boomerang_lead; // Constant scale factor that determines how far away the carrot point is. 
    float boomerang_drift; // Determines the amount of horizontal drift allowed, lower values reduce drift while decreasing speed.

    // Constants for controlling drivetrain with joysticks

    float control_throttle_deadband; // Deadband percent for the throttle axis.
    float control_throttle_min_output; // Minimum throttle output percent after deadband.
    float control_throttle_curve_gain; // Expo gain for throttle axis (1 linear, 1.06 very curvy).
    
    float control_turn_deadband; // Deadband percent for the turn axis.
    float control_turn_min_output; // Minimum turn output percent after deadband.
    float control_turn_curve_gain; // Expo gain for turn axis (1 linear, 1.06 very curvy).
    float control_desaturate_bias; // Desaturation bias for split_arcade_curved (0 = prioritize turn, 1 = prioritize throttle).

    float turn_cutoff = 20; // Degrees, that within, slew will stop being applied.
    float drive_cutoff = 7; // Inches, that within, slew will stop being applied and heading correction stops.
};

struct drive_constants;
struct heading_constants;
struct turn_constants;
struct swing_constants;

extern Constants constants;

struct drive_constants {
  float p = constants.drive_kp;
  float i = constants.drive_ki;
  float d = constants.drive_kd;
  float starti = constants.drive_starti;
};

struct heading_constants {
  float p = constants.heading_kp;
  float i = constants.heading_ki;
  float d = constants.heading_kd;
  float starti = constants.heading_starti;
};

struct turn_constants {
  float p = constants.turn_kp;
  float i = constants.turn_ki;
  float d = constants.turn_kd;
  float starti = constants.turn_starti;
};

struct swing_constants {
  float p = constants.swing_kp;
  float i = constants.swing_ki;
  float d = constants.swing_kd;
  float starti = constants.swing_starti;
};

struct drive_distance_params {
    float heading = NAN;
    float min_voltage = constants.drive_min_voltage;
    float max_voltage = constants.drive_max_voltage;
    float heading_max_voltage = constants.heading_max_voltage;
    float exit_error = constants.drive_exit_error;
    float settle_error = constants.drive_settle_error;
    float settle_time = constants.drive_settle_time;
    float large_settle_error = constants.drive_large_settle_error;
    float large_settle_time = constants.drive_large_settle_time;
    float timeout = constants.drive_timeout;
    float slew = constants.drive_slew;
    float heading_slew = constants.heading_slew;
    bool wait = true;
    drive_constants drive_k = drive_constants{};
    heading_constants heading_k = heading_constants{};
};

struct turn_to_angle_params {
    mik::turn_direction direction = mik::turn_direction::FASTEST;
    float min_voltage = constants.turn_min_voltage;
    float max_voltage = constants.turn_max_voltage;
    float exit_error = constants.turn_exit_error;
    float settle_error = constants.turn_settle_error;
    float settle_time = constants.turn_settle_time;
    float large_settle_error = constants.turn_large_settle_error;
    float large_settle_time = constants.turn_large_settle_time;
    float timeout = constants.turn_timeout;
    float slew = constants.turn_slew;
    bool wait = true;
    turn_constants k = turn_constants{};
};

struct swing_to_angle_params {
    mik::turn_direction direction = mik::turn_direction::FASTEST;
    float min_voltage = constants.swing_min_voltage;
    float max_voltage = constants.swing_max_voltage;
    float opposite_voltage = constants.swing_opposite_voltage;
    float exit_error = constants.swing_exit_error;
    float settle_error = constants.swing_settle_error;
    float settle_time = constants.swing_settle_time;
    float large_settle_error = constants.swing_large_settle_error;
    float large_settle_time = constants.swing_large_settle_time;
    float timeout = constants.swing_timeout;
    float slew = constants.swing_slew;
    bool wait = true;
    swing_constants k = swing_constants{};
};

struct drive_to_point_params {
    float min_voltage = constants.drive_min_voltage;
    float max_voltage = constants.drive_max_voltage;
    float heading_max_voltage = constants.heading_max_voltage;
    float exit_error = constants.drive_exit_error;
    float settle_error = constants.drive_settle_error;
    float settle_time = constants.drive_settle_time;
    float large_settle_error = constants.drive_large_settle_error;
    float large_settle_time = constants.drive_large_settle_time;
    float timeout = constants.drive_timeout;
    float slew = constants.drive_slew;
    float heading_slew = constants.heading_slew;

    bool wait = true;
    drive_constants drive_k = drive_constants{};
    heading_constants heading_k = heading_constants{};
};

struct drive_to_pose_params {
    vex::directionType direction = vex::directionType::undefined;
    float lead = constants.boomerang_lead;
    float drift = constants.boomerang_drift;
    float min_voltage = constants.drive_min_voltage;
    float max_voltage = constants.drive_max_voltage;
    float heading_max_voltage = constants.heading_max_voltage;
    float exit_error = constants.drive_exit_error;
    float settle_error = constants.drive_settle_error;
    float settle_time = constants.drive_settle_time;
    float large_settle_error = constants.drive_large_settle_error;
    float large_settle_time = constants.drive_large_settle_time;
    float timeout = constants.drive_timeout;
    float slew = constants.drive_slew;
    bool wait = true;
    drive_constants drive_k = drive_constants{};
    heading_constants heading_k = heading_constants{};
};

struct turn_to_point_params {
    mik::turn_direction direction = mik::turn_direction::FASTEST;
    float angle_offset = 0;
    float min_voltage = constants.turn_min_voltage;
    float max_voltage = constants.turn_max_voltage;
    float exit_error = constants.turn_exit_error;
    float settle_error = constants.turn_settle_error;
    float settle_time = constants.turn_settle_time;
    float large_settle_error = constants.turn_large_settle_error;
    float large_settle_time = constants.turn_large_settle_time;
    float timeout = constants.turn_timeout;
    float slew = constants.turn_slew;
    bool wait = true;
    turn_constants k = turn_constants{};
};

struct swing_to_point_params {
    mik::turn_direction direction = mik::turn_direction::FASTEST;
    float angle_offset = 0;
    float min_voltage = constants.swing_min_voltage;
    float max_voltage = constants.swing_max_voltage;
    float opposite_voltage = constants.swing_opposite_voltage;
    float exit_error = constants.swing_exit_error;
    float settle_error = constants.swing_settle_error;
    float settle_time = constants.swing_settle_time;
    float large_settle_error = constants.swing_large_settle_error;
    float large_settle_time = constants.swing_large_settle_time;
    float timeout = constants.swing_timeout;
    float slew = constants.swing_slew;
    bool wait = true;
    swing_constants k = swing_constants{};
};