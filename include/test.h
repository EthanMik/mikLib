#pragma once

#include "vex.h"

void test_drive();
void test_turn();
void test_swing();
void test_heading();
void test_full();
void test_odom();

void config_test_drive();
void config_test_turn();
void config_test_swing();
void config_test_heading();
void config_test_full();
void config_test_odom();

struct pid_data
{
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

void PID_tuner();

int run_diagnostic();
void config_add_pid_output_SD_console();
void config_spin_all_motors();
void config_motor_wattage();
void config_motor_temp();
void config_odom_data();
void config_error_data();
void config_skills_driver_run();
void config_test_three_wire_port(port port);