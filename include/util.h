#ifndef UTIL_H
#define UTIL_H

#include "vex.h"
#include <algorithm>
#include <cmath>

// Cnvert RPM to voltage
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

// Clamp a value between a minimum and maximum
float clamp(float input, float min, float max);

// Returns zero for input less than absolute value width
float deadband(float input, float width);

#endif