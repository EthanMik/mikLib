---
title: Util
sidebar_label: Util
sidebar_position: 5
---

# Util

Helper functions used throughout mikLib

## Math & joystick

### clamp

```cpp
float clamp(float input, float min, float max);
```

Clamps `input` between `min` and `max`. Does no error checking and assumes
`min <= max`.

### deadband / deadband_squared

```cpp
float deadband(float input, float width);
float deadband_squared(float input, float width);
```

Zeroes out small joystick values. `deadband_squared` squares the input for
finer low-end control.

| Parameter | Description |
| --------- | ----------- |
| `input` | The input joystick value. |
| `width` | Minimum value that is not zeroed out. |

### percent_to_volt / volt_to_percent

```cpp
float percent_to_volt(float percent);
float volt_to_percent(float volt);
```

Convert between a `-100..100` percent scale and a `-12..12` volt scale.

### sign

```cpp
template <typename T> constexpr T sign(T value);
```

Returns `-1` for negative numbers and `1` otherwise.

## Angles

### to_rad / to_deg

```cpp
float to_rad(float angle_deg);
float to_deg(float angle_rad);
```

Convert between degrees and radians.

### reduce_negative_180_to_180 / reduce_negative_90_to_90 / reduce_0_to_360

```cpp
float reduce_negative_180_to_180(float angle);
float reduce_negative_90_to_90(float angle);
float reduce_0_to_360(float angle);
```

Reduce an angle (in degrees) to the named equivalent range. For
`reduce_negative_90_to_90`, an angle with no equivalent returns the angle
halfway around the circle.

### angle_error

```cpp
float angle_error(float error, mik::turn_direction dir = mik::turn_direction::undefined);
```

Normalizes an angular error according to a direction preference. `CW` wraps
negative errors up by 360, `CCW` wraps positive errors down by 360, and
`undefined` (default) reduces to `(-180, 180]`.

| Parameter | Description |
| --------- | ----------- |
| `error` | Signed angular difference in degrees (e.g. `target - current`). |
| `dir` | Direction preference: cw, ccw, or fastest (default). |

### mirror

```cpp
void mirror(float& x, float& y, float& angle, mik::turn_direction& turn_direction, bool mirror_x, bool mirror_y);
// plus overloads for any subset of {x, y, angle, turn_direction}
```

Mirrors a pose (and optional turn direction) for use on the opposite side of
the field. Negating `x` uses `360 - angle`; negating `y` uses `180 - angle`.
Turn direction flips when exactly one axis is mirrored.

| Parameter | Description |
| --------- | ----------- |
| `x` / `y` | Coordinates in inches. |
| `angle` | Heading in degrees. |
| `turn_direction` | The preferred turn direction. |
| `mirror_x` / `mirror_y` | Whether to negate X / Y. |

## Voltage scaling

These shape drive output and are used inside the motion algorithms.

### left_voltage_scaling / right_voltage_scaling

```cpp
float left_voltage_scaling(float drive_output, float heading_output);
float right_voltage_scaling(float drive_output, float heading_output);
```

Proportionally scale drive and heading output so neither side exceeds 12 volts.

### slew_scaling

```cpp
float slew_scaling(float drive_output, float prev_drive_output, float slew, bool apply = true);
```

Limits acceleration to reduce wheel slip. `slew` is the max change in voltage
per 10 ms; `0` disables it.

### overturn_scaling

```cpp
float overturn_scaling(float drive_output, float heading_output, float max_speed);
```

Scales voltage to prevent overturning on sharp boomerang segments.

### clamp_min_voltage

```cpp
float clamp_min_voltage(float drive_output, float drive_min_voltage);
```

Raises an output up to `drive_min_voltage` if it is too slow (used for motion
chaining). Has no effect on a `0` output, since direction is unknown.

### clamp_max_slip

```cpp
float clamp_max_slip(float drive_output, float current_X, float current_Y, float current_angle_deg,
                     float desired_X, float desired_Y, float drift);
```

Clamps drive output to keep the robot from drifting on turning boomerang
segments. Higher `drift` allows more drift.

## Geometry & settling

### dist

```cpp
float dist(point p1, point p2);
```

Returns the distance between two points.

### is_line_settled

```cpp
bool is_line_settled(float desired_X, float desired_Y, float desired_angle_deg,
                     float current_X, float current_Y, float exit_error);
```

Draws a line perpendicular to the robot-to-target line and checks whether the
robot has crossed it. Enables fast settling and motion chaining.

| Parameter | Description |
| --------- | ----------- |
| `desired_X` / `desired_Y` | Ending position in inches. |
| `desired_angle_deg` | Direction of the line to be drawn. |
| `current_X` / `current_Y` | The robot's current position in inches. |
| `exit_error` | Distance from the line (inches) within which the robot is settled. |

## SD card files

```cpp
bool SD_text_file_exists(const std::string& file_name);
void wipe_SD_file(const std::string& file_name);
void write_to_SD_file(const std::string& file_name, const std::string& data);
void remove_duplicates_SD_file(const std::string& file_name, const std::string& duplicate_word);
std::vector<std::string> get_SD_file_txt(const std::string& file_name);
```

Read/write helpers for text files on the SD card. **Use `.txt` files.**

| Function | Description |
| -------- | ----------- |
| `SD_text_file_exists` | Returns `true` if the file is found; prints to console otherwise. |
| `wipe_SD_file` | Empties the file. |
| `write_to_SD_file` | Appends `data` to the file on a new line. |
| `remove_duplicates_SD_file` | Removes any line containing `duplicate_word`. |
| `get_SD_file_txt` | Returns a vector with each line of the file. |

## Printing & ports

### print

```cpp
void print(float num, const mik::color& clr = mik::color::WHITE);
// overloads accept int, double, std::string, const char*, bool, long, char, etc.
```

Prints to the terminal via serial in an optional color.

### to_string / to_string_float

```cpp
std::string to_string_float(float num, int precision = 5, bool remove_trailing_zero = true);
template<typename T> std::string to_string(const T& value);
```

Stringify numbers and other values. `to_string_float` controls precision and
trailing-zero trimming.

### to_triport / port_to_string

```cpp
vex::triport::port& to_triport(int port);
vex::triport::port& to_triport(vex::triport& expander, int port);
std::string port_to_string(int port);
```

Convert an integer port (e.g. `PORT1`) into a triport reference or a printable
string.

## Button "new press" macros

```cpp
btnA_new_press(state)   btnB_new_press(state)   btnX_new_press(state)   btnY_new_press(state)
btnL1_new_press(state)  btnR1_new_press(state)  btnL2_new_press(state)  btnR2_new_press(state)
btnUp_new_press(state)  btnDown_new_press(state) btnLeft_new_press(state) btnRight_new_press(state)
```

Each macro returns `true` only on the **first frame** of a new press of the
given boolean `state`, and `false` otherwise; useful for toggles.
