---
title: mik::distance

---

# mik::distance






`#include <distance.h>`

Inherits from vex::distance

## Public Functions

|                | Name           |
| -------------- | -------------- |
| | **[distance](/api/classes/classmik_1_1distance#function-distance)**(int port, [mik::distance_position](/api/namespaces/namespacemik#enum-distance-position) position, float x_center_offset, float y_center_offset)<br>Creates a new distance sensor object that contains its position and offset from tracking center, on the port specified.  |
| const std::string | **[name](/api/classes/classmik_1_1distance#function-name)**() const |
| [mik::distance_position](/api/namespaces/namespacemik#enum-distance-position) | **[position](/api/classes/classmik_1_1distance#function-position)**() const |
| float | **[x_center_offset](/api/classes/classmik_1_1distance#function-x-center-offset)**() const |
| void | **[x_center_offset](/api/classes/classmik_1_1distance#function-x-center-offset)**(float new_offset) |
| float | **[y_center_offset](/api/classes/classmik_1_1distance#function-y-center-offset)**() const |
| void | **[y_center_offset](/api/classes/classmik_1_1distance#function-y-center-offset)**(float new_offset) |

## Public Functions Documentation

### function distance

```cpp
distance(
    int port,
    mik::distance_position position,
    float x_center_offset,
    float y_center_offset
)
```

Creates a new distance sensor object that contains its position and offset from tracking center, on the port specified. 

**Parameters**: 

  * **index** The port index for this sensor. The index is zero-based. 
  * **[position](/api/classes/classmik_1_1distance#function-position)** The face of the robot that the distance sensor is mounted to. 
  * **[x_center_offset](/api/classes/classmik_1_1distance#function-x-center-offset)** The horizontal offset from the tracking center, right is +, left is - 
  * **[y_center_offset](/api/classes/classmik_1_1distance#function-y-center-offset)** The vertical offset from the tracking center, forward is +, backwards is - 


### function name

```cpp
const std::string name() const
```


**Return**: The name of the sensor, based on position 

### function position

```cpp
mik::distance_position position() const
```


**Return**: The position of the distance sensor. 

### function x_center_offset

```cpp
float x_center_offset() const
```


**Return**: The horizontal offset 

### function x_center_offset

```cpp
void x_center_offset(
    float new_offset
)
```


**Return**: Sets the vertical offset 

### function y_center_offset

```cpp
float y_center_offset() const
```


**Return**: The vertical offset 

### function y_center_offset

```cpp
void y_center_offset(
    float new_offset
)
```


**Return**: Sets the horizontal offset 

-------------------------------

Updated on 2026-03-02 at 17:21:01 -0600