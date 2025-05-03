#pragma once

#include "vex.h"

extern std::function<void()> test_func;

void test_drive();
void test_turn();
void test_swing();
void test_full();
void test_odom();

void test_spin_all_motors(std::vector<hzn::motor_group> motor_chains);

struct pid_data
{
  std::vector<std::pair<std::string, std::reference_wrapper<float>>> variables = {};
  
  int index = 0;
  int min = 0;
  int max = 3;
  float modifier = 1;
  float modifer_scale = 1;
  bool needs_update = false;
};

extern pid_data data;

int get_flicker_index(const std::string &valueStr, int place);
void PID_tuner();

void print(float num);
void print(int num);
void print(double num);
void print(uint32_t num);
void print(std::string str);
void print(const char* str);
void print(bool boolean);

void test_serial_output();

int print_vector_to_serial(const std::string& name, const std::vector<float>& vector);

void print_coordinates();

void skills_driver_run();
