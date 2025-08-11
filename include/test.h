#pragma once

#include "vex.h"

/** @brief Constants used while tuning relative motions */
void relative_mode_constants();

/** @brief Constants used while tuning odom motions */
void odom_mode_constants();

/** @brief Robot should drive and end in starting position. */
void test_drive();
/** @brief Robot should drive and end in starting position. */
void test_odom_drive();

/** @brief Robot should drive in curves and end in starting position. */
void test_heading();
/** @brief Robot should drive in curves and end in starting position. */
void test_odom_heading();

/** @brief Robot should turn and end in starting position. */
void test_turn();
/** @brief Robot should turn and end in starting position. */
void test_odom_turn();

/** @brief Robot should swing and end in start heading. */
void test_swing();
/** @brief Robot should swing and end close to start heading. */
void test_odom_swing();

/** @brief Robot should drive, turn, and swing and end in starting position. */
void test_full();
/** @brief Robot should drive, turn, and swing and end in starting position. */
void test_odom_full();

/** @brief Robot should drive in curves and end in starting position. */
void test_boomerang();

/** @brief Robot should drive in an S shape forwards and backwards and end in starting position.
 * Play around with settle error and lookahead distance if robot is driving sporadic.
 */
void test_pursuit();

/**
 * @brief Enables a PID tuner suite.  
 * `test_drive()` can be run on controller and Actual and Setpoint values will be graphed on brain.  
 * Adjust `set_plot_bounds()`’s `x_max_bound` if the trace doesn’t fit.
 * Check `PID_tuner()`'s documentation to see controls.
 */
void config_tune_drive();

/**
 * @brief Enables a PID tuner suite.  
 * `test_heading()` can be run on controller and Actual and Setpoint values will be graphed on brain.  
 * Adjust `set_plot_bounds()`’s `x_max_bound` if the trace doesn’t fit.
 * Check `PID_tuner()`'s documentation to see controls.
 */
void config_tune_heading();

/**
 * @brief Enables a PID tuner suite.  
 * `test_turn()` can be run on controller and Actual and Setpoint values will be graphed on brain.  
 * Adjust `set_plot_bounds()`’s `x_max_bound` if the trace doesn’t fit.
 * Check `PID_tuner()`'s documentation to see controls.
 */
void config_tune_turn();

/**
 * @brief Enables a PID tuner suite.  
 * `test_swing()` can be run on controller and Actual and Setpoint values will be graphed on brain.  
 * Adjust `set_plot_bounds()`’s `x_max_bound` if the trace doesn’t fit.
 * Check `PID_tuner()`'s documentation to see controls.
 */
void config_tune_swing(); 

/** Swaps the tuning configuration for config_test_...() functions.
 * Swaps odom_constants to default_constants and swaps test_drive to test_odom_drive etc.
 */
bool config_swap_test_mode();

/** @returns True if odom testing mode is selected */
bool config_is_testing_odom();

struct pid_data {
  std::vector<std::pair<std::string, std::reference_wrapper<float>>> variables = {};
  int index = 0;
  int min = 0;
  int max = 3;
  float modifier = 1;
  float modifer_scale = 1;
  float var_upper_size = 1;
  bool needs_update = false;
};

extern pid_data data;
extern std::vector<std::string> error_data;

/**
 * @brief Displays a menu on the controller to change PID values.
 * Heres a guide on how to tune a PID https://www.youtube.com/watch?v=6EcxGh1fyMw&t=602s.
 * If SD is inserted all changed values are logged in pid_data.txt.
 * Use `config_add_pid_output_SD_console()` to see the data.
 *
 * **Controls:
 *
 * - Joysticks – Move drivetrain (only when no autonomous is running).
 * 
 * - Up Arrow – Move cursor to the tuning value above
 * 
 * - Down Arrow – Move cursor to the tuning value below
 * 
 * - Right Arrow – Increase the hovered digit by 1
 * 
 * - Left Arrow – Decrease the hovered digit by 1
 * 
 * - A – Shift the digit cursor one place to the right
 * 
 * - Y – Shift the digit cursor one place to the left
 * 
 * - X – Start the auton test, reset the graph, and begin re-plotting
 * 
 * - B – Cancel the auton run and re-enable user control
 */
void PID_tuner();

/** @brief Allows UI to interface with all of robots motors */
void config_add_motors(std::vector<mik::motor_group> motor_groups, std::vector<mik::motor> motors);

/** @brief Stops all motors connected to robot. Used when disabling user control. */
void stop_all_motors(vex::brakeType mode = vex::brakeType::coast);

/** @brief Changes braketype to all motors connected to robot. Used when disabling user control. */
void set_brake_all_motors(vex::brakeType mode);  

/** @brief Logs errors during robot calibration, checks inertial, SD, and drivetrain motors
 * It is recommended to add other motors and devices to this function
 */
int run_diagnostic();

/** @brief Displays a log of the most recent controller edited PID values from the PID tuner suite  */
void config_add_pid_output_SD_console();

/** @brief Spins all drivetrain motors one at a time.
 * Useful for debugging the spin direction of motors as motors may be flipped in drivetrain.
 * Intended behavior is for all motors to spin forward.
 */
void config_spin_all_motors();

/** @brief Adds motor wattage values into UI console, 
 * Used for checking motor friction. around 0.5~ is good for one side of a 6 motor drivetrain. 
 */
void config_motor_wattage();

/** @brief Adds motor temperature values into UI console, 
 * around 80% is when the motors become cooked 
 */
void config_motor_temp();

/** Adds motor torque values to UI console */
void config_motor_torque();

/** Adds motor efficency % values to UI console */
void config_motor_efficiency();

/** Adds motor current values to UI console */
void config_motor_current();

/** @brief Adds odometry data into the UI console, will start position tracking if not already done so
 * useful for debugging tracking pods
 */
void config_odom_data();

/** @brief Adds errors found into the UI console, errors are collected from run_diagnostic() */
void config_error_data();

/** @brief Starts a practice driver skills run that will stop the robot after 60 seconds */
void config_skills_driver_run();

/** @brief Triggers a component plugged into a 3 wire port at specified port */
void config_test_three_wire_port(int port);