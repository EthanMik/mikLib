---
title: Odom
sidebar_label: Odom
sidebar_position: 3
---

# Odom

Generic odometry class

The relevant outputs are `position` (an x/y
[point](#public-members)) and `orientation_deg`. Requires an inertial sensor for heading. 
The math uses the [Pilons arc method](https://wiki.purduesigbots.com/software/odometry).

:::note
[Chassis](./Chassis) uses an `odom` instance internally and starts it once `set_coordinates` is called.
You usually only need this class directly when building a custom tracking setup.
:::

## Methods

### set_physical_distances

```cpp
void set_physical_distances(float forward_tracker_center_distance,
                            float sideways_tracker_center_distance);
```

Sets the tracker center distances. The forward tracker center distance is the
horizontal distance from the center of the robot to the wheel the sensor
measures. The sideways tracker center distance is the vertical distance from
the center of the robot to the sideways wheel being measured. If there is no
sideways wheel, set its center distance to `0`, which is equivalent to a
no-drift robot.

| Parameter | Description |
| --------- | ----------- |
| `forward_tracker_center_distance` | Horizontal distance to the wheel center, in inches. |
| `sideways_tracker_center_distance` | Vertical distance to the wheel center, in inches. |

### set_position

```cpp
void set_position(point position, float orientation_deg,
                  float forward_tracker_position, float sideways_tracker_position);
```

Resets the position, including the tracking wheels. Position is field-centric,
and `0` degrees points in the positive Y direction.

| Parameter | Description |
| --------- | ----------- |
| `position` | Field-centric x/y position of the robot. |
| `orientation_deg` | Field-centered, clockwise-positive orientation. |
| `forward_tracker_position` | Current forward sensor position, in inches. |
| `sideways_tracker_position` | Current sideways sensor position, in inches. |

### update_position

```cpp
void update_position(float forward_tracker_position,
                     float sideways_tracker_position, float orientation_deg);
```

Runs one odometry update. Compares the input sensor readings against the stored
values to update `position` and `orientation_deg`. 

| Parameter | Description |
| --------- | ----------- |
| `forward_tracker_position` | Current forward sensor position, in inches. |
| `sideways_tracker_position` | Current sideways sensor position, in inches. |
| `orientation_deg` | Field-centered, clockwise-positive orientation. |

## Public members

| Member | Description |
| ------ | ----------- |
| `position` | Current field-centric x/y position. |
| `orientation_deg` | Current orientation in degrees. |
| `forward_tracker_center_distance` | Configured forward tracker center distance. |
| `sideways_tracker_center_distance` | Configured sideways tracker center distance. |
