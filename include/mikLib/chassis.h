#pragma once

#include "vex.h"

// Drive motions are at end of file

struct drive_distance_params;
struct turn_to_angle_params;
struct swing_to_angle_params;
struct drive_to_point_params;
struct drive_to_pose_params;
struct turn_to_point_params;
struct swing_to_point_params;
struct follow_path_params;
struct drive_constants;
struct heading_constants;
struct turn_constants;
struct swing_constants;

class Chassis {
public:
    /** ALL CONSTANTS USED IN MOTIONS. */

    float drive_min_voltage = 0; // Minimum voltage on the drive, used for chaining movements.
    float drive_max_voltage; // Max voltage out of 12.

    float drive_kp; // Proportional constant.
    float drive_ki; // Integral constant.
    float drive_kd; // Derivative constant.
    float drive_starti; // Minimum distance in inches for integral to begin

    float drive_settle_error; // Error to be considered settled in degrees.
    float drive_settle_time; // Time to be considered settled in milliseconds.
    float drive_timeout; // Time before quitting and move on in milliseconds.

    float heading_max_voltage; // Max voltage out of 12.
    float heading_kp; // Proportional constant.
    float heading_ki; // Integral constant.
    float heading_kd; // Derivative constant.
    float heading_starti; // Minimum distance in degrees for integral to begin

    float turn_min_voltage = 0; // Minimum voltage for turning out of 12.
    float turn_max_voltage; // Max voltage out of 12.

    float turn_kp; // Proportional constant.
    float turn_ki; // Integral constant.
    float turn_kd; // Derivative constant.
    float turn_starti; // Minimum angle in degrees for integral to begin.

    float turn_settle_error; // Error to be considered settled in degrees.
    float turn_settle_time; // Time to be considered settled in milliseconds.
    float turn_timeout; // Time before quitting and move on in milliseconds.

    float swing_min_voltage = 0; // Minimum voltage for swinging out of 12.
    float swing_max_voltage; // Max voltage out of 12.

    float swing_kp; // Proportional constant.
    float swing_ki; // Integral constant.
    float swing_kd; // Derivative constant.
    float swing_starti; // Minimum distance in degrees for integral to begin
    
    float swing_settle_error; // Error to be considered settled in degrees.
    float swing_settle_time; // Time to be considered settled in milliseconds.
    float swing_timeout; // Time before quitting and move on in milliseconds.
    
    float boomerang_lead; // Constant scale factor that determines how far away the carrot point is. 
    float boomerang_setback; // Distance in inches from target by which the carrot is always pushed back.

    float pursuit_lookahead_distance; // Radius of the look-ahead circle, in inches.

    float control_throttle_deadband; // Deadband percent for the throttle axis.
    float control_throttle_min_output; // Minimum throttle output percent after deadband.
    float control_throttle_curve_gain; // Expo gain for throttle axis (1 linear, 1.06 very curvy).
    
    float control_turn_deadband; // Deadband percent for the turn axis.
    float control_turn_min_output; // Minimum turn output percent after deadband.
    float control_turn_curve_gain; // Expo gain for turn axis (1 linear, 1.06 very curvy).

    /**
     * @param left_drive  Motor group on the robot's left side.
     * @param right_drive Motor group on the robot's right side.
     * @param inertial_port Inertial sensor port (1-21).
     * @param inertial_scale Scale factor applied to raw gyro angles to correct drift.
     * @param forward_tracker_port Forward tracker rotation sensor port (1-21).
     * @param forward_tracker_diameter Forward tracking‑wheel diameter (in inches).
     * @param forward_tracker_center_distance Distance from the chassis centre to the forward tracker (in).
     * @param sideways_tracker_port Sideways tracker rotation sensor port (1-21).
     * @param sideways_tracker_diameter Sideways tracking‑wheel diameter (in inches).
     * @param sideways_tracker_center_distance Distance from the chassis centre to the sideways tracker (in).
     * @param reset_sensors Distance sensors parallel to a robot face that can reset odometry axes.
     */
    Chassis(mik::motor_group left_drive, mik::motor_group right_drive, int inertial_port, float inertial_scale, int forward_tracker_port, float forward_tracker_diameter, float forward_tracker_center_distance, int sideways_tracker_port, float sideways_tracker_diameter, float sideways_tracker_center_distance, mik::distance_reset reset_sensors);

    /**
     * @brief Reset default joystick control constants for throttle and turn.
     * Try it out in desmos https://www.desmos.com/calculator/umicbymbnl.
     *
     * @param control_throttle_deadband Deadband percent for the throttle axis.
     * @param control_throttle_min_output Minimum throttle output percent after deadband.
     * @param control_throttle_curve_gain Expo gain for throttle axis (1 linear, 1.06 very curvy).
     * @param control_turn_deadband  Deadband percent for the turn axis.
     * @param control_turn_min_output Minimum turn output percent after deadband.
     * @param control_turn_curve_gain Expo gain for turn axis.
     */
    void set_control_constants(float control_throttle_deadband, float control_throttle_min_output, float control_throttle_curve_gain, float control_turn_deadband, float control_turn_min_output, float control_turn_curve_gain);

    /**
     * @brief Resets default turn constants.
     * Turning includes turn_to_angle() and turn_to_point().
     * 
     * @param turn_max_voltage Max voltage out of 12.
     * @param turn_kp Proportional constant.
     * @param turn_ki Integral constant.
     * @param turn_kd Derivative constant.
     * @param turn_starti Minimum angle in degrees for integral to begin.
     */
    void set_turn_constants(float turn_max_voltage, float turn_kp, float turn_ki, float turn_kd, float turn_starti);

    /**
     * @brief Resets default drive constants.
     * Driving includes drive_distance(), drive_to_point(), drive_to_pose(), and follow_path()
     * 
     * @param drive_max_voltage Max voltage out of 12.
     * @param drive_kp Proportional constant.
     * @param drive_ki Integral constant.
     * @param drive_kd Derivative constant.
     * @param drive_starti Minimum distance in inches for integral to begin.
     */
    void set_drive_constants(float drive_max_voltage, float drive_kp, float drive_ki, float drive_kd, float drive_starti);
    /**
     * @brief Resets default heading constants.
     * Heading control keeps the robot facing the right direction
     * and is part of drive_distance(), drive_to_point(), drive_to_pose(), and follow_path()
     * 
     * @param heading_max_voltage Max voltage out of 12.
     * @param heading_kp Proportional constant.
     * @param heading_ki Integral constant.
     * @param heading_kd Derivative constant.
     * @param heading_starti Minimum angle in degrees for integral to begin.
     */
    void set_heading_constants(float heading_max_voltage, float heading_kp, float heading_ki, float heading_kd, float heading_starti);

    /**
     * @brief Resets default swing constants.
     * Swing control holds one side of the drive still and turns with the other.
     * Used in left_swing_to_angle(), right_swing_to_angle(), right_swing_to_point() and left_swing_to_point.
     * 
     * @param swing_max_voltage Max voltage out of 12.
     * @param swing_kp Proportional constant.
     * @param swing_ki Integral constant.
     * @param swing_kd Derivative constant.
     * @param swing_starti Minimum angle in degrees for integral to begin.
     */
    void set_swing_constants(float swing_max_voltage, float swing_kp, float swing_ki, float swing_kd, float swing_starti);

    /**
     * @brief Resets default turn exit conditions.
     * The robot exits when error is less than settle_error for a duration of settle_time, 
     * or if the function has gone on for longer than timeout.
     * 
     * @param turn_settle_error Error to be considered settled in degrees.
     * @param turn_settle_time Time to be considered settled in milliseconds.
     * @param turn_timeout Time before quitting and move on in milliseconds.
     */
    void set_turn_exit_conditions(float turn_settle_error, float turn_settle_time, float turn_timeout);

    /**
     * @brief Resets default drive exit conditions.
     * The robot exits when error is less than settle_error for a duration of settle_time, 
     * or if the function has gone on for longer than timeout.
     * 
     * @param drive_settle_error Error to be considered settled in inches.
     * @param drive_settle_time Time to be considered settled in milliseconds.
     * @param drive_timeout Time before quitting and move on in milliseconds.
     */
    void set_drive_exit_conditions(float drive_settle_error, float drive_settle_time, float drive_timeout);

    /**
     * @brief Resets default swing exit conditions.
     * The robot exits when error is less than settle_error for a duration of settle_time, 
     * or if the function has gone on for longer than timeout.
     * 
     * @param swing_settle_error Error to be considered settled in degrees.
     * @param swing_settle_time Time to be considered settled in milliseconds.
     * @param swing_timeout Time before quitting and move on in milliseconds.
     */
    void set_swing_exit_conditions(float swing_settle_error, float swing_settle_time, float swing_timeout);

    /**
     * @brief Resets the tracking offsets. Used for when robots center of rotation changes, ex: clamping onto a large game object.
     * @param forward_tracker_center_distance Distance from the chassis centre to the forward tracker (in).
     * @param sideways_tracker_center_distance Distance from the chassis centre to the sideways tracker (in).
     */
    void set_tracking_offsets(float forward_tracker_center_distance, float sideways_tracker_center_distance);

    /**
     * @brief Globally sets the brake mode for both drive motor groups.
     * @param mode coast, brake, hold
     */
    void set_brake_type(vex::brakeType brake);

    /** @brief Yield to the scheduler until motion is finished. */
    void wait();

    /** 
     * @brief Yield to the scheduler until the current motion the robots in has traveled specifed units. 
     * Drive motions use inches, turn motions use degrees.
     * @param units units of motion (inches or degrees).
    */
    void wait_until(float units);

    /** @return True if the robot is in motion. */
    bool is_in_motion();

    /** @brief Cancels the current motion the robot is in. Useful for chaining movements faster */
    void cancel_motion();

    /**
     * @brief Drives each side of the chassis at the specified voltage.
     * 
     * @param left_voltage Voltage (0-12).
     * @param right_voltage Voltage (0-12).
     */
    void drive_with_voltage(float left_voltage, float right_voltage);

    /**
     * @brief Stops both sides of the drivetrain.
     * @param mode coast, brake, hold
     */    
    void stop_drive(vex::brakeType brake);

    /** @return Field‑relative inertial heading (deg, 0‑360). */
    float get_absolute_heading();
    
    /** @brief Mirror all subsequent turn angles, affecting turn_to_angle(), drive_to_pose(), and set_coordinates(). 
     * Useful on opposite field sides. Also changes turn directions to their inverse, cw->ccw, ccw->cw. 
    */
    void mirror_all_auton_angles();
    
    /** @brief Mirror all subsequent x-coordinates, affecting drive_to_point(), turn_to_point(), drive_to_pose(), and set_coordinates().
     * Useful on opposite field sides. 
    */
    void mirror_all_auton_x_pos();

    /** @brief Disables mirroring for x_pos, y_pos and angles.
    */
    void disable_mirroring();
    
    /** @brief Mirror all subsequent y-coordinates, affecting drive_to_point(), turn_to_point(), drive_to_pose(), and set_coordinates().
     * Useful on opposite field sides. 
    */
    void mirror_all_auton_y_pos();
    
    /** @return True if angles have been mirrored */
    bool angles_mirrored();

    /** @return True if x coordinates have been mirrored */
    bool x_pos_mirrored();
    
    /** @return True if y coordinates have been mirrored */
    bool y_pos_mirrored();

    /**
     * @brief Turns the robot to a field-centric angle.
     * Optimizes direction, so it turns whichever way is closer to the 
     * current heading of the robot, unless a turn direction is specified.
     * 
     * @param angle Desired angle in degrees.
     * @param turn_direction The way the robot should turn, (ccw, cw, or shortest path)
     * @param min_voltage Minimum voltage on the drive, used for chaining movements.
     * @param max_voltage Max voltage on the drive out of 12.
     * @param settle_error Error to be considered settled in degrees.
     * @param settle_time Time to be considered settled in milliseconds.
     * @param timeout Time before quitting and move on in milliseconds.
     * @param k PID and starti constants. Do k. to access constants.
     * @param wait Yields program until motion has finished, true by default.
     */
    void turn_to_angle(float angle, const turn_to_angle_params& p);

    /**
     * @brief Drives the robot a given distance with a given heading.
     * Drive distance does not optimize for direction, so it won't try
     * to drive at the opposite heading from the one given to get there faster.
     * You can control the heading, but if you choose not to, it will drive with the
     * heading it's currently facing. It uses forward tracker to find distance traveled. 
     * Use negative distance to go backwards
     * 
     * @param distance Desired distance in inches.
     * @param heading Desired heading in degrees.
     * @param min_voltage Minimum voltage on the drive, used for chaining movements.
     * @param max_voltage Max voltage on the drive out of 12.
     * @param heading_max_voltage Max voltage for getting to heading out of 12.
     * @param settle_error Error to be considered settled in inches.
     * @param settle_time Time to be considered settled in milliseconds.
     * @param timeout Time before quitting and move on in milliseconds.
     * @param drive_k Drive PID and starti constants. Do drive_k. to access constants.
     * @param heading_k Heading PID and starti constants. Do heading_k. to access constants.
     * @param wait Yields program until motion has finished, true by default.
     */
    void drive_distance(float distance, const drive_distance_params& p);

    /**
     * Turns to a given angle with the left side of the drivetrain.
     * Like turn_to_angle(), is optimized for turning the shorter
     * direction, unless a turn direction is specified
     * 
     * @param angle Desired angle in degrees.
     * @param turn_direction The way the robot should turn, (ccw, cw, or shortest path)
     * @param min_voltage Minimum voltage on the drive, used for chaining movements.
     * @param max_voltage Max voltage on the drive out of 12.
     * @param settle_error Error to be considered settled in degrees.
     * @param settle_time Time to be considered settled in milliseconds.
     * @param timeout Time before quitting and move on in milliseconds.
     * @param k PID and starti constants. Do k. to access constants.
     * @param wait Yields program until motion has finished, true by default.
     */
    void left_swing_to_angle(float angle, const swing_to_angle_params& p);

    /**
     * Turns to a given angle with the right side of the drivetrain.
     * Like turn_to_angle(), is optimized for turning the shorter
     * direction, unless a turn direction is specified
     * 
     * @param angle Desired angle in degrees.
     * @param turn_direction The way the robot should turn, (ccw, cw, or shortest path)
     * @param min_voltage Minimum voltage on the drive, used for chaining movements.
     * @param max_voltage Max voltage on the drive out of 12.
     * @param settle_error Error to be considered settled in degrees.
     * @param settle_time Time to be considered settled in milliseconds.
     * @param timeout Time before quitting and move on in milliseconds.
     * @param k PID and starti constants. Do k. to access constants.
     * @param wait Yields program until motion has finished, true by default.
     */
    void right_swing_to_angle(float angle, const swing_to_angle_params& p);

    /** @return Position of the forward tracker in inches */ 
    float get_ForwardTracker_position();
    /** @return Position of the sideways tracker in inches */ 
    float get_SidewaysTracker_position();

    /**
     * @brief Resets the robot's coordinates and heading.
     * This is for odom-using robots to specify where the bot is at the beginning
     * of the match.
     * 
     * @param X_position Robot's x in inches.
     * @param Y_position Robot's y in inches.
     * @param orientation_deg Desired heading in degrees.
     */
    void set_coordinates(float X_position, float Y_position, float orientation_deg);

    /**
     * @brief Resets the robot's heading.
     * For example, at the beginning of auton, if your robot starts at
     * 45 degrees, so set_heading(45) and the robot will know which way 
     * it's facing.
     * 
     * @param orientation_deg Desired heading in degrees.
     */
    void set_heading(float orientation_deg);

    /** @brief Background task for updating the odometry. */
    void position_track();
    /** @brief Background task for updating the odometry. */
    static int position_track_task();

    /** @return The robot's x position in inches */
    float get_X_position();
    /** @return The robot's y position in inches */
    float get_Y_position();

    /** 
     * @brief Resets an X or Y position of the robot based on the heading and distance from a wall.
     * The distance sensor must be facing the desired wall with no obstruction in order to work.
     * Choosing to reset off a top or bottom wall will reset the robots y positon, and a left or right
     * wall resetting the robots x position.
     * 
     * @param sensor_pos The side of the robot that the distance sensor is mounted.
     * @param wall_pos The wall that is being looked at by desired distance sensor.
     * @param max_reset_distance The maxiumum allowed of distance in inches that an odom axis can be changed.
     * 
     * @return True if the desired axis was reset successfully.
     */
    bool reset_axis(mik::distance_position sensor_pos, mik::wall_position wall_pos, float max_reset_distance);
    
    /**
     * @brief Turns to a specified point on the field.
     * Functions similarly to turn_to_angle() except with a point. The
     * angle_offset parameter turns the robot extra relative to the 
     * desired target. For example, if you want the back of your robot
     * to point at (36, 42), you would run turn_to_point(36, 42, {.angle_offset = 180}).
     * 
     * @param X_position Desired x position in inches.
     * @param Y_position Desired y position in inches.
     * @param angle_offset Angle turned past the desired heading in degrees.
     * @param turn_direction The way the robot should turn, (ccw, cw, or shortest path)
     * @param min_voltage Minimum voltage on the drive, used for chaining movements.
     * @param max_voltage Max voltage on the drive out of 12.
     * @param settle_error Error to be considered settled in degrees.
     * @param settle_time Time to be considered settled in milliseconds.
     * @param timeout Time before quitting and move on in milliseconds.
     * @param k PID and starti constants. Do k. to access constants.
     * @param wait Yields program until motion has finished, true by default.
     */
    void turn_to_point(float X_position, float Y_position, const turn_to_point_params& p);
    
    /**
     * @brief Turns to a specified point on the field with the left side of the drivetrain.
     * Functions similarly to left_swing_to_angle() except with a point. The
     * angle_offset parameter turns the robot extra relative to the 
     * desired target. For example, if you want the back of your robot
     * to point at (36, 42), you would run left_swing_to_point(36, 42, {.angle_offset = 180}).
     * 
     * @param X_position Desired x position in inches.
     * @param Y_position Desired y position in inches.
     * @param angle_offset Angle turned past the desired heading in degrees.
     * @param turn_direction The way the robot should turn, (ccw, cw, or shortest path)
     * @param min_voltage Minimum voltage on the drive, used for chaining movements.
     * @param max_voltage Max voltage on the drive out of 12.
     * @param settle_error Error to be considered settled in degrees.
     * @param settle_time Time to be considered settled in milliseconds.
     * @param timeout Time before quitting and move on in milliseconds.
     * @param k PID and starti constants. Do k. to access constants.
     * @param wait Yields program until motion has finished, true by default.
     */
    void left_swing_to_point(float X_position, float Y_position, const swing_to_point_params& p);

    /**
     * @brief Turns to a specified point on the field with the right side of the drivetrain.
     * Functions similarly to right_swing_to_angle() except with a point. The
     * angle_offset parameter turns the robot extra relative to the 
     * desired target. For example, if you want the back of your robot
     * to point at (36, 42), you would run right_swing_to_point(36, 42, {.angle_offset = 180}).
     * 
     * @param X_position Desired x position in inches.
     * @param Y_position Desired y position in inches.
     * @param angle_offset Angle turned past the desired heading in degrees.
     * @param turn_direction The way the robot should turn, (ccw, cw, or shortest path)
     * @param min_voltage Minimum voltage on the drive, used for chaining movements.
     * @param max_voltage Max voltage on the drive out of 12.
     * @param settle_error Error to be considered settled in degrees.
     * @param settle_time Time to be considered settled in milliseconds.
     * @param timeout Time before quitting and move on in milliseconds.
     * @param k PID and starti constants. Do k. to access constants.
     * @param wait Yields program until motion has finished, true by default.
     */
    void right_swing_to_point(float X_position, float Y_position, const swing_to_point_params& p);

    /**
     * @brief Drives to a specified point on the field.
     * Uses the double-PID method, with one for driving and one for heading correction.
     * The drive error is the euclidean distance to the desired point, and the heading error
     * is the turn correction from the current heading to the desired point. Uses optimizations
     * like driving backwards whenever possible and scaling the drive output with the cosine
     * of the angle to the point.
     * 
     * @param X_position Desired x position in inches.
     * @param Y_position Desired y position in inches.
     * @param min_voltage Minimum voltage on the drive, used for chaining movements.
     * @param max_voltage Max voltage on the drive out of 12.
     * @param heading_max_voltage Max voltage for getting to heading out of 12.
     * @param settle_error Error to be considered settled in inches.
     * @param settle_time Time to be considered settled in milliseconds.
     * @param timeout Time before quitting and move on in milliseconds.
     * @param drive_k Drive PID and starti constants. Do drive_k. to access constants.
     * @param heading_k Heading PID and starti constants. Do heading_k. to access constants.
     * @param wait Yields program until motion has finished, true by default.
     */
    void drive_to_point(float X_position, float Y_position, const drive_to_point_params& p);
    
    /**
     * @brief Drives to a specified point and orientation on the field.
     * Uses a boomerang controller. The carrot point is back from the target
     * by the same distance as the robot's distance to the target, times the lead. The
     * robot always tries to go to the carrot, which is constantly moving, and the
     * robot eventually gets into position. The heading correction is optimized to only
     * try to reach the correct angle when drive error is low, and the robot will drive 
     * backwards to reach a pose if it's faster. .5 is a reasonable value for the lead. 
     * The setback parameter is used to glide into position more effectively. It is
     * the distance back from the target that the robot tries to drive to first.
     * Try it out in a desmos simulation https://www.desmos.com/calculator/sptjw5szex.
     * 
     * @param X_position Desired x position in inches.
     * @param Y_position Desired y position in inches.
     * @param angle Desired orientation in degrees.
     * @param lead Constant scale factor that determines how far away the carrot point is. 
     * @param setback Distance in inches from target by which the carrot is always pushed back.
     * @param min_voltage Minimum voltage on the drive, used for chaining movements.
     * @param max_voltage Max voltage on the drive out of 12.
     * @param heading_max_voltage Max voltage for getting to heading out of 12.
     * @param settle_error Error to be considered settled in inches.
     * @param settle_time Time to be considered settled in milliseconds.
     * @param timeout Time before quitting and move on in milliseconds.
     * @param drive_k Drive PID and starti constants. Do drive_k. to access constants.
     * @param heading_k Heading PID and starti constants. Do heading_k. to access constants.
     * @param wait Yields program until motion has finished, true by default.
     */
    void drive_to_pose(float X_position, float Y_position, float angle, const drive_to_pose_params& p);

    /** @brief Drives the robot along defined waypoints.
     * Waypoints can be obtained from https://path.jerryio.com/.
     * 
     * Algorithm is from Taolib and is very similar to a pure pursuit controler.
     * It continously finds the best intersection between a look-ahead circle
     * (whose radius is `lookahead_distance`) and the current path segment,
     * then goes to that point with pair of PIDs, one regulating
     * forward motion and the other correcting heading. The larger the lookahead
     * the faster but less accurate the robot will follow the path.
     * 
     * @param path The vector of points that the robot will follow.
     * @param lookahead_distance Radius of the look-ahead circle, in inches.
     * @param min_voltage Minimum voltage on the drive, used for chaining movements.
     * @param max_voltage Max voltage on the drive out of 12.
     * @param heading_max_voltage Max voltage for getting to heading out of 12.
     * @param settle_error Error to be considered settled in inches.
     * @param settle_time Time to be considered settled in milliseconds.
     * @param timeout Time before quitting and move on in milliseconds.
     * @param drive_k Drive PID and starti constants. Do drive_k. to access constants.
     * @param heading_k Heading PID and starti constants. Do heading_k. to access constants.
     * @param wait Yields program until motion has finished, true by default.
     */
    void follow_path(std::vector<point> path, const follow_path_params& p);
    
    /** @brief disables joystick control of the drivetrain */
    void disable_control();
    /** @brief enables joystick control of the drivetrain */
    void enable_control();

    // Drive control modes
    void split_arcade();
    void split_arcade_curved();
    void tank();
    void tank_curved();

    /**
     * @brief Dispatch joystick input based on the selected drive mode.
     * @param dm Drive mode enumeration.
     */
    void control(mik::drive_mode dm);
    
    vex::rotation forward_tracker;
    vex::rotation sideways_tracker;
    vex::inertial inertial;
    
    mik::motor_group left_drive;
    mik::motor_group right_drive; 

    mik::distance_reset reset_sensors;

    bool motion_running;
    float distance_traveled;
    
    bool position_tracking;
    bool control_disabled;
  
    mik::drive_mode selected_drive_mode = mik::drive_mode::SPLIT_ARCADE;

    /** SET POINTS. USED FOR GRAPHING AND ACCESSING CHASSIS DATA IN ANOTHER TASK */

    float desired_angle = 0;
    float desired_distance = 0;
    float desired_heading = 0;
    float desired_X_position = 0;
    float desired_Y_position = 0;
    float desired_angle_offset = 0;
    std::vector<point> desired_path{};

private:
    bool angles_mirrored_ = false;
    bool x_pos_mirrored_ = false;
    bool y_pos_mirrored_ = false;

    float inertial_scale;

    float forward_tracker_diameter;
    float forward_tracker_center_distance;
    float forward_tracker_inch_to_deg_ratio;

    float sideways_tracker_diameter;
    float sideways_tracker_center_distance;
    float sideways_tracker_inch_to_deg_ratio;

    PID pid; // Primary PID controller.
    PID pid_2; // Secondary PID controller (heading).
    odom odom;

    vex::task odom_task;
    vex::task drive_task;
};

extern Chassis chassis;

struct drive_constants {
  float p = chassis.drive_kp;
  float i = chassis.drive_ki;
  float d = chassis.drive_kd;
  float starti = chassis.drive_starti;
};

struct heading_constants {
  float p = chassis.heading_kp;
  float i = chassis.heading_ki;
  float d = chassis.heading_kd;
  float starti = chassis.heading_starti;
};

struct turn_constants {
  float p = chassis.turn_kp;
  float i = chassis.turn_ki;
  float d = chassis.turn_kd;
  float starti = chassis.turn_starti;
};

struct swing_constants {
  float p = chassis.swing_kp;
  float i = chassis.swing_ki;
  float d = chassis.swing_kd;
  float starti = chassis.swing_starti;
};

struct drive_distance_params {
    float heading = chassis.get_absolute_heading();
    float min_voltage = chassis.drive_min_voltage;
    float max_voltage = chassis.drive_max_voltage;
    float heading_max_voltage = chassis.heading_max_voltage;
    float settle_error = chassis.drive_settle_error;
    float settle_time = chassis.drive_settle_time;
    float timeout = chassis.drive_timeout;
    bool wait = true;
    drive_constants drive_k = drive_constants{};
    heading_constants heading_k = heading_constants{};
};

struct turn_to_angle_params {
    mik::direction turn_direction = mik::direction::FASTEST;
    float min_voltage = chassis.turn_min_voltage;
    float max_voltage = chassis.turn_max_voltage;
    float settle_error = chassis.turn_settle_error;
    float settle_time = chassis.turn_settle_time;
    float timeout = chassis.turn_timeout;
    bool wait = true;
    turn_constants k = turn_constants{}; 
};

struct swing_to_angle_params {
    mik::direction turn_direction = mik::direction::FASTEST;
    float min_voltage = chassis.swing_min_voltage;
    float max_voltage = chassis.swing_max_voltage;
    float settle_error = chassis.swing_settle_error;
    float settle_time = chassis.swing_settle_time;
    float timeout = chassis.swing_timeout;
    bool wait = true;
    swing_constants k = swing_constants{};
};

struct drive_to_point_params {
    float min_voltage = chassis.drive_min_voltage;
    float max_voltage = chassis.drive_max_voltage;
    float heading_max_voltage = chassis.heading_max_voltage;
    float settle_error = chassis.drive_settle_error;
    float settle_time = chassis.drive_settle_time;
    float timeout = chassis.drive_timeout;
    bool wait = true;
    drive_constants drive_k = drive_constants{};
    heading_constants heading_k = heading_constants{};
};

struct drive_to_pose_params {
    float lead = chassis.boomerang_lead;
    float setback = chassis.boomerang_setback;
    float min_voltage = chassis.drive_min_voltage;
    float max_voltage = chassis.drive_max_voltage;
    float heading_max_voltage = chassis.heading_max_voltage;
    float settle_error = chassis.drive_settle_error;
    float settle_time = chassis.drive_settle_time;
    float timeout = chassis.drive_timeout;
    bool wait = true;
    drive_constants drive_k = drive_constants{};
    heading_constants heading_k = heading_constants{};
};

struct turn_to_point_params {
    mik::direction turn_direction = mik::direction::FASTEST;
    float angle_offset = 0;
    float min_voltage = chassis.drive_min_voltage;
    float max_voltage = chassis.turn_max_voltage;
    float settle_error = chassis.turn_settle_error;
    float settle_time = chassis.turn_settle_time;
    float timeout = chassis.turn_timeout;
    bool wait = true;
    turn_constants k = turn_constants{};   
};

struct swing_to_point_params {
    mik::direction turn_direction = mik::direction::FASTEST;
    float angle_offset = 0;
    float min_voltage = chassis.swing_min_voltage;
    float max_voltage = chassis.swing_max_voltage;
    float settle_error = chassis.swing_settle_error;
    float settle_time = chassis.swing_settle_time;
    float timeout = chassis.swing_timeout;
    bool wait = true;
    swing_constants k = swing_constants{};
};

struct follow_path_params {
    float lookahead_distance = chassis.pursuit_lookahead_distance;
    float min_voltage = chassis.drive_min_voltage;
    float max_voltage = chassis.drive_max_voltage;
    float heading_max_voltage = chassis.heading_max_voltage;
    float settle_error = chassis.drive_settle_error;
    float settle_time = chassis.drive_settle_time;
    float timeout = chassis.drive_timeout;
    bool wait = true;
    drive_constants drive_k = drive_constants{};
    heading_constants heading_k = heading_constants{};
};

extern drive_distance_params g_drive_distance_params_buffer;
extern turn_to_angle_params g_turn_to_angle_params_buffer;
extern swing_to_angle_params g_swing_to_angle_params_buffer;
extern turn_to_point_params g_turn_to_point_params_buffer;
extern swing_to_point_params g_swing_to_point_params_buffer;
extern drive_to_point_params g_drive_to_point_params_buffer;
extern drive_to_pose_params g_drive_to_pose_params_buffer;
extern follow_path_params g_follow_path_params_buffer;

inline void Chassis::drive_distance(float distance, const drive_distance_params& p = drive_distance_params{}) {
    desired_distance = distance;
    desired_heading = p.heading;
    g_drive_distance_params_buffer = p;

    pid = PID(distance, p.drive_k.p, p.drive_k.i, p.drive_k.d, p.drive_k.starti, p.settle_error, p.settle_time, p.timeout);
    pid_2 = PID(reduce_negative_180_to_180(p.heading - get_absolute_heading()), p.heading_k.p, p.heading_k.i, p.heading_k.d, p.heading_k.starti);
    
    motion_running = true;
    distance_traveled = 0;

    drive_task = vex::task([](){
        const float distance = chassis.desired_distance;
        const float heading = chassis.desired_heading;
        drive_distance_params p = g_drive_distance_params_buffer;

        float drive_start_position = chassis.get_ForwardTracker_position();
        float current_position = drive_start_position;

        float drive_error = distance + drive_start_position - current_position;
        float prev_drive_error = drive_error;

        while (chassis.pid.is_settled() == false) {
            current_position = chassis.get_ForwardTracker_position();
    
            drive_error = distance + drive_start_position - current_position;
            chassis.distance_traveled += std::abs(drive_error - prev_drive_error);
            prev_drive_error = drive_error;

            float heading_error = reduce_negative_180_to_180(heading - chassis.get_absolute_heading());
            float drive_output = chassis.pid.compute(drive_error);
            float heading_output = chassis.pid_2.compute(heading_error);
    
            drive_output = clamp(drive_output, -p.max_voltage, p.max_voltage);
            heading_output = clamp(heading_output, -p.heading_max_voltage, p.heading_max_voltage);
            
            drive_output = clamp_min_voltage(drive_output, p.min_voltage);

            chassis.drive_with_voltage(drive_output + heading_output, drive_output - heading_output);
            vex::task::sleep(10);
        }

        chassis.motion_running = false;
        if (p.min_voltage == 0) { chassis.stop_drive(hold); }

        return 0;
    });
    if (p.wait) {
        this->wait();
    }
}

inline void Chassis::turn_to_angle(float angle, const turn_to_angle_params& p = turn_to_angle_params{}) {
    desired_angle = mirror_angle(angle, angles_mirrored_);
    g_turn_to_angle_params_buffer = p;

    pid = PID(angle_error(angle - chassis.get_absolute_heading(), mirror_direction(p.turn_direction, chassis.angles_mirrored_)), p.k.p, p.k.i, p.k.d, p.k.starti, p.settle_error, p.settle_time, p.timeout);
    
    motion_running = true;
    distance_traveled = 0;

    drive_task = vex::task([](){
        const float angle = chassis.desired_angle;
        const turn_to_angle_params p = g_turn_to_angle_params_buffer;

        bool crossed = false;
        float raw_error = angle_error(angle - chassis.get_absolute_heading());
        float error = angle_error(angle - chassis.get_absolute_heading(), mirror_direction(p.turn_direction, chassis.angles_mirrored_));
        float prev_error = error;
        float prev_raw_error = raw_error;

        while(chassis.pid.is_settled() == false) {
            raw_error = angle_error(angle - chassis.get_absolute_heading());
            if (sign(raw_error) != sign(prev_raw_error)) {
                crossed = true;
            }
            prev_raw_error = raw_error;
            
            if (crossed) {
                error = raw_error;
            } else {
                error = angle_error(angle - chassis.get_absolute_heading(), mirror_direction(p.turn_direction, chassis.angles_mirrored_));
            }
            
            if (p.min_voltage != 0 && sign(error) != sign(prev_error)) break;
            chassis.distance_traveled += std::abs(error - prev_error);

            prev_error = error;

            float output = chassis.pid.compute(error);
            output = clamp(output, -p.max_voltage, p.max_voltage);
            output = clamp_min_voltage(output, p.min_voltage);

            chassis.drive_with_voltage(output, -output);
            vex::task::sleep(10); 
        }
    
        chassis.motion_running = false;
        if (p.min_voltage == 0) { chassis.stop_drive(hold); }

        return 0;
    });
    if (p.wait) { this->wait(); }
}

inline void Chassis::left_swing_to_angle(float angle, const swing_to_angle_params& p = swing_to_angle_params{}) {
    desired_angle = mirror_angle(angle, angles_mirrored_);
    g_swing_to_angle_params_buffer = p;

    pid = PID(angle_error(angle - chassis.get_absolute_heading(), mirror_direction(p.turn_direction, chassis.angles_mirrored_)), p.k.p, p.k.i, p.k.d, p.k.starti, p.settle_error, p.settle_time, p.timeout);

    motion_running = true;
    distance_traveled = 0;

    drive_task = vex::task([](){
        const float angle = chassis.desired_angle;
        const swing_to_angle_params p = g_swing_to_angle_params_buffer;

        bool crossed = false;
        float raw_error = angle_error(angle - chassis.get_absolute_heading());
        float error = angle_error(angle - chassis.get_absolute_heading(), mirror_direction(p.turn_direction, chassis.angles_mirrored_));
        float prev_error = error;
        float prev_raw_error = raw_error;

        while(!chassis.pid.is_settled()) {
            raw_error = angle_error(angle - chassis.get_absolute_heading());
            if (sign(raw_error) != sign(prev_raw_error)) {
                crossed = true;
            }
            prev_raw_error = raw_error;
            
            if (crossed) {
                error = raw_error;
            } else {
                error = angle_error(angle - chassis.get_absolute_heading(), mirror_direction(p.turn_direction, chassis.angles_mirrored_));
            }
            
            if (p.min_voltage != 0 && sign(error) != sign(prev_error)) { break; }
            chassis.distance_traveled += std::abs(error - prev_error);

            prev_error = error;

            float output = chassis.pid.compute(error);
            output = clamp(output, -p.max_voltage, p.max_voltage);
            output = clamp_min_voltage(output, p.min_voltage);
    
            chassis.left_drive.spin(fwd, output, volt);
            chassis.right_drive.stop(hold);
    
            vex::task::sleep(10);
        }

        chassis.motion_running = false;
        if (p.min_voltage == 0) { chassis.stop_drive(hold); }

        return 0;
    });
    if (p.wait) { this->wait(); }    
}

inline void Chassis::right_swing_to_angle(float angle, const swing_to_angle_params& p = swing_to_angle_params{}) {
    desired_angle = mirror_angle(angle, angles_mirrored_);
    g_swing_to_angle_params_buffer = p;

    pid = PID(angle_error(angle - chassis.get_absolute_heading(), mirror_direction(p.turn_direction, chassis.angles_mirrored_)), p.k.p, p.k.i, p.k.d, p.k.starti, p.settle_error, p.settle_time, p.timeout);

    motion_running = true;
    distance_traveled = 0;

    drive_task = vex::task([](){
        const float angle = chassis.desired_angle;
        const swing_to_angle_params p = g_swing_to_angle_params_buffer;

        bool crossed = false;
        float raw_error = angle_error(angle - chassis.get_absolute_heading());
        float error = angle_error(angle - chassis.get_absolute_heading(), mirror_direction(p.turn_direction, chassis.angles_mirrored_));
        float prev_error = error;
        float prev_raw_error = raw_error;

        while(!chassis.pid.is_settled()) {
            raw_error = angle_error(angle - chassis.get_absolute_heading());
            if (sign(raw_error) != sign(prev_raw_error)) {
                crossed = true;
            }
            prev_raw_error = raw_error;
            
            if (crossed) {
                error = raw_error;
            } else {
                error = angle_error(angle - chassis.get_absolute_heading(), mirror_direction(p.turn_direction, chassis.angles_mirrored_));
            }
            
            if (p.min_voltage != 0 && sign(error) != sign(prev_error)) break;
            chassis.distance_traveled += std::abs(error - prev_error);

            prev_error = error;

            float output = chassis.pid.compute(error);
            output = clamp(output, -p.max_voltage, p.max_voltage);
            output = clamp_min_voltage(output, p.min_voltage);
    
            chassis.right_drive.spin(reverse, output, volt);
            chassis.left_drive.stop(hold);
    
            vex::task::sleep(10);
        }

        chassis.motion_running = false;
        if (p.min_voltage == 0) { chassis.stop_drive(hold); }

        return 0;
    });
    if (p.wait) { this->wait(); }    
}

inline void Chassis::turn_to_point(float X_position, float Y_position, const turn_to_point_params& p = turn_to_point_params{}) {
    X_position = mirror_x(X_position, x_pos_mirrored_);
    Y_position = mirror_y(Y_position, y_pos_mirrored_);

    desired_X_position = X_position;
    desired_Y_position = Y_position;
    desired_angle_offset = p.angle_offset;
    g_turn_to_point_params_buffer = p;

    float start_angle = to_deg(atan2((X_position - get_X_position()), (Y_position - get_Y_position())));
    desired_angle = start_angle;

    float start_error = angle_error(start_angle - chassis.get_absolute_heading() + p.angle_offset, mirror_direction(p.turn_direction, chassis.angles_mirrored_));
    pid = PID(start_error, p.k.p, p.k.i, p.k.d, p.k.starti, p.settle_error, p.settle_time, p.timeout);

    motion_running = true;
    distance_traveled = 0;

    drive_task = vex::task([](){
        const float x_pos = chassis.desired_X_position;
        const float y_pos = chassis.desired_Y_position;
        const float angle_offset = chassis.desired_angle_offset;
        const turn_to_point_params p = g_turn_to_point_params_buffer;

        bool crossed = false;
        float angle = to_deg(atan2((x_pos - chassis.get_X_position()), (y_pos - chassis.get_Y_position())));
        float raw_error = angle_error(angle - chassis.get_absolute_heading() + angle_offset);
        float error = angle_error(angle - chassis.get_absolute_heading() + angle_offset, mirror_direction(p.turn_direction, chassis.angles_mirrored_));
        float prev_error = error;
        float prev_raw_error = raw_error;

        while(!chassis.pid.is_settled()) {
            raw_error = angle_error(angle - chassis.get_absolute_heading() + angle_offset);
            if (sign(raw_error) != sign(prev_raw_error)) {
                crossed = true;
            }
            prev_raw_error = raw_error;
            
            if (crossed) {
                error = raw_error;
            } else {
                error = angle_error(angle - chassis.get_absolute_heading() + angle_offset, mirror_direction(p.turn_direction, chassis.angles_mirrored_));
            }

            if (p.min_voltage != 0 && sign(error) != sign(prev_error)) break;
            chassis.distance_traveled += std::abs(error - prev_error);

            prev_error = error;

            float output = chassis.pid.compute(error);
            output = clamp(output, -p.max_voltage, p.max_voltage);
            output = clamp_min_voltage(output, p.min_voltage);

            chassis.drive_with_voltage(output, -output);
            task::sleep(10);
        }

        chassis.motion_running = false;
        if (p.min_voltage == 0) { chassis.stop_drive(hold); }

        return 0;
    });
    if (p.wait) { this->wait(); }
}

inline void Chassis::left_swing_to_point(float X_position, float Y_position, const swing_to_point_params& p = swing_to_point_params{}) {
    X_position = mirror_x(X_position, x_pos_mirrored_);
    Y_position = mirror_y(Y_position, y_pos_mirrored_);

    desired_X_position = X_position;
    desired_Y_position = Y_position;
    desired_angle_offset = p.angle_offset;
    g_swing_to_point_params_buffer = p;

    float start_angle = to_deg(atan2((X_position - get_X_position()), (Y_position - get_Y_position())));
    desired_angle = start_angle;

    float start_error = angle_error(start_angle - chassis.get_absolute_heading() + p.angle_offset, mirror_direction(p.turn_direction, chassis.angles_mirrored_));
    pid = PID(start_error, p.k.p, p.k.i, p.k.d, p.k.starti, p.settle_error, p.settle_time, p.timeout);

    motion_running = true;
    distance_traveled = 0;

    drive_task = vex::task([](){
        const float x_pos = chassis.desired_X_position;
        const float y_pos = chassis.desired_Y_position;
        const float angle_offset = chassis.desired_angle_offset;
        const swing_to_point_params p = g_swing_to_point_params_buffer;

        bool crossed = false;
        float angle = to_deg(atan2((x_pos - chassis.get_X_position()), (y_pos - chassis.get_Y_position())));
        float raw_error = angle_error(angle - chassis.get_absolute_heading() + angle_offset);
        float error = angle_error(angle - chassis.get_absolute_heading() + angle_offset, mirror_direction(p.turn_direction, chassis.angles_mirrored_));
        float prev_error = error;
        float prev_raw_error = raw_error;

        while(!chassis.pid.is_settled()) {
            raw_error = angle_error(angle - chassis.get_absolute_heading() + angle_offset);
            if (sign(raw_error) != sign(prev_raw_error)) {
                crossed = true;
            }
            prev_raw_error = raw_error;
            
            if (crossed) {
                error = raw_error;
            } else {
                error = angle_error(angle - chassis.get_absolute_heading() + angle_offset, mirror_direction(p.turn_direction, chassis.angles_mirrored_));
            }

            if (p.min_voltage != 0 && sign(error) != sign(prev_error)) { break; }
            chassis.distance_traveled += std::abs(error - prev_error);

            prev_error = error;

            float output = chassis.pid.compute(error);
            output = clamp(output, -p.max_voltage, p.max_voltage);
            output = clamp_min_voltage(output, p.min_voltage);

            chassis.left_drive.spin(fwd, output, volt);
            chassis.right_drive.stop(hold);

            task::sleep(10);
        }

        chassis.motion_running = false;
        if (p.min_voltage == 0) { chassis.stop_drive(hold); }

        return 0;
    });
    if (p.wait) { this->wait(); }  
}

inline void Chassis::right_swing_to_point(float X_position, float Y_position, const swing_to_point_params& p = swing_to_point_params{}) {
    X_position = mirror_x(X_position, x_pos_mirrored_);
    Y_position = mirror_y(Y_position, y_pos_mirrored_);

    desired_X_position = X_position;
    desired_Y_position = Y_position;
    desired_angle_offset = p.angle_offset;
    g_swing_to_point_params_buffer = p;

    float start_angle = to_deg(atan2((X_position - get_X_position()), (Y_position - get_Y_position())));
    desired_angle = start_angle;

    float start_error = angle_error(start_angle - chassis.get_absolute_heading() + p.angle_offset, mirror_direction(p.turn_direction, chassis.angles_mirrored_));
    pid = PID(start_error, p.k.p, p.k.i, p.k.d, p.k.starti, p.settle_error, p.settle_time, p.timeout);

    motion_running = true;
    distance_traveled = 0;

    drive_task = vex::task([](){
        const float x_pos = chassis.desired_X_position;
        const float y_pos = chassis.desired_Y_position;
        const float angle_offset = chassis.desired_angle_offset;
        const swing_to_point_params p = g_swing_to_point_params_buffer;

        bool crossed = false;
        float angle = to_deg(atan2((x_pos - chassis.get_X_position()), (y_pos - chassis.get_Y_position())));
        float raw_error = angle_error(angle - chassis.get_absolute_heading() + angle_offset);
        float error = angle_error(angle - chassis.get_absolute_heading() + angle_offset, mirror_direction(p.turn_direction, chassis.angles_mirrored_));
        float prev_error = error;
        float prev_raw_error = raw_error;

        while(!chassis.pid.is_settled()) {
            raw_error = angle_error(angle - chassis.get_absolute_heading() + angle_offset);
            if (sign(raw_error) != sign(prev_raw_error)) {
                crossed = true;
            }
            prev_raw_error = raw_error;
            
            if (crossed) {
                error = raw_error;
            } else {
                error = angle_error(angle - chassis.get_absolute_heading() + angle_offset, mirror_direction(p.turn_direction, chassis.angles_mirrored_));
            }

            if (p.min_voltage != 0 && sign(error) != sign(prev_error)) { break; }
            chassis.distance_traveled += std::abs(error - prev_error);

            prev_error = error;

            float output = chassis.pid.compute(error);
            output = clamp(output, -p.max_voltage, p.max_voltage);
            output = clamp_min_voltage(output, p.min_voltage);

            chassis.right_drive.spin(reverse, output, volt);
            chassis.left_drive.stop(hold);

            task::sleep(10);
        }

        chassis.motion_running = false;
        if (p.min_voltage == 0) { chassis.stop_drive(hold); }

        return 0;
    });
    if (p.wait) { this->wait(); }  
}

inline void Chassis::drive_to_point(float X_position, float Y_position, const drive_to_point_params& p = drive_to_point_params{}) {
    X_position = mirror_x(X_position, x_pos_mirrored_);
    Y_position = mirror_y(Y_position, y_pos_mirrored_);

    desired_X_position = X_position;
    desired_Y_position = Y_position;
    g_drive_to_point_params_buffer = p;

    pid = PID(hypot(X_position - get_X_position(), Y_position - get_Y_position()), p.drive_k.p, p.drive_k.i, p.drive_k.d, p.drive_k.starti, p.settle_error, p.settle_time, p.timeout);
    desired_heading = to_deg(atan2(X_position - get_X_position(), Y_position - get_Y_position()));
    pid_2 = PID(desired_heading - get_absolute_heading(), p.heading_k.p, p.heading_k.i, p.heading_k.d, p.heading_k.starti);

    motion_running = true;
    distance_traveled = 0;

    drive_task = vex::task([](){
        const float x_pos = chassis.desired_X_position;
        const float y_pos = chassis.desired_Y_position;
        const float heading = chassis.desired_heading;
        const drive_to_point_params p = g_drive_to_point_params_buffer;

        bool line_settled = false;
        bool prev_line_settled = is_line_settled(x_pos, y_pos, heading, chassis.get_X_position(), chassis.get_Y_position());
        float drive_error = hypot(x_pos - chassis.get_X_position(), y_pos - chassis.get_Y_position());
        float prev_drive_error = drive_error;

        while(!chassis.pid.is_settled()){
            line_settled = is_line_settled(x_pos, y_pos, heading, chassis.get_X_position(), chassis.get_Y_position());
            if (line_settled && !prev_line_settled) { break; }
            prev_line_settled = line_settled;
    
            drive_error = hypot(x_pos - chassis.get_X_position(), y_pos - chassis.get_Y_position());
            chassis.distance_traveled += std::abs(drive_error - prev_drive_error);
            prev_drive_error = drive_error;

            float heading_error = reduce_negative_180_to_180(to_deg(atan2(x_pos - chassis.get_X_position(), y_pos - chassis.get_Y_position())) - chassis.get_absolute_heading());
            float drive_output = chassis.pid.compute(drive_error);
    
            float heading_scale_factor = cos(to_rad(heading_error));
            drive_output *= heading_scale_factor;
            heading_error = reduce_negative_90_to_90(heading_error);
            float heading_output = chassis.pid_2.compute(heading_error);
            
            if (drive_error < p.settle_error) { heading_output = 0; }
    
            drive_output = clamp(drive_output, -fabs(heading_scale_factor) * p.max_voltage, fabs(heading_scale_factor) * p.max_voltage);
            heading_output = clamp(heading_output, -p.heading_max_voltage, p.heading_max_voltage);
    
            drive_output = clamp_min_voltage(drive_output, p.min_voltage);
    
            chassis.drive_with_voltage(left_voltage_scaling(drive_output, heading_output), right_voltage_scaling(drive_output, heading_output));
            vex::task::sleep(10);
        }

        chassis.motion_running = false;
        if (p.min_voltage == 0) { chassis.stop_drive(hold); }

        return 0;
    });

    if (p.wait) { this->wait(); }
}

inline void Chassis::drive_to_pose(float X_position, float Y_position, float angle, const drive_to_pose_params& p = drive_to_pose_params{}) {
    X_position = mirror_x(X_position, x_pos_mirrored_);
    Y_position = mirror_y(Y_position, y_pos_mirrored_);
    angle = mirror_angle(angle, angles_mirrored_);

    desired_X_position = X_position;
    desired_Y_position = Y_position;
    desired_angle = angle;
    desired_heading = angle;
    g_drive_to_pose_params_buffer = p;

    float target_distance = hypot(X_position - get_X_position(), Y_position - get_Y_position());
    pid = PID(target_distance, p.drive_k.p, p.drive_k.i, p.drive_k.d, p.drive_k.starti, p.settle_error, p.settle_time, p.timeout);
    pid_2 = PID(to_deg(atan2(X_position - get_X_position(), Y_position - get_Y_position())) - get_absolute_heading(), p.heading_k.p, p.heading_k.i, p.heading_k.d, p.heading_k.starti);
    
    motion_running = true;
    distance_traveled = 0;

    drive_task = vex::task([](){
        const float x_pos = chassis.desired_X_position;
        const float y_pos = chassis.desired_Y_position;
        const float angle = chassis.desired_angle;
        const drive_to_pose_params p = g_drive_to_pose_params_buffer;

        bool line_settled = is_line_settled(x_pos, y_pos, angle, chassis.get_X_position(), chassis.get_Y_position());
        bool prev_line_settled = is_line_settled(x_pos, y_pos, angle, chassis.get_X_position(), chassis.get_Y_position());
        bool crossed_center_line = false;
        bool center_line_side = is_line_settled(x_pos, y_pos, angle + 90, chassis.get_X_position(), chassis.get_Y_position());
        bool prev_center_line_side = center_line_side;

        float target_distance = hypot(x_pos - chassis.get_X_position(), y_pos - chassis.get_Y_position());
        float carrot_X = x_pos- sin(to_rad(angle)) * (p.lead * target_distance + p.setback);
        float carrot_Y = y_pos - cos(to_rad(angle)) * (p.lead * target_distance + p.setback);
        float drive_error = hypot(carrot_X - chassis.get_X_position(), carrot_Y - chassis.get_Y_position());
        float prev_drive_error = drive_error;

        while(!chassis.pid.is_settled()){
            line_settled = is_line_settled(x_pos, y_pos, angle, chassis.get_X_position(), chassis.get_Y_position());
            if (line_settled && !prev_line_settled) { break; }
            prev_line_settled = line_settled;
    
            center_line_side = is_line_settled(x_pos, y_pos, angle + 90, chassis.get_X_position(), chassis.get_Y_position());
            if (center_line_side != prev_center_line_side) {
                crossed_center_line = true;
            }
    
            target_distance = hypot(x_pos - chassis.get_X_position(), y_pos - chassis.get_Y_position());
    
            carrot_X = x_pos - sin(to_rad(angle)) * (p.lead * target_distance + p.setback);
            carrot_Y = y_pos - cos(to_rad(angle)) * (p.lead * target_distance + p.setback);
    
            drive_error = hypot(carrot_X - chassis.get_X_position(), carrot_Y - chassis.get_Y_position());
            chassis.distance_traveled += std::abs(drive_error - prev_drive_error);
            prev_drive_error = drive_error;

            float heading_error = reduce_negative_180_to_180(to_deg(atan2(carrot_X - chassis.get_X_position(), carrot_Y - chassis.get_Y_position())) - chassis.get_absolute_heading());
    
            if (drive_error < p.settle_error || crossed_center_line || drive_error < p.setback) { 
                heading_error = reduce_negative_180_to_180(angle - chassis.get_absolute_heading()); 
                drive_error = target_distance;
            }
            
            float drive_output = chassis.pid.compute(drive_error);
    
            float heading_scale_factor = cos(to_rad(heading_error));
            drive_output *= heading_scale_factor;
            heading_error = reduce_negative_90_to_90(heading_error);
            float heading_output = chassis.pid_2.compute(heading_error);
    
            drive_output = clamp(drive_output, -fabs(heading_scale_factor) * p.max_voltage, fabs(heading_scale_factor) * p.max_voltage);
            heading_output = clamp(heading_output, -p.heading_max_voltage, p.heading_max_voltage);
    
            drive_output = clamp_min_voltage(drive_output, p.min_voltage);
    
            chassis.drive_with_voltage(left_voltage_scaling(drive_output, heading_output), right_voltage_scaling(drive_output, heading_output));
            vex::task::sleep(10);
        }

        chassis.motion_running = false;
        if (p.min_voltage == 0) { chassis.stop_drive(hold); }

        return 0;
    });

    if (p.wait) { this->wait(); }
}

inline void Chassis::follow_path(std::vector<point> path, const follow_path_params& p) {
    if (x_pos_mirrored_) {
        for (auto& point : path) {
            point.x = -point.x;
        }
    }

    if (y_pos_mirrored_) {
        for (auto& point : path) {
            point.y = -point.y;
        }
    }

    pid = PID(0, p.drive_k.p, p.drive_k.i, p.drive_k.d, p.drive_k.starti, p.settle_error, p.settle_time, p.timeout);
    pid_2 = PID(0, p.heading_k.p, p.heading_k.i, p.heading_k.d, p.heading_k.starti);

    motion_running = true;
    distance_traveled = 0;

	// Add current position to the start of the path so that intersections can be found initially, even if the robot is off the path.
    path.insert(path.begin(), odom.position);

    desired_path = path;
    g_follow_path_params_buffer = p;
    
    drive_task = vex::task([](){
        std::vector<point> path = chassis.desired_path;
        follow_path_params p = g_follow_path_params_buffer;

        point target_intersection = chassis.odom.position; // The point on the path that we should target with PID.

        point prev_position = chassis.odom.position;

        // Loop through all waypoints in the provided path.
        for (int i = 0; i < (path.size() - 1); i++) {
            point start = path[i]; // The current waypoint
            point end = path[i+1]; // The next waypoint
  
            while (dist(chassis.odom.position, end) > p.lookahead_distance) {
                // Find the point(s) of intersection between a circle centered around our global position with the radius of our
                // lookahead distance and a line segment formed between our starting/ending points.
                // This can be 0-2 points depending on whether there are tangent, secant, or no intersections.
                std::vector<point> intersections = line_circle_intersections(chassis.odom.position, p.lookahead_distance, start, end);
  
                // Choose the best intersection to go to, ensuring that we don't go backwards along the path.
                if (intersections.size() == 2) {
                    // There are two intersections between our lookahead circle and the path. Find the one closest to the end of the line segment.
                    if (dist(intersections[0], end) < dist(intersections[1], end)) {
                        target_intersection = intersections[0];
                    } else {
                        target_intersection = intersections[1];
                    }
                } else if (intersections.size() == 1) {
                    // There is one intersection. Go to that intersection.
                    target_intersection = intersections[0];
                }

                point current_position = chassis.odom.position;
                chassis.distance_traveled += dist(current_position, prev_position);
                prev_position = current_position;
  
                // Move towards the target intersection with PID
                float drive_error = dist(chassis.odom.position, target_intersection);

                float heading_error = reduce_negative_180_to_180(to_deg(atan2(target_intersection.x - chassis.odom.position.x, target_intersection.y - chassis.odom.position.y)) - chassis.get_absolute_heading());
                float drive_output = chassis.pid.compute(drive_error);
  
                float heading_scale_factor = cos(to_rad(heading_error));
                drive_output *= heading_scale_factor;
                heading_error = reduce_negative_90_to_90(heading_error);
                float heading_output = chassis.pid_2.compute(heading_error);
                
                if (drive_error < p.settle_error) { heading_output = 0; }
  
                drive_output = clamp(drive_output, -fabs(heading_scale_factor) * p.max_voltage, fabs(heading_scale_factor) * p.max_voltage);
                heading_output = clamp(heading_output, -p.heading_max_voltage, p.heading_max_voltage);
  
                chassis.drive_with_voltage(drive_output + heading_output, drive_output - heading_output);
                task::sleep(10);
            }
        }

        chassis.motion_running = false;
        if (p.min_voltage == 0) { chassis.stop_drive(hold); }

        return 0;
    });
  
    if (p.wait) { this->wait(); }
}