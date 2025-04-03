#pragma once

#include "vex.h"

extern std::vector<std::vector<float>> graph_buffer;

void test_palette();

void test();

void test_spin_all_motors(std::vector<hzn::motor_group> motor_chains);

void test_print_motor_torque(std::vector<hzn::motor_group> motor_chains);


struct pid_data
{
  std::vector<std::reference_wrapper<float>> variables = {
    lead_scalar, current_scalar
  };
  
  int index = 0;
  float modifier = 1;
  float modifer_scale = 1;
  bool needs_update = false;
};

extern pid_data data;

int get_flicker_index(const std::string &valueStr, int place);
void PID_tuner();

void print(float num);

void test_serial_output();

int print_vector_to_serial(const std::string& name, const std::vector<float>& vector);

void click();

void print_coordinates();

void display_screen(screen* scr);

void add_to_graph_buffer(std::vector<float> data);
void clear_graph_buffer();
void graph();
