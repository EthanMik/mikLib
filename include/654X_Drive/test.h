#pragma once

#include "vex.h"

extern std::vector<std::vector<float>> graph_buffer;

void test_palette();

void test();

void test_spin_all_motors(std::vector<hzn::motor_group> motor_chains);

void test_print_motor_torque(std::vector<hzn::motor_group> motor_chains);

void test_serial_output();

int print_vector_to_serial(const std::string& name, const std::vector<float>& vector);

void click();

void print_coordinates();

void display_screen(screen* scr);

void add_to_graph_buffer(std::vector<float> data);
void clear_graph_buffer();
void graph();
