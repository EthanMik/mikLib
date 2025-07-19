#pragma once

#include "vex.h"

/** @brief Robot should drive and end in starting position. */
void test_drive();
/** @brief Robot should drive in curves and end in starting position. */
void test_heading();
/** @brief Robot should turn and end in starting position. */
void test_turn();
/** @brief Robot should swing and end in start heading. */
void test_swing();
/** @brief Robot should drive, turn, and swing and end in starting position. */
void test_full();
/** @brief Robot should drive with odom and end in starting position. */
void test_odom();

void test_odom_boomerang();

/**
 * @brief Enables a PID tuner suite.  
 * `test_drive()` can be run on controller and Actual and Setpoint values will be graphed on brain.  
 * Adjust `set_plot_bounds()`’s `x_max_bound` if the trace doesn’t fit.
 * Check `PID_tuner()`'s documentation to see controls.
 */
void config_test_drive();

/**
 * @brief Enables a PID tuner suite.  
 * `test_turn()` can be run on controller and Actual and Setpoint values will be graphed on brain.  
 * Adjust `set_plot_bounds()`’s `x_max_bound` if the trace doesn’t fit.
 * Check `PID_tuner()`'s documentation to see controls.
 */
void config_test_turn();

/**
 * @brief Enables a PID tuner suite.  
 * `test_swing()` can be run on controller and Actual and Setpoint values will be graphed on brain.  
 * Adjust `set_plot_bounds()`’s `x_max_bound` if the trace doesn’t fit.
 * Check `PID_tuner()`'s documentation to see controls.
 */
void config_test_swing(); 

/**
 * @brief Enables a PID tuner suite.  
 * `test_heading()` can be run on controller and Actual and Setpoint values will be graphed on brain.  
 * Adjust `set_plot_bounds()`’s `x_max_bound` if the trace doesn’t fit.
 * Check `PID_tuner()`'s documentation to see controls.
 */
void config_test_heading();

/**
 * @brief Enables a PID tuner suite.  
 * `test_heading()` can be run on controller and Actual and Setpoint values will be graphed on brain.  
 * Adjust `set_plot_bounds()`’s `x_max_bound` if the trace doesn’t fit.
 * Check `PID_tuner()`'s documentation to see controls.
 */
void config_test_full();

/**
 * @brief Enables a PID tuner suite.  
 * `test_odom()` can be run on controller and Actual and Setpoint values will be graphed on brain.  
 * Adjust `set_plot_bounds()`’s `x_max_bound` if the trace doesn’t fit.
 * Check `PID_tuner()`'s documentation to see controls.
 */
void config_test_odom();

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
 * - B – Start the auton test, reset the graph, and begin re-plotting
 * 
 * - X – Cancel the auton run and re-enable user control
 */
void PID_tuner();

void config_add_motors(std::vector<std::vector<mik::motor>> motor_groups);
void config_add_motors(std::vector<mik::motor> motors);

/** @brief Logs errors during robot calibration, checks inertial, SD, and drivetrain motors
 * It is recommended to add other motors and devices to this function
 */
int run_diagnostic();

/** @brief Displays a log of the most recent controller edited PID values from the PID tuner suite  */
void config_add_pid_output_SD_console();

/** @brief Spins all drivetrain motors one at a time.
 * Useful for debugging the spin direction of motors as motors may be flipped in drivetrain.
 * Intended behavior is for all motors to spin forward.
 * It is recommended to add other motors to this function
 */
void config_spin_all_motors();

/** @brief Adds motor wattage values into UI console, 
 * Used for checking motor friction. around 0.5~ is good for one side of a 6 motor drivetrain. 
 * It is recommended to add other motors to this function
 */
void config_motor_wattage();

/** @brief Adds motor temperature values into UI console, 
 * around 80% is when the motors become cooked 
 * It is recommended to add other motors to this function
 */
void config_motor_temp();

/** @brief Adds odometry data into the UI console, will start position tracking if not already done so
 * useful for debugging tracking pods
 */
void config_odom_data();

/** @brief Adds errors found into the UI console, errors are collected from run_diagnostic() */
void config_error_data();

/** @brief Starts a practice driver skills run that will stop the robot after 60 seconds */
void config_skills_driver_run();

/** @brief Triggers a component plugged into a 3 wire port at specified port */
void config_test_three_wire_port(port port);