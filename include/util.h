#ifndef UTIL_H
#define UTIL_H

#include "654-Template/motor_chain.h"
#include "654-Template/manual_drive.h"
#include "654-Template/auton_drive.h"
#include "robot-config.h"
#include "vex.h"

// Clamp a value between a minimum and maximum
float clamp(float input, float min, float max);

// Returns zero for input less than absolute value width
float deadband(float input, float width);

// Convert RPM to voltage
float rpm_to_volt(float rpm, float maxRPM = 600.0);

// Convert percentage to voltage
float percent_to_volt(float percent);

// convert normalized percentage to voltage
float normalize_to_volt(float normalized_percent);

// Convert voltage to RPM
float volt_to_rpm(float volt, double maxRPM = 600.0);

// Convert voltage to percentage
float volt_to_percent(float volt);

// Convert voltage to normalized value
float volt_to_normalized(float volt);

// Converts degrees to radians
float to_rad(float angle_deg);

// Converts degrees into normalized vector
std::vector<float> to_normalized_vector(float angle);

float get_vector_distance(std::vector<float> v1, std::vector<float> v2);

float reduce_negative_180_to_180(float angle);

float reduce_0_to_360(float angle);

#endif