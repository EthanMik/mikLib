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
    float swing_timeout; // Time before quitting and move on in milliseconds.
    
    // Drive to pose constants, (boomerang controller).

    float boomerang_lead; // Constant scale factor that determines how far away the carrot point is. 
    float boomerang_drift; // Decreasing drift results in a slower speeds while turning. Use higher values (~8) for traction drives 

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

extern Constants constants;

/** @brief PID and slew gains for drive (forward/backward) motions. */
struct drive_constants {
  float p = constants.drive_kp;        ///< Proportional constant.
  float i = constants.drive_ki;        ///< Integral constant.
  float d = constants.drive_kd;        ///< Derivative constant.
  float starti = constants.drive_starti; ///< Minimum distance in inches for integral to begin.
  float slew = constants.drive_slew;   ///< Limits drive acceleration in volts per 10 ms.
};

/** @brief PID and slew gains for heading correction while driving. */
struct heading_constants {
  float p = constants.heading_kp;      ///< Proportional constant.
  float i = constants.heading_ki;      ///< Integral constant.
  float d = constants.heading_kd;      ///< Derivative constant.
  float starti = constants.heading_starti; ///< Minimum distance in degrees for integral to begin.
  float slew = constants.heading_slew; ///< Limits heading correction acceleration in volts per 10 ms.
};

/** @brief PID and slew gains for turn motions. */
struct turn_constants {
  float p = constants.turn_kp;         ///< Proportional constant.
  float i = constants.turn_ki;         ///< Integral constant.
  float d = constants.turn_kd;         ///< Derivative constant.
  float starti = constants.turn_starti; ///< Minimum angle in degrees for integral to begin.
  float slew = constants.turn_slew;    ///< Limits turning acceleration in volts per 10 ms.
};

/** @brief PID and slew gains for swing motions. */
struct swing_constants {
  float p = constants.swing_kp;        ///< Proportional constant.
  float i = constants.swing_ki;        ///< Integral constant.
  float d = constants.swing_kd;        ///< Derivative constant.
  float starti = constants.swing_starti; ///< Minimum distance in degrees for integral to begin.
  float slew = constants.swing_slew;   ///< Limits swinging acceleration in volts per 10 ms.
};

/** @brief Optional parameters for Chassis::turn_to_angle(). */
struct turn_to_angle_params {
    mik::turn_direction direction = mik::turn_direction::undefined; ///< The way the robot should turn (ccw, cw, or shortest path).
    float min_voltage = constants.turn_min_voltage; ///< Minimum voltage on the drive, used for chaining movements.
    float max_voltage = constants.turn_max_voltage; ///< Max voltage on the drive out of 12.
    float exit_error = constants.turn_exit_error;   ///< Distance from target in degrees; within this error the motion exits.
    float settle_error = constants.turn_settle_error; ///< Error to be considered settled in degrees.
    float settle_time = constants.turn_settle_time; ///< Time to be considered settled in milliseconds.
    float timeout = constants.turn_timeout;         ///< Time before quitting and moving on in milliseconds.
    bool wait = true;                               ///< Yields program until motion has finished, true by default.
    turn_constants k = turn_constants{};            ///< PID and starti constants. Use k. to access constants.
};

/** @brief Optional parameters for Chassis::left_swing_to_angle() and Chassis::right_swing_to_angle(). */
struct swing_to_angle_params {
    mik::turn_direction direction = mik::turn_direction::undefined; ///< The way the robot should turn (ccw, cw, or shortest path).
    float min_voltage = constants.swing_min_voltage; ///< Minimum voltage on the drive, used for chaining movements.
    float max_voltage = constants.swing_max_voltage; ///< Max voltage on the drive out of 12.
    float opposite_voltage = constants.swing_opposite_voltage; ///< Voltage on the opposite side of the drivetrain out of 12.
    float exit_error = constants.swing_exit_error;   ///< Distance from target in degrees; within this error the motion exits.
    float settle_error = constants.swing_settle_error; ///< Error to be considered settled in degrees.
    float settle_time = constants.swing_settle_time; ///< Time to be considered settled in milliseconds.
    float timeout = constants.swing_timeout;         ///< Time before quitting and moving on in milliseconds.
    bool wait = true;                                ///< Yields program until motion has finished, true by default.
    swing_constants k = swing_constants{};           ///< PID and starti constants. Use k. to access constants.
};

/** @brief Optional parameters for Chassis::turn_to_point(). */
struct turn_to_point_params {
    mik::turn_direction direction = mik::turn_direction::undefined; ///< The way the robot should turn (ccw, cw, or shortest path).
    float angle_offset = 0;                          ///< Angle turned past the desired heading in degrees.
    float min_voltage = constants.turn_min_voltage;  ///< Minimum voltage on the drive, used for chaining movements.
    float max_voltage = constants.turn_max_voltage;  ///< Max voltage on the drive out of 12.
    float exit_error = constants.turn_exit_error;    ///< Distance from target in degrees; within this error the motion exits.
    float settle_error = constants.turn_settle_error; ///< Error to be considered settled in degrees.
    float settle_time = constants.turn_settle_time;  ///< Time to be considered settled in milliseconds.
    float timeout = constants.turn_timeout;          ///< Time before quitting and moving on in milliseconds.
    bool wait = true;                                ///< Yields program until motion has finished, true by default.
    turn_constants k = turn_constants{};             ///< PID and starti constants. Use k. to access constants.
};

/** @brief Optional parameters for Chassis::left_swing_to_point() and Chassis::right_swing_to_point(). */
struct swing_to_point_params {
    mik::turn_direction direction = mik::turn_direction::undefined; ///< The way the robot should turn (ccw, cw, or shortest path).
    float angle_offset = 0;                          ///< Angle turned past the desired heading in degrees.
    float min_voltage = constants.swing_min_voltage; ///< Minimum voltage on the drive, used for chaining movements.
    float max_voltage = constants.swing_max_voltage; ///< Max voltage on the drive out of 12.
    float opposite_voltage = constants.swing_opposite_voltage; ///< Voltage on the opposite side of the drivetrain out of 12.
    float exit_error = constants.swing_exit_error;   ///< Distance from target in degrees; within this error the motion exits.
    float settle_error = constants.swing_settle_error; ///< Error to be considered settled in degrees.
    float settle_time = constants.swing_settle_time; ///< Time to be considered settled in milliseconds.
    float timeout = constants.swing_timeout;         ///< Time before quitting and moving on in milliseconds.
    bool wait = true;                                ///< Yields program until motion has finished, true by default.
    swing_constants k = swing_constants{};           ///< PID and starti constants. Use k. to access constants.
};

/** @brief Optional parameters for Chassis::drive_distance(). */
struct drive_distance_params {
    float heading = NAN;                             ///< Desired heading in degrees. Defaults to the current heading.
    float min_voltage = constants.drive_min_voltage; ///< Minimum voltage on the drive, used for chaining movements.
    float max_voltage = constants.drive_max_voltage; ///< Max voltage on the drive out of 12.
    float heading_max_voltage = constants.heading_max_voltage; ///< Max voltage for getting to heading out of 12.
    float exit_error = constants.drive_exit_error;   ///< Distance from target in inches; within this error the motion exits.
    float settle_error = constants.drive_settle_error; ///< Error to be considered settled in inches.
    float settle_time = constants.drive_settle_time; ///< Time to be considered settled in milliseconds.
    float timeout = constants.drive_timeout;         ///< Time before quitting and moving on in milliseconds.
    bool wait = true;                                ///< Yields program until motion has finished, true by default.
    drive_constants drive_k = drive_constants{};     ///< Drive PID and starti constants. Use drive_k. to access constants.
    heading_constants heading_k = heading_constants{}; ///< Heading PID and starti constants. Use heading_k. to access constants.
};

/** @brief Optional parameters for Chassis::drive_to_point(). */
struct drive_to_point_params {
    vex::directionType direction = vex::directionType::undefined; ///< Force forward or reverse approach. Defaults to choosing automatically.
    float min_voltage = constants.drive_min_voltage; ///< Minimum voltage on the drive, used for chaining movements.
    float max_voltage = constants.drive_max_voltage; ///< Max voltage on the drive out of 12.
    float heading_max_voltage = constants.heading_max_voltage; ///< Max voltage for getting to heading out of 12.
    float exit_error = constants.drive_exit_error;   ///< Distance from target in inches; within this error the motion exits.
    float settle_error = constants.drive_settle_error; ///< Error to be considered settled in inches.
    float settle_time = constants.drive_settle_time; ///< Time to be considered settled in milliseconds.
    float timeout = constants.drive_timeout;         ///< Time before quitting and moving on in milliseconds.
    bool wait = true;                                ///< Yields program until motion has finished, true by default.
    drive_constants drive_k = drive_constants{};     ///< Drive PID and starti constants. Use drive_k. to access constants.
    heading_constants heading_k = heading_constants{}; ///< Heading PID and starti constants. Use heading_k. to access constants.
};

/** @brief Optional parameters for Chassis::drive_to_pose() (boomerang controller). */
struct drive_to_pose_params {
    vex::directionType direction = vex::directionType::undefined; ///< Force forward or reverse approach. Defaults to choosing automatically.
    float lead = constants.boomerang_lead;           ///< Constant scale factor that determines how far away the carrot point is.
    float drift = constants.boomerang_drift;         ///< Limits speed while turning. Higher values increase lateral speed.
    float min_voltage = constants.drive_min_voltage; ///< Minimum voltage on the drive, used for chaining movements.
    float max_voltage = constants.drive_max_voltage; ///< Max voltage on the drive out of 12.
    float heading_max_voltage = constants.heading_max_voltage; ///< Max voltage for getting to heading out of 12.
    float exit_error = constants.drive_exit_error;   ///< Distance from target in inches; within this error the motion exits.
    float settle_error = constants.drive_settle_error; ///< Error to be considered settled in inches.
    float settle_time = constants.drive_settle_time; ///< Time to be considered settled in milliseconds.
    float timeout = constants.drive_timeout;         ///< Time before quitting and moving on in milliseconds.
    bool wait = true;                                ///< Yields program until motion has finished, true by default.
    drive_constants drive_k = drive_constants{};     ///< Drive PID and starti constants. Use drive_k. to access constants.
    heading_constants heading_k = heading_constants{}; ///< Heading PID and starti constants. Use heading_k. to access constants.
};

/** @brief Optional parameters for Chassis::holonomic_to_pose(). */
struct holonomic_to_pose_params {
    float min_voltage = constants.drive_min_voltage; ///< Minimum voltage on the drive, used for chaining movements.
    float max_voltage = constants.drive_max_voltage; ///< Max voltage on the drive out of 12.
    float heading_max_voltage = constants.heading_max_voltage; ///< Max voltage for heading correction out of 12.
    float exit_error = constants.drive_exit_error;   ///< Distance from target in inches; within this error the motion exits.
    float settle_error = constants.drive_settle_error; ///< Drive error to be considered settled in inches.
    float settle_time = constants.drive_settle_time; ///< Drive time to be considered settled in milliseconds.
    float turn_settle_error = constants.turn_settle_error; ///< Turn error to be considered settled in degrees.
    float turn_settle_time = constants.turn_settle_time; ///< Turn time to be considered settled in milliseconds.
    float timeout = constants.drive_timeout;         ///< Time before quitting and moving on in milliseconds.
    bool wait = true;                                ///< Yields program until motion has finished, true by default.
    drive_constants drive_k = drive_constants{};     ///< Drive PID and starti constants. Use drive_k. to access constants.
    heading_constants heading_k = heading_constants{}; ///< Heading PID and starti constants. Use heading_k. to access constants.
};

/** @brief Optional parameters for Chassis::strafe_distance(). */
struct strafe_distance_params {
    float heading = NAN;                             ///< Desired heading in degrees. Defaults to the current heading.
    float min_voltage = constants.drive_min_voltage; ///< Minimum voltage on the drive, used for chaining movements.
    float max_voltage = constants.drive_max_voltage; ///< Max voltage on the drive out of 12.
    float heading_max_voltage = constants.heading_max_voltage; ///< Max voltage for getting to heading out of 12.
    float exit_error = constants.drive_exit_error;   ///< Distance from target in inches; within this error the motion exits.
    float settle_error = constants.drive_settle_error; ///< Error to be considered settled in inches.
    float settle_time = constants.drive_settle_time; ///< Time to be considered settled in milliseconds.
    float timeout = constants.drive_timeout;         ///< Time before quitting and moving on in milliseconds.
    bool wait = true;                                ///< Yields program until motion has finished, true by default.
    drive_constants drive_k = drive_constants{};     ///< Drive PID and starti constants. Use drive_k. to access constants.
    heading_constants heading_k = heading_constants{}; ///< Heading PID and starti constants. Use heading_k. to access constants.
};