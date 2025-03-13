#pragma once

#include "vex.h"

// Clamp a value between a minimum and maximum
float clamp(float input, float min, float max);

// Returns zero for input less than absolute value width
float deadband(float input, float width);

// Convert percentage to voltage
float percent_to_volt(float percent);

// convert normalized percentage to voltage
float normalize_to_volt(float normalized_percent);

// Convert voltage to percentage
float volt_to_percent(float volt);

// Convert voltage to normalized value
float volt_to_normalized(float volt);

// Converts degrees to radians
float to_rad(float angle_deg);

// Converts radians to degrees
float to_deg(float angle_rad);

// Converts vector into normalized vector
void to_normalized_vector(std::vector<float>& vector);

// Converts degrees into normalized vector
std::vector<float> to_normalized_vector(float angle);

float get_vector_distance(std::vector<float> v1, std::vector<float> v2);

float reduce_negative_180_to_180(float angle);

float reduce_negative_90_to_90(float angle);

float reduce_0_to_360(float angle);

bool is_line_settled(float desired_X, float desired_Y, float desired_angle_deg, float current_X, float current_Y);

float left_voltage_scaling(float drive_output, float heading_output);

float right_voltage_scaling(float drive_output, float heading_output);

float clamp_min_voltage(float drive_output, float drive_min_voltage);

std::string to_string_float(float num);