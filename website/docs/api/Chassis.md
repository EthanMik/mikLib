---
title: Chassis
sidebar_label: Chassis
sidebar_position: 1
---

# Chassis

How to interact with the robot


## Constructor

```cpp
Chassis(mik::motor_group left_drive, mik::motor_group right_drive, int inertial_port,
        double inertial_scale, bool force_calibrate_inertial, double wheel_diameter,
        double drivetrain_rpm, int forward_tracker_port, double forward_tracker_diameter,
        double forward_tracker_center_distance, int sideways_tracker_port,
        double sideways_tracker_diameter, double sideways_tracker_center_distance,
        mik::distance_reset reset_sensors);
```

| Parameter | Description |
| --------- | ----------- |
| `left_drive` / `right_drive` | Motor groups for each side of the robot. |
| `inertial_port` | Inertial sensor port (1-21). |
| `inertial_scale` | Scale factor applied to raw gyro angles to correct drift. |
| `force_calibrate_inertial` | If true, keeps calibrating until drift is within threshold for 1 second. |
| `wheel_diameter` | Drivetrain wheel diameter, in inches. |
| `drivetrain_rpm` | RPM of the drivetrain output (after gearing). |
| `forward_tracker_port` | Forward tracker rotation sensor port (1-21). Use `PORT0` for motor encoders. |
| `forward_tracker_diameter` | Forward tracking-wheel diameter, in inches. |
| `forward_tracker_center_distance` | Distance from chassis center to the forward tracker, in inches. |
| `sideways_tracker_port` | Sideways tracker rotation sensor port (1-21). |
| `sideways_tracker_diameter` | Sideways tracking-wheel diameter, in inches. |
| `sideways_tracker_center_distance` | Distance from chassis center to the sideways tracker, in inches. |
| `reset_sensors` | Distance sensors parallel to a robot face that can reset odometry axes. |

## Motion algorithms

Each motion blocks until it finishes by default (`wait = true`).
It also can take multiple individual constants passed as struct
(documented on the [Constants](./Constants#motion-parameter-structs) page), so
you override only what you need:

```cpp
chassis.drive_distance(24);                      // all defaults
chassis.turn_to_angle(90, {.max_voltage = 6});   // override max voltage
```

### drive_with_voltage

```cpp
void drive_with_voltage(float left_voltage, float right_voltage);
```

Drives each side of the chassis at the specified voltage (`-12` to `12`;
negative drives that side backward).


#### Reset of motions are [documented here](../tutorial/motions.mdx)


## Async control

Use these to chain or interrupt motions when running them non-blocking
(`{.wait = false}`).

| Method | Description |
| ------ | ----------- |
| `void wait()` | Yields until the current motion finishes. |
| `void wait_until(float units)` | Yields until the motion has traveled `units` (inches for drives, degrees for turns). |
| `void wait_until(float units, vex::percentUnits)` | Same, where `units` is `0-100` percent of the motion. |
| `void wait_until_within(float units)` | Yields until the motion is within `units` of the target. |
| `bool is_in_motion()` | Returns `true` if the robot is in motion. |
| `void cancel_motion()` | Cancels the current motion, leaving drive voltage at `min_voltage` so the next motion starts without stopping. |

## Odometry

| Method | Description |
| ------ | ----------- |
| `void set_coordinates(float X_position, float Y_position, float orientation_deg)` | Sets the robot's position and heading, and also starts the odometry task |
| `void set_heading(float orientation_deg)` | Sets just the robot's heading. |
| `float get_X_position()` / `float get_Y_position()` | The robot's x / y position in inches. |
| `void position_track()` | Runs one iteration of the odometry update loop. |
| `static int position_track_task()` | VEX task entry point that continuously calls `position_track()`. Pass to `vex::task`. |

## Distance Resets

:::important
Distance resets only work if you use the absolute positioning system. Where 0, 0 is at the center of the field. Using [path.jerryio](https://path.jerryio.com/) is recommended.
:::

:::important
This [simulator](https://ethanmik.github.io/Wall-Reset-Simulator/) is how distance resets work in mikLib
:::
### reset_axis

```cpp
bool reset_axis(mik::distance_position sensor_pos, float max_reset_distance, int reset_attempts = 1);
bool reset_axis(mik::distance_position sensor_pos, mik::wall_position wall_pos,
                float max_reset_distance, int reset_attempts = 1);
```

Resets an X or Y odometry axis using a distance sensor facing a wall. The wall
is detected automatically from the robot's pose, or you can specify it with
`wall_pos`. Returns `true` if the axis was reset successfully.

| Parameter | Description |
| --------- | ----------- |
| `sensor_pos` | The side of the robot the distance sensor is mounted on. |
| `wall_pos` | The wall to reset against, overriding automatic detection. |
| `max_reset_distance` | Maximum distance (inches) an axis is allowed to change. |
| `reset_attempts` | Number of readings to average before applying the reset. |

## Driver control

Call one drive mode every loop in the usercontrol task, or use `control()` to
dispatch by the selected mode.

| Method | Description |
| ------ | ----------- |
| `void split_arcade()` | Left stick throttle (Axis3), right stick turn (Axis1), with deadband. |
| `void split_arcade_curved()` | Split arcade with an exponential response curve; desaturates combined output. |
| `void tank()` | Left stick controls the left side (Axis3), right stick the right (Axis2). |
| `void tank_curved()` | Tank with an exponential curve per stick. |
| `void field_centric_holonomic()` | Field-centric holonomic control (inputs rotated by heading). |
| `void split_arcade_holonomic()` | Robot-centric holonomic split arcade: Axis3 throttle, Axis1 turn, Axis4 strafe. |
| `void control(mik::drive_mode dm)` | Dispatches joystick input based on the given drive mode. |
| `void enable_control()` / `void disable_control()` | Enable/disable joystick control of the drivetrain. |

## Setters

These override the global tuning [Constants](./Constants) at runtime.

### PID constants

```cpp
void set_drive_constants(float drive_max_voltage, float drive_kp, float drive_ki, float drive_kd, float drive_starti, float drive_slew);
void set_heading_constants(float heading_max_voltage, float heading_kp, float heading_ki, float heading_kd, float heading_starti, float heading_slew);
void set_turn_constants(float turn_max_voltage, float turn_kp, float turn_ki, float turn_kd, float turn_starti, float turn_slew);
void set_swing_constants(float swing_max_voltage, float swing_kp, float swing_ki, float swing_kd, float swing_starti, float swing_slew);
```

Each setter resets the default constants for one PID controller.

| Parameter | Description |
| --------- | ----------- |
| `max_voltage` | Max voltage out of 12. |
| `kp` | Proportional constant. |
| `ki` | Integral constant. |
| `kd` | Derivative constant. |
| `starti` | Minimum error before the integral term begins accumulating (degrees for turn/heading/swing, inches for drive). |
| `slew` | Slew rate, in volts per 10 ms. |

| Controller | Affects |
| ---------- | ------- |
| **drive** | `drive_distance()`, `drive_to_point()`, `drive_to_pose()`, `holonomic_to_pose()`, `strafe_distance()` |
| **heading** | Keeps the robot facing the target during every drive motion. |
| **turn** | `turn_to_angle()`, `turn_to_point()` |
| **swing** | `left_swing_to_angle()`, `right_swing_to_angle()`, `left_swing_to_point()`, `right_swing_to_point()` |

### Exit conditions

```cpp
void set_drive_exit_conditions(float drive_settle_error, float drive_settle_time, float drive_timeout);
void set_turn_exit_conditions(float turn_settle_error, float turn_settle_time, float turn_timeout);
void set_swing_exit_conditions(float swing_settle_error, float swing_settle_time, float swing_timeout);
```

A motion exits once error stays below `settle_error` for `settle_time`, or once
`timeout` elapses.

| Parameter | Description |
| --------- | ----------- |
| `settle_error` | Error to be considered settled (inches for drive, degrees for turn/swing). |
| `settle_time` | Time within `settle_error` before settling, in milliseconds. |
| `timeout` | Time before quitting and moving on, in milliseconds. |

### Driver control constants

```cpp
void set_control_constants(float control_throttle_deadband, float control_throttle_min_output, float control_throttle_curve_gain, float control_turn_deadband, float control_turn_min_output, float control_turn_curve_gain, float control_desaturate_bias);
```

Resets the joystick deadbands and expo curves for throttle and turn. Tune it
visually in [Desmos](https://www.desmos.com/calculator/umicbymbnl).

| Parameter | Description |
| --------- | ----------- |
| `control_throttle_deadband` | Deadband percent for the throttle axis. |
| `control_throttle_min_output` | Minimum throttle output percent after deadband. |
| `control_throttle_curve_gain` | Expo gain for the throttle axis (1 linear, 1.06 very curvy). |
| `control_turn_deadband` | Deadband percent for the turn axis. |
| `control_turn_min_output` | Minimum turn output percent after deadband. |
| `control_turn_curve_gain` | Expo gain for the turn axis. |
| `control_desaturate_bias` | Desaturation bias when throttle + turn exceeds 100 (0 = prioritize turn, 1 = prioritize throttle, default 0.5). |

### Tracking offsets

```cpp
void set_tracking_offsets(float forward_tracker_center_distance, float sideways_tracker_center_distance);
```

Updates the tracker offsets when the robot's center of rotation changes (e.g.
clamping onto a large game object).

| Parameter | Description |
| --------- | ----------- |
| `forward_tracker_center_distance` | Distance from the chassis center to the forward tracker, in inches. |
| `sideways_tracker_center_distance` | Distance from the chassis center to the sideways tracker, in inches. |

### Brake type

```cpp
void set_brake_type(vex::brakeType brake);
```

Globally sets the brake mode (`coast`, `brake`, `hold`) for both drive motor
groups. Defaults to `coast`.

## Other utilities

| Method | Description |
| ------ | ----------- |
| `void stop_drive(vex::brakeType brake = undefined)` | Stops both sides of the drivetrain. |
| `void calibrate_inertial()` | Calibrates the inertial sensor (until within threshold for 1s if force-calibrating). |
| `float get_rotation()` | Inertial rotation scaled by `inertial_scale`, in degrees. |
| `float get_absolute_heading()` | Field-relative heading (0-360°). |
| `float get_motor_encoder_position()` | Average of the left/right drive encoders, in inches. |
| `float get_left_drive_position(int index = -1)` / `get_right_drive_position(int index = -1)` | Side drive position in inches; `-1` averages the side. |
| `float get_forward_tracker_position()` / `get_sideways_tracker_position()` | Tracker positions in inches. |
| `void mirror_all_auton_x_pos()` / `mirror_all_auton_y_pos()` | Mirror all subsequent coordinates/angles across the X / Y axis (for the opposite field side). |
| `void disable_mirroring()` | Disables all mirroring. |
| `bool x_pos_mirrored()` / `bool y_pos_mirrored()` | Whether X / Y coordinates are currently mirrored. |

## Public members

| Member | Description |
| ------ | ----------- |
| `mik::tracker_mode tracker_mode` | Tracking mode used for odometry. |
| `vex::brakeType stop_behavior` | How the robot stops after a motion. A `min_voltage > 0` skips this. |
| `bool sideways_tracker_used` | True if a sideways tracker is configured. |
| `mik::drive_mode selected_drive_mode` | The drive mode used by `control()`. |
| `float percent_traveled` | Progress through the current motion, 0-100. |
| `bool position_tracking` | True while the odometry task is running. |
| `bool control_disabled` | True when joystick control is disabled. |
| `desired_angle`, `desired_distance`, `desired_heading`, `desired_X_position`, `desired_Y_position`, `desired_angle_offset` | Current motion setpoints (useful for graphing or cross-task access). |
