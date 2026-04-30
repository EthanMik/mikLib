#pragma once

#include "mikLib/drive.h"

class Chassis {
public:

    // Constants are in constants.h

    mik::tracker_mode tracker_mode; // Type of tracking mode to use for odometry.

    // How the robot will stop after a motion is finished. min speed > 0 will skip this step. Default will set voltage to 0.
    vex::brakeType stop_behavior = vex::brakeType::undefined; 

    /**
     * @param left_drive  Motor group on the robot's left side.
     * @param right_drive Motor group on the robot's right side.
     * @param inertial_port Inertial sensor port (1-21).
     * @param inertial_scale Scale factor applied to raw gyro angles to correct drift.
     * @param forward_tracker_port Forward tracker rotation sensor port (1-21). Use PORT0 to use motor encoders instead.
     * @param forward_tracker_diameter Forward tracking‑wheel diameter (in inches).
     * @param forward_tracker_center_distance Distance from the chassis centre to the forward tracker (in).
     * @param sideways_tracker_port Sideways tracker rotation sensor port (1-21).
     * @param sideways_tracker_diameter Sideways tracking‑wheel diameter (in inches).
     * @param sideways_tracker_center_distance Distance from the chassis centre to the sideways tracker (in).
     * @param reset_sensors Distance sensors parallel to a robot face that can reset odometry axes.
     */
    Chassis(mik::motor_group left_drive, mik::motor_group right_drive, int inertial_port,
        double inertial_scale, bool force_calibrate_inertial, double wheel_diameter,
        double drivetrain_rpm, int forward_tracker_port, double forward_tracker_diameter,
        double forward_tracker_center_distance, int sideways_tracker_port, double sideways_tracker_diameter,
        double sideways_tracker_center_distance, mik::distance_reset reset_sensors
    );

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
     * @param control_desaturate_bias Desaturation bias when throttle+turn exceeds 100 (0 = prioritize turn, 1 = prioritize throttle, default 0.5).
     */
    void set_control_constants(float control_throttle_deadband, float control_throttle_min_output, float control_throttle_curve_gain, float control_turn_deadband, float control_turn_min_output, float control_turn_curve_gain, float control_desaturate_bias);

    /**
     * @brief Resets default turn constants.
     * Turning includes turn_to_angle() and turn_to_point().
     * 
     * @param turn_max_voltage Max voltage out of 12.
     * @param turn_kp Proportional constant.
     * @param turn_ki Integral constant.
     * @param turn_kd Derivative constant.
     * @param turn_starti Minimum angle in degrees for integral to begin.
     * @param turn_slew Slew rate in volt per 10 ms.
     */
    void set_turn_constants(float turn_max_voltage, float turn_kp, float turn_ki, float turn_kd, float turn_starti, float turn_slew);

    /**
     * @brief Resets default drive constants.
     * Driving includes drive_distance(), drive_to_point(), drive_to_pose(), and follow_path()
     * 
     * @param drive_max_voltage Max voltage out of 12.
     * @param drive_kp Proportional constant.
     * @param drive_ki Integral constant.
     * @param drive_kd Derivative constant.
     * @param drive_starti Minimum distance in inches for integral to begin.
     * @param drive_slew Slew rate in volt per 10 ms.
     */
    void set_drive_constants(float drive_max_voltage, float drive_kp, float drive_ki, float drive_kd, float drive_starti, float drive_slew);
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
     * @param heading_slew Slew rate in volt per 10 ms.
     */
    void set_heading_constants(float heading_max_voltage, float heading_kp, float heading_ki, float heading_kd, float heading_starti, float heading_slew);

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
     * @param swing_slew Slew rate in volt per 10 ms.
     */
    void set_swing_constants(float swing_max_voltage, float swing_kp, float swing_ki, float swing_kd, float swing_starti, float swing_slew);

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

    /** 
     * @brief Yield to the scheduler until the current motion the robots in has traveled specifed units. 
     * @param units units of motion (inches or degrees)
     * @param percent Uses a 0-100, with 0 being start and 100 being end of motion.
    */
    void wait_until(float units, vex::percentUnits percent_units);

    /**
     * @brief Yields to the scheduler until the current motion is within specified units of the the target.
     * @param units units of motion (inches or degrees).
     */
    void wait_until_within(float units);

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
    void stop_drive(vex::brakeType brake = vex::brakeType::undefined);

    /** @brief Calibrates the inertial sensor, if force calibrate is true
     * it will continue to calibrate until it is within threshold for 1 second
     */
    void calibrate_inertial();

    /** @return inertial rotation scaled by inertial scale in deg. */
    float get_rotation();

    /** @return Field‑relative inertial heading (deg, 0‑360). */
    float get_absolute_heading();
    
    /** @brief Mirror all subsequent x-coordinates, affecting drive_to_point(), turn_to_point(), drive_to_pose(), and set_coordinates().
     * Useful on opposite field sides. 
    */
    void mirror_all_auton_x_pos();
    
    /** @brief Mirror all subsequent y-coordinates, affecting drive_to_point(), turn_to_point(), drive_to_pose(), and set_coordinates().
     * Useful on opposite field sides. 
    */
    void mirror_all_auton_y_pos();

    /** @brief Disables mirroring for x_pos, y_pos and angles.
    */
    void disable_mirroring();
    
    /** @return True if x coordinates have been mirrored */
    bool x_pos_mirrored();
    
    /** @return True if y coordinates have been mirrored */
    bool y_pos_mirrored();

    /**
     * @brief Turns the robot to a field-centric angle.
     * Optimizes direction, so it turns whichever way is closer to the 
     * current heading of the robot, unless a turn direction is specified. 
     * Uses degrees for tracking distance.
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
    void turn_to_angle(float angle, turn_to_angle_params p = turn_to_angle_params{});

    /**
     * @brief Drives the robot a given distance with a given heading.
     * Drive distance does not optimize for direction, so it won't try
     * to drive at the opposite heading from the one given to get there faster.
     * You can control the heading, but if you choose not to, it will drive with the
     * heading it's currently facing. It uses forward tracker to find distance traveled. 
     * Use negative distance to go backwards. Uses inches for tracking distance.
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
    void drive_distance(float distance, drive_distance_params p = drive_distance_params{});

    /**
     * Turns to a given angle with the left side of the drivetrain.
     * Like turn_to_angle(), is optimized for turning the shorter
     * direction, unless a turn direction is specified. Uses degreees for tracking distance.
     * 
     * @param angle Desired angle in degrees.
     * @param turn_direction The way the robot should turn, (ccw, cw, or shortest path)
     * @param min_voltage Minimum voltage on the drive, used for chaining movements.
     * @param max_voltage Max voltage on the drive out of 12.
     * @param opposite_voltage Voltage on the opposite side of the drivetrain out of 12.
     * @param settle_error Error to be considered settled in degrees.
     * @param settle_time Time to be considered settled in milliseconds.
     * @param large_settle_error Error to be considered large settled in degrees.
     * @param large_settle_time Time to be considered large settled in milliseconds.
     * @param timeout Time before quitting and move on in milliseconds.
     * @param k PID and starti constants. Do k. to access constants.
     * @param wait Yields program until motion has finished, true by default.
     */
    void left_swing_to_angle(float angle, swing_to_angle_params p = swing_to_angle_params{});

    /**
     * Turns to a given angle with the right side of the drivetrain.
     * Like turn_to_angle(), is optimized for turning the shorter
     * direction, unless a turn direction is specified. Uses degrees for tracking distance.
     * 
     * @param angle Desired angle in degrees.
     * @param turn_direction The way the robot should turn, (ccw, cw, or shortest path)
     * @param min_voltage Minimum voltage on the drive, used for chaining movements.
     * @param max_voltage Max voltage on the drive out of 12.
     * @param opposite_voltage Voltage on the opposite side of the drivetrain out of 12.
     * @param settle_error Error to be considered settled in degrees.
     * @param settle_time Time to be considered settled in milliseconds.
     * @param large_settle_error Error to be considered large settled in degrees.
     * @param large_settle_time Time to be considered large settled in milliseconds.
     * @param timeout Time before quitting and move on in milliseconds.
     * @param k PID and starti constants. Do k. to access constants.
     * @param wait Yields program until motion has finished, true by default.
     */
    void right_swing_to_angle(float angle, swing_to_angle_params p = swing_to_angle_params{});
    
    /** @return Position of the left and right drivetrain encoders averaged in inches */ 
    float get_motor_encoder_position();
    /** 
     * @param index Index of motor to get position of, default, -1, is average position
     * @return Position of the right side of the drivetrain in inches */ 
    float get_right_drive_position(int index = -1);
    /** 
     * @param index Index of motor to get position of, default, -1, is average position
     * @return Position of the right side of the drivetrain in inches */ 
    float get_left_drive_position(int index = -1);
    /** @return Position of the forward tracker in inches */ 
    float get_forward_tracker_position();
    /** @return Position of the sideways tracker in inches */ 
    float get_sideways_tracker_position();

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
     * wall resetting the robots x position. The wall the robot is facing is automatically found by using its 
     * absolute X, Y, and heading. Wall facing can be specified.
     * 
     * @param sensor_pos The side of the robot that the distance sensor is mounted.
     * @param max_reset_distance The maxiumum allowed of distance in inches that an odom axis can be changed.
     * 
     * @return True if the desired axis was reset successfully.
     */
    bool reset_axis(mik::distance_position sensor_pos, float max_reset_distance, int reset_attempts = 1);
    bool reset_axis(mik::distance_position sensor_pos, mik::wall_position wall_pos, float max_reset_distance, int reset_attempts = 1);

    /**
     * @brief Turns to a specified point on the field.
     * Functions similarly to turn_to_angle() except with a point. The
     * angle_offset parameter turns the robot extra relative to the 
     * desired target. For example, if you want the back of your robot
     * to point at (36, 42), you would run turn_to_point(36, 42, {.angle_offset = 180}).
     * Uses degrees for tracking distance.
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
    void turn_to_point(float X_position, float Y_position, turn_to_point_params p = turn_to_point_params{});
    
    /**
     * @brief Turns to a specified point on the field with the left side of the drivetrain.
     * Functions similarly to left_swing_to_angle() except with a point. The
     * angle_offset parameter turns the robot extra relative to the 
     * desired target. For example, if you want the back of your robot
     * to point at (36, 42), you would run left_swing_to_point(36, 42, {.angle_offset = 180}).
     * Uses degrees for tracking distance.
     * 
     * @param X_position Desired x position in inches.
     * @param Y_position Desired y position in inches.
     * @param angle_offset Angle turned past the desired heading in degrees.
     * @param turn_direction The way the robot should turn, (ccw, cw, or shortest path)
     * @param min_voltage Minimum voltage on the drive, used for chaining movements.
     * @param max_voltage Max voltage on the drive out of 12.
     * @param opposite_voltage Voltage on the opposite side of the drivetrain out of 12.
     * @param settle_error Error to be considered settled in degrees.
     * @param settle_time Time to be considered settled in milliseconds.
     * @param large_settle_error Error to be considered large settled in degrees.
     * @param large_settle_time Time to be considered large settled in milliseconds.
     * @param timeout Time before quitting and move on in milliseconds.
     * @param k PID and starti constants. Do k. to access constants.
     * @param wait Yields program until motion has finished, true by default.
     */
    void left_swing_to_point(float X_position, float Y_position, swing_to_point_params p = swing_to_point_params{});

    /**
     * @brief Turns to a specified point on the field with the right side of the drivetrain.
     * Functions similarly to right_swing_to_angle() except with a point. The
     * angle_offset parameter turns the robot extra relative to the 
     * desired target. For example, if you want the back of your robot
     * to point at (36, 42), you would run right_swing_to_point(36, 42, {.angle_offset = 180}).
     * Uses degrees for tracking distance.
     * 
     * @param X_position Desired x position in inches.
     * @param Y_position Desired y position in inches.
     * @param angle_offset Angle turned past the desired heading in degrees.
     * @param turn_direction The way the robot should turn, (ccw, cw, or shortest path)
     * @param min_voltage Minimum voltage on the drive, used for chaining movements.
     * @param max_voltage Max voltage on the drive out of 12.
     * @param opposite_voltage Voltage on the opposite side of the drivetrain out of 12.
     * @param settle_error Error to be considered settled in degrees.
     * @param settle_time Time to be considered settled in milliseconds.
     * @param large_settle_error Error to be considered large settled in degrees.
     * @param large_settle_time Time to be considered large settled in milliseconds.
     * @param timeout Time before quitting and move on in milliseconds.
     * @param k PID and starti constants. Do k. to access constants.
     * @param wait Yields program until motion has finished, true by default.
     */
    void right_swing_to_point(float X_position, float Y_position, swing_to_point_params p = swing_to_point_params{});

    /**
     * @brief Drives to a specified point on the field.
     * Uses the double-PID method, with one for driving and one for heading correction.
     * The drive error is the euclidean distance to the desired point, and the heading error
     * is the turn correction from the current heading to the desired point. Uses optimizations
     * like driving backwards whenever possible and scaling the drive output with the cosine
     * of the angle to the point. Uses inches for tracking distance.
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
    void drive_to_point(float X_position, float Y_position, drive_to_point_params p  = drive_to_point_params{});
    
    /**
     * @brief Drives to a specified point and orientation on the field.
     * Uses a boomerang controller. The carrot point is back from the target
     * by the same distance as the robot's distance to the target, times the lead. The
     * robot always tries to go to the carrot, which is constantly moving, and the
     * robot eventually gets into position. The heading correction is optimized to only
     * try to reach the correct angle when drive error is low, and the robot will drive 
     * backwards to reach a pose if it's faster. .5 is a reasonable value for the lead. 
     * Try it out in a desmos simulation https://www.desmos.com/calculator/sptjw5szex.
     * Uses inches for tracking distance.
     *
     * @param X_position Desired x position in inches.
     * @param Y_position Desired y position in inches.
     * @param angle Desired orientation in degrees.
     * @param lead Constant scale factor that determines how far away the carrot point is.
     * @param drift Determines the amount of horizontal drift allowed, lower values reduce drift.
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
    void drive_to_pose(float X_position, float Y_position, float angle, drive_to_pose_params p = drive_to_pose_params{});

    /**
     * @brief Drives and turns simultaneously to a desired pose on a holonomic chassis.
     * Uses two PID loops, one for drive distance and one for heading, running concurrently
     * so translation and rotation happen at the same time. The heading controller is optimized
     * to turn the shorter direction. The motion exits only once both PID loops have settled:
     * drive uses the drive exit conditions, heading uses the turn exit conditions.
     * Drive gains come from drive_k and heading gains come from heading_k (defaults to heading constants).
     * Uses inches for tracking distance.
     *
     * @param X_position Desired x position in inches.
     * @param Y_position Desired y position in inches.
     * @param angle Desired orientation in degrees.
     * @param max_voltage Max voltage on the drive out of 12.
     * @param heading_max_voltage Max voltage for heading correction out of 12.
     * @param settle_error Drive error to be considered settled in inches.
     * @param settle_time Drive time to be considered settled in milliseconds.
     * @param turn_settle_error Turn Error to be considered settled in degrees.
     * @param turn_settle_time Turn Time to be considered settled in milliseconds.
     * @param timeout Time before quitting and moving on in milliseconds.
     * @param drive_k Drive PID and starti constants.
     * @param heading_k Heading PID and starti constants.
     * @param wait Yields program until motion has finished, true by default.
     */
    void holonomic_to_pose(float X_position, float Y_position, float angle, holonomic_to_pose_params p = holonomic_to_pose_params{});

    /** @brief disables joystick control of the drivetrain */
    void disable_control();
    /** @brief enables joystick control of the drivetrain */
    void enable_control();

    // Drive control modes

    /** @brief Drive using split-arcade layout: left stick (Axis3) for throttle, right stick (Axis1) for turn, with deadband applied. */
    void split_arcade();

    /**
     * @brief Drive using split-arcade layout with an exponential response curve applied to both throttle and turn axes.
     * Desaturates combined output to stay within motor limits.
     */
    void split_arcade_curved();

    /** @brief Drive using tank layout: left stick (Axis3) controls left side, right stick (Axis2) controls right side, with deadband applied. */
    void tank();

    /** @brief Drive using tank layout with an exponential response curve applied to each stick independently. */
    void tank_curved();

    /**
     * @brief Drive a holonomic (X-drive / mecanum) chassis with field-centric control.
     * Joystick inputs are rotated by the current absolute heading so forward is always field-forward.
     */
    void field_centric_holonomic();

    /** @brief Drive a holonomic chassis with robot-centric split-arcade control: Axis3 throttle, Axis1 turn, Axis4 strafe. */
    void split_arcade_holonomic();

    /**
     * @brief Dispatch joystick input based on the selected drive mode.
     * @param dm Drive mode enumeration.
     */
    void control(mik::drive_mode dm);
    
    mik::tracker forward_tracker;
    mik::tracker sideways_tracker;

    vex::inertial inertial;
    
    mik::motor_group left_drive;
    mik::motor_group right_drive; 

    mik::distance_reset reset_sensors;

    bool calibrating = false;
    bool motion_running;
    float distance_traveled;
    float distance_from_target;
    float percent_traveled; // Percent of the current motion traveled, 0-100.
    float active_min_voltage = 0;
    
    bool position_tracking;
    bool control_disabled;
    bool sideways_tracker_used;

    mik::drive_mode selected_drive_mode = mik::drive_mode::SPLIT_ARCADE;

    /** SET POINTS. USED FOR GRAPHING AND ACCESSING CHASSIS DATA IN ANOTHER TASK */

    float desired_angle = 0;
    float desired_distance = 0;
    float desired_heading = 0;
    float desired_X_position = 0;
    float desired_Y_position = 0;
    float desired_angle_offset = 0;
    swing_to_angle_params turn_params_buffer{};
    turn_type turn_type_buffer = turn_type::TURN; 
    drive_to_point_params drive_to_point_params_buffer{};
    drive_to_pose_params drive_to_pose_params_buffer{};
    drive_distance_params drive_distance_params_buffer{};
    holonomic_to_pose_params holonomic_to_pose_params_buffer{};

private:
    // Universal function for swinging and
    void turn(float target_angle, float angle_offset, swing_to_angle_params p, turn_type type);

    bool x_pos_mirrored_ = false;
    bool y_pos_mirrored_ = false;

    float inertial_scale;
    bool force_calibrate_inertial;
    const float minimum_calibration_error = .05;

    float wheel_diameter;
    float drivetrain_rpm;

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