#pragma once

#include "vex.h"

extern std::function<void()> test_func;

void test_drive();
void test_turn();
void test_swing();
void test_full();
void test_odom();


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

void config_spin_all_motors();
void config_motor_wattage();
void config_motor_temp();
void config_odom_data();
void config_skills_driver_run();
void config_test_three_wire_port(port port);

void print(float num);
void print(int num);
void print(double num);
void print(uint32_t num);
void print(std::string str);
void print(const char* str);
void print(bool boolean);
void print(long num);
void print(long long num);
void print(unsigned long long num);
void print(unsigned int num);
void print(char c);
