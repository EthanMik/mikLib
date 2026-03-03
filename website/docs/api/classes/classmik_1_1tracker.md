---
title: mik::tracker

---

# mik::tracker






`#include <tracker.h>`

## Public Functions

|                | Name           |
| -------------- | -------------- |
| float | **[angle](/api/classes/classmik_1_1tracker#function-angle)**(vex::rotationUnits units =vex::rotationUnits::deg)<br>Gets the angle of the tracker.  |
| int | **[index](/api/classes/classmik_1_1tracker#function-index)**() |
| bool | **[installed](/api/classes/classmik_1_1tracker#function-installed)**() |
| float | **[position](/api/classes/classmik_1_1tracker#function-position)**(vex::rotationUnits units)<br>Gets the current position of the tracker.  |
| void | **[resetPosition](/api/classes/classmik_1_1tracker#function-resetposition)**()<br>Resets the position of the tracker to the value of zero.  |
| void | **[setPosition](/api/classes/classmik_1_1tracker#function-setposition)**(float value, vex::rotationUnits units)<br>Sets the value of the tracker to the value specified in the parameter.  |
| | **[tracker](/api/classes/classmik_1_1tracker#function-tracker)**(int port)<br>Creates a new piston object on the port specified in the parameter.  |
| | **[tracker](/api/classes/classmik_1_1tracker#function-tracker)**(int expander_port, int port)<br>Creates a new piston object on a triport expander.  |

## Public Attributes

|                | Name           |
| -------------- | -------------- |
| bool | **[is_rev_encoder](/api/classes/classmik_1_1tracker#variable-is-rev-encoder)**  |

## Public Functions Documentation

### function angle

```cpp
float angle(
    vex::rotationUnits units =vex::rotationUnits::deg
)
```

Gets the angle of the tracker. 

**Parameters**: 

  * **units** The measurement unit for the encoder device. 


**Return**: Returns a float that represents the unit value specified by the parameter of the encoder sensor. 

### function index

```cpp
int index()
```


**Return**: The index of the tracker, 0 -> 21 for smart ports and -1 -> -8 for triports 

### function installed

```cpp
bool installed()
```


**Return**: True if the tracker is plugged in and working 

### function position

```cpp
float position(
    vex::rotationUnits units
)
```

Gets the current position of the tracker. 

**Parameters**: 

  * **units** The measurement unit for the position. 


**Return**: Returns a float that represents the current position of the encoder in the units defined in the parameter. 

### function resetPosition

```cpp
void resetPosition()
```

Resets the position of the tracker to the value of zero. 

### function setPosition

```cpp
void setPosition(
    float value,
    vex::rotationUnits units
)
```

Sets the value of the tracker to the value specified in the parameter. 

**Parameters**: 

  * **value** Sets the current position of the tracker. 
  * **units** The measurement unit for the position value. 


### function tracker

```cpp
tracker(
    int port
)
```

Creates a new piston object on the port specified in the parameter. 

**Parameters**: 

  * **port** Port in "PORT_A" or "PORT1". 


### function tracker

```cpp
tracker(
    int expander_port,
    int port
)
```

Creates a new piston object on a triport expander. 

**Parameters**: 

  * **expander_port** Port in "PORT1" format. 
  * **port** Triport in "PORT_A" format. 


## Public Attributes Documentation

### variable is_rev_encoder

```cpp
bool is_rev_encoder = false;
```


-------------------------------

Updated on 2026-03-02 at 17:21:01 -0600