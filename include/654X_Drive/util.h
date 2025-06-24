#pragma once

#include "vex.h"

// Clamp a value between a minimum and maximum
float clamp(float input, float min, float max);

// Returns zero for input less than absolute value width
float deadband(float input, float width);

float deadband_squared(float input, float width);

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

float reverse_angle(float angle);

float reduce_negative_180_to_180(float angle);

float reduce_negative_90_to_90(float angle);

float reduce_0_to_360(float angle);

bool is_line_settled(float desired_X, float desired_Y, float desired_angle_deg, float current_X, float current_Y);

float left_voltage_scaling(float drive_output, float heading_output);

float right_voltage_scaling(float drive_output, float heading_output);

float clamp_min_voltage(float drive_output, float drive_min_voltage);

void wipe_SD_file(const std::string& file_name);
void write_to_SD_file(const std::string& file_name, const std::string& data);
void remove_duplicates_SD_file(const std::string& file_name, const std::string& duplicate_word);
std::vector<std::string> get_SD_file_txt(const std::string& file_name);
std::vector<char> get_SD_file_char(const std::string& file_name);

void print(float num);
void print(int num);
void print(double num);
void print(std::string str);
void print(const char* str);
void print(bool boolean);
void print(long num);
void print(long long num);
void print(unsigned long long num);
void print(unsigned int num);
void print(char c);

std::string to_string_float(float num, int precision = 5, bool remove_trailing_zero = true);

inline std::string to_string(std::nullptr_t) { return "nullptr"; }
inline std::string to_string(bool v) { return v ? "true" : "false"; }
inline std::string to_string(char c) { return std::string(1, c); }
inline std::string to_string(const char* s) { return s ? std::string(s) : "<null>"; }
inline std::string to_string(char* s) { return s ? std::string(s) : "<null>"; }
inline const std::string& to_string(const std::string& s) { return s; }
inline std::string&& to_string(std::string&& s) { return std::move(s); }

template<typename T>
auto to_string(const T& value) -> typename std::enable_if<
    !std::is_pointer<T>::value &&
    !std::is_same<T, bool>::value &&
    !std::is_same<T, char>::value &&
    !std::is_same<T, std::nullptr_t>::value,
    std::string>::type
{
    std::ostringstream oss;
    oss << value;
    return oss.str();
}