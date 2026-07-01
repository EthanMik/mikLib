---
title: Constants
sidebar_label: Constants
sidebar_position: 2
---

# Constants

Tuning constants in mikLib

- The global [`Constants`](#constants-struct) struct, which holds
  every motion constant used in [Chassis](./Chassis).
- The [PID structs](#pid-gain-structs) (`drive_constants`, etc.).
- The [motion parameter structs](#motion-parameter-structs)
  (`turn_to_angle_params`, etc.) passed to each motion.

## Constants struct

A single global instance, `constants`, stores the defaults applied to every
motion. Set these once at startup (or via the [Chassis setters](./Chassis#setters)).

### Drive constants

Used while driving. Heading constants keep the robot facing the target while it drives.

| Field | Description |
| ----- | ----------- |
| `drive_min_voltage` | Minimum voltage on the drive, used for chaining movements. |
| `drive_max_voltage` | Max voltage out of 12. |
| `drive_kp` / `drive_ki` / `drive_kd` | Proportional / integral / derivative constants. |
| `drive_starti` | Minimum distance (inches) for integral to begin. |
| `drive_slew` | Limits drive acceleration in volts per 10 ms. |
| `drive_exit_error` | Error (inches) at which the drive motion exits. |
| `drive_settle_error` | Error (inches) to be considered settled. |
| `drive_settle_time` | Time (ms) to be considered settled. |
| `drive_timeout` | Time (ms) before quitting and moving on. |
| `heading_max_voltage` | Max heading-correction voltage out of 12. |
| `heading_kp` / `heading_ki` / `heading_kd` | Heading PID constants. |
| `heading_starti` | Minimum distance (degrees) for integral to begin. |
| `heading_slew` | Limits heading-correction acceleration in volts per 10 ms. |

### Turn constants

| Field | Description |
| ----- | ----------- |
| `turn_min_voltage` | Minimum voltage for turning out of 12. |
| `turn_max_voltage` | Max voltage out of 12. |
| `turn_kp` / `turn_ki` / `turn_kd` | Turn PID constants. |
| `turn_starti` | Minimum angle (degrees) for integral to begin. |
| `turn_slew` | Limits turning acceleration in volts per 10 ms. |
| `turn_exit_error` | Error at which the turn motion exits. |
| `turn_settle_error` | Error (degrees) to be considered settled. |
| `turn_settle_time` | Time (ms) to be considered settled. |
| `turn_timeout` | Time (ms) before quitting and moving on. |

### Swing constants

Swinging turns the robot using one side of the drivetrain.

| Field | Description |
| ----- | ----------- |
| `swing_min_voltage` | Minimum voltage for swinging out of 12. |
| `swing_opposite_voltage` | Voltage on the opposite (non-swung) side out of 12. |
| `swing_max_voltage` | Max voltage out of 12. |
| `swing_kp` / `swing_ki` / `swing_kd` | Swing PID constants. |
| `swing_starti` | Minimum distance (degrees) for integral to begin. |
| `swing_slew` | Limits swinging acceleration in volts per 10 ms. |
| `swing_exit_error` | Error at which the swing motion exits. |
| `swing_settle_error` | Error (degrees) to be considered settled. |
| `swing_settle_time` | Time (ms) to be considered settled. |
| `swing_timeout` | Time (ms) before quitting and moving on. |

### Boomerang, control, and slew cutoffs

| Field | Description |
| ----- | ----------- |
| `boomerang_lead` | Scale factor for how far away the carrot point is. |
| `boomerang_drift` | Lower values give slower speeds while turning. Use higher (~8) for traction drives. |
| `control_throttle_deadband` | Deadband percent for the throttle axis. |
| `control_throttle_min_output` | Minimum throttle output percent after deadband. |
| `control_throttle_curve_gain` | Expo gain for throttle (1 linear, 1.06 very curvy). |
| `control_turn_deadband` | Deadband percent for the turn axis. |
| `control_turn_min_output` | Minimum turn output percent after deadband. |
| `control_turn_curve_gain` | Expo gain for the turn axis. |
| `control_desaturate_bias` | Desaturation bias for `split_arcade_curved` (0 = prioritize turn, 1 = prioritize throttle). |
| `turn_cutoff` | Degrees within which slew stops being applied. |
| `drive_cutoff` | Inches within which slew stops and heading correction stops. |

## PID structs

Each motion's `k` (or `drive_k` / `heading_k`) field takes one of these. Their
fields default to the matching values in `constants`, so you only override what
you need:

```cpp
// Sets the only the drive PID kP
drive_constants k = { .p = 2.0 };
```

```cpp
struct drive_constants   { float p, i, d, starti, slew; };
struct heading_constants { float p, i, d, starti, slew; };
struct turn_constants    { float p, i, d, starti, slew; };
struct swing_constants   { float p, i, d, starti, slew; };
```

| Field | Description |
| ----- | ----------- |
| `p` | Proportional constant. |
| `i` | Integral constant. |
| `d` | Derivative constant. |
| `starti` | Minimum error for the integral term to begin. |
| `slew` | Limits acceleration in volts per 10 ms. |

## Motion parameter structs

Every [Chassis](./Chassis) motion takes an optional params struct as its last
argument. All fields default to the global `constants`, so you override only
what you need with designated initializers:

```cpp
chassis.turn_to_angle(90, {.max_voltage = 6, .direction = mik::turn_direction::cw});
```

### turn_to_angle_params / turn_to_point_params

| Field | Description |
| ----- | ----------- |
| `direction` | The way the robot should turn (ccw, cw, or shortest path). |
| `angle_offset` | *(point only)* Angle turned past the desired heading, in degrees. |
| `min_voltage` | Minimum voltage on the drive, used for chaining movements. |
| `max_voltage` | Max voltage on the drive out of 12. |
| `exit_error` | Distance from target (degrees) within which the motion exits. |
| `settle_error` | Error (degrees) to be considered settled. |
| `settle_time` | Time (ms) to be considered settled. |
| `timeout` | Time (ms) before quitting and moving on. |
| `wait` | Yields the program until the motion finishes (default `true`). |
| `k` | A [`turn_constants`](#pid-structs) override. |

### swing_to_angle_params / swing_to_point_params

Same as the turn params above, plus:

| Field | Description |
| ----- | ----------- |
| `opposite_voltage` | Voltage on the opposite side of the drivetrain out of 12. |
| `k` | A [`swing_constants`](#pid-structs) override. |

### drive_distance_params / strafe_distance_params

| Field | Description |
| ----- | ----------- |
| `heading` | Desired heading in degrees. Defaults to the current heading. |
| `min_voltage` | Minimum voltage on the drive, used for chaining movements. |
| `max_voltage` | Max voltage on the drive out of 12. |
| `heading_max_voltage` | Max voltage for getting to heading out of 12. |
| `exit_error` | Distance from target (inches) within which the motion exits. |
| `settle_error` | Error (inches) to be considered settled. |
| `settle_time` | Time (ms) to be considered settled. |
| `timeout` | Time (ms) before quitting and moving on. |
| `wait` | Yields the program until the motion finishes (default `true`). |
| `drive_k` / `heading_k` | [`drive_constants`](#pid-structs) / [`heading_constants`](#pid-structs) overrides. |

### drive_to_point_params / drive_to_pose_params

The drive params above, plus:

| Field | Description |
| ----- | ----------- |
| `direction` | Force a forward or reverse approach. Defaults to choosing automatically. |
| `lead` | *(pose only)* Scale factor for how far away the carrot point is. |
| `drift` | *(pose only)* Limits speed while turning; higher values increase lateral speed out of 10. |

### holonomic_to_pose_params

The drive params above, plus separate turn settling:

| Field | Description |
| ----- | ----------- |
| `turn_settle_error` | Turn error (degrees) to be considered settled. |
| `turn_settle_time` | Turn time (ms) to be considered settled. |
