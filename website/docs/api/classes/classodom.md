---
title: odom
summary: General-use odometry class with X_position, Y_position, and orientation_deg being the relevant outputs. This works for one and two-tracker systems, and needs a gyro to get input angle. 

---

# odom



General-use odometry class with X_position, Y_position, and orientation_deg being the relevant outputs. This works for one and two-tracker systems, and needs a gyro to get input angle. 


`#include <odom.h>`

## Public Functions

|                | Name           |
| -------------- | -------------- |
| void | **[set_physical_distances](/api/classes/classodom#function-set-physical-distances)**(float forward_tracker_center_distance, float sideways_tracker_center_distance)<br>Setter method for tracker center distances. The forward tracker center distance is the horizontal distance from the center of the robot to the center of the wheel the sensor is measuring. The sideways tracker center distance is the vertical distance from the center of the robot to the center of the sideways wheel being measured. If there's really no sideways wheel we set the center distance to 0 and pretend the wheel never spins, which is equivalent to a no-drift robot.  |
| void | **[set_position](/api/classes/classodom#function-set-position)**([point](/api/classes/structpoint) position, float orientation_deg, float forward_tracker_position, float sideways_tracker_position) |
| void | **[update_position](/api/classes/classodom#function-update-position)**(float forward_tracker_position, float sideways_tracker_position, float orientation_deg) |

## Public Attributes

|                | Name           |
| -------------- | -------------- |
| float | **[orientation_deg](/api/classes/classodom#variable-orientation-deg)**  |
| [point](/api/classes/structpoint) | **[position](/api/classes/classodom#variable-position)**  |

## Public Functions Documentation

### function set_physical_distances

```cpp
void set_physical_distances(
    float forward_tracker_center_distance,
    float sideways_tracker_center_distance
)
```

Setter method for tracker center distances. The forward tracker center distance is the horizontal distance from the center of the robot to the center of the wheel the sensor is measuring. The sideways tracker center distance is the vertical distance from the center of the robot to the center of the sideways wheel being measured. If there's really no sideways wheel we set the center distance to 0 and pretend the wheel never spins, which is equivalent to a no-drift robot. 

**Parameters**: 

  * **forward_tracker_center_distance** A horizontal distance to the wheel center in inches. 
  * **sideways_tracker_center_distance** A vertical distance to the wheel center in inches. 


### function set_position

```cpp
void set_position(
    point position,
    float orientation_deg,
    float forward_tracker_position,
    float sideways_tracker_position
)
```


**Parameters**: 

  * **[position](/api/classes/classodom#variable-position)** Field-centric x and y position of the robot. 
  * **[orientation_deg](/api/classes/classodom#variable-orientation-deg)** Field-centered, clockwise-positive, orientation. 
  * **forward_tracker_position** Current position of the sensor in inches. 
  * **sideways_tracker_position** Current position of the sensor in inches. 


Resets the position, including tracking wheels. Position is field-centric, and orientation is such that 0 degrees is in the positive Y direction. Orientation can be provided with some flexibility, including less than 0 and greater than 360.


### function update_position

```cpp
void update_position(
    float forward_tracker_position,
    float sideways_tracker_position,
    float orientation_deg
)
```


**Parameters**: 

  * **forward_tracker_position** Current position of the sensor in inches. 
  * **sideways_tracker_position** Current position of the sensor in inches. 
  * **[orientation_deg](/api/classes/classodom#variable-orientation-deg)** Field-centered, clockwise-positive, orientation. 


Does the odometry math to update position Uses the Pilons arc method outline here: [https://wiki.purduesigbots.com/software/odometry](https://wiki.purduesigbots.com/software/odometry) All the deltas are done by getting member variables and comparing them to the input. Ultimately this all works to update the public member variable X_position. This function needs to be run at 200Hz or so for best results.


## Public Attributes Documentation

### variable orientation_deg

```cpp
float orientation_deg;
```


### variable position

```cpp
point position;
```


-------------------------------

Updated on 2026-03-02 at 17:21:00 -0600