---
title: PID
sidebar_label: PID
sidebar_position: 4
---

# PID

Generic PID class

## Constructors

```cpp
PID();
PID(float kp, float ki, float kd);
PID(float kp, float ki, float kd, float starti);
PID(float kp, float ki, float kd, float starti,
    float settle_error, float settle_time, float exit_error,
    float timeout, float stall_timeout = 0);
```

`starti` keeps the integral term at `0` until `error` drops below it, which
prevents integral windup on large errors.

The settling constructor adds exit conditions. The controller is **settled**
when `error` stays below `settle_error` for `settle_time`, or once the motion
has run longer than `timeout`.

| Parameter | Description |
| --------- | ----------- |
| `kp` | Proportional constant. |
| `ki` | Integral constant. |
| `kd` | Derivative constant. |
| `starti` | Maximum error at which the integral term starts accumulating. |
| `settle_error` | Maximum error to be considered settled. |
| `settle_time` | Minimum time (ms) under `settle_error` to be considered settled. |
| `exit_error` | Error at which the motion is considered finished. |
| `timeout` | Time (ms) after which to give up and move on. `0` disables it. |
| `stall_timeout` | Time (ms) to give up when the robot is near 0 velocity. `0` disables it. |

## Methods

### compute

```cpp
float compute(float error);
```

Computes the output power from the current `error`. Includes two
optimizations: the integral term resets to `0` whenever the robot crosses
`error == 0`, and integral only accumulates while `error` is below `starti`.

- **Returns** — the output power.

### is_settled

```cpp
bool is_settled();
```

Returns whether the movement has settled, per the settling rules described
above.

- **Returns** — `true` if the movement is settled.

## Public members

These are readable at any time (e.g. for graphing or debugging):

| Member | Description |
| ------ | ----------- |
| `error` | Current error. |
| `kp`, `ki`, `kd` | Active PID gains. |
| `starti` | Integral gating threshold. |
| `settle_error`, `settle_time` | Active settle conditions. |
| `exit_error` | Active exit error. |
| `timeout`, `stall_timeout` | Active timeouts. |
| `accumulated_error` | Running integral sum. |
| `previous_error` | Error from the previous `compute()` call. |
| `output` | Last computed output. |
| `time_spent_settled` | Time (ms) the controller has been within `settle_error`. |
| `time_spent_running` | Total time (ms) the controller has been running. |
| `time_spent_stalled` | Time (ms) the controller has been near 0 velocity. |
| `exiting` | `true` once an exit condition has been met. |
