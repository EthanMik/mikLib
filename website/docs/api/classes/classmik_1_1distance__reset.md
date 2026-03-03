---
title: mik::distance_reset

---

# mik::distance_reset






`#include <distance.h>`

## Public Functions

|                | Name           |
| -------------- | -------------- |
| | **[distance_reset](/api/classes/classmik_1_1distance__reset#function-distance-reset)**(const std::vector< [mik::distance](/api/classes/classmik_1_1distance) > & distance_sensors) |
| std::vector< [mik::distance](/api/classes/classmik_1_1distance) > & | **[get_distance_sensors](/api/classes/classmik_1_1distance__reset#function-get-distance-sensors)**() |
| float | **[get_reset_axis_pos](/api/classes/classmik_1_1distance__reset#function-get-reset-axis-pos)**([mik::distance_position](/api/namespaces/namespacemik#enum-distance-position) sensor_pos, [mik::wall_position](/api/namespaces/namespacemik#enum-wall-position) wall_pos, float x, float y, float angle)<br>Gets an X or Y position of the robot based on the heading and distance from a wall. The distance sensor must be facing the desired wall with no obstruction in order to work. Choosing to reset off a top or bottom wall will reset the robots y positon, and a left or right wall resetting the robots x position.  |
| std::string | **[get_wall_facing](/api/classes/classmik_1_1distance__reset#function-get-wall-facing)**([mik::distance_position](/api/namespaces/namespacemik#enum-distance-position) sensor_pos, float x, float y, float angle) |

## Public Functions Documentation

### function distance_reset

```cpp
distance_reset(
    const std::vector< mik::distance > & distance_sensors
)
```


Wraps [mik::distance](/api/classes/classmik_1_1distance) sensors into a group. Two distance sensors perpendicular to each other should be enough, As you can reset both coords at once if the sensors are facing two different walls. Ex: A front or back sensor with a left or right sensor with the robot in a corner. 


### function get_distance_sensors

```cpp
std::vector< mik::distance > & get_distance_sensors()
```


**Return**: vector containing all [mik::distance](/api/classes/classmik_1_1distance) sensors. 

### function get_reset_axis_pos

```cpp
float get_reset_axis_pos(
    mik::distance_position sensor_pos,
    mik::wall_position wall_pos,
    float x,
    float y,
    float angle
)
```

Gets an X or Y position of the robot based on the heading and distance from a wall. The distance sensor must be facing the desired wall with no obstruction in order to work. Choosing to reset off a top or bottom wall will reset the robots y positon, and a left or right wall resetting the robots x position. 

**Parameters**: 

  * **sensor_pos** The side of the robot that the distance sensor is mounted. 
  * **wall_pos** The wall that is being looked at by desired distance sensor. 
  * **max_reset_distance** The maxiumum allowed of distance in inches that an odom axis can be changed.


**Return**: A new x or y coordinate based on the wall desired sensor is faced at. 

### function get_wall_facing

```cpp
std::string get_wall_facing(
    mik::distance_position sensor_pos,
    float x,
    float y,
    float angle
)
```


-------------------------------

Updated on 2026-03-02 at 17:21:01 -0600