---
title: swing_to_angle_params

---

# swing_to_angle_params






`#include <chassis.h>`

## Public Attributes

|                | Name           |
| -------------- | -------------- |
| [swing_constants](/api/classes/structswing__constants) | **[k](/api/classes/structswing__to__angle__params#variable-k)**  |
| float | **[max_voltage](/api/classes/structswing__to__angle__params#variable-max-voltage)**  |
| float | **[min_voltage](/api/classes/structswing__to__angle__params#variable-min-voltage)**  |
| float | **[opposite_voltage](/api/classes/structswing__to__angle__params#variable-opposite-voltage)**  |
| float | **[settle_error](/api/classes/structswing__to__angle__params#variable-settle-error)**  |
| float | **[settle_time](/api/classes/structswing__to__angle__params#variable-settle-time)**  |
| float | **[slew](/api/classes/structswing__to__angle__params#variable-slew)**  |
| float | **[timeout](/api/classes/structswing__to__angle__params#variable-timeout)**  |
| [mik::turn_direction](/api/namespaces/namespacemik#enum-turn-direction) | **[turn_direction](/api/classes/structswing__to__angle__params#variable-turn-direction)**  |
| bool | **[wait](/api/classes/structswing__to__angle__params#variable-wait)**  |

## Public Attributes Documentation

### variable k

```cpp
swing_constants k = swing_constants{};
```


### variable max_voltage

```cpp
float max_voltage = chassis.swing_max_voltage;
```


### variable min_voltage

```cpp
float min_voltage = chassis.swing_min_voltage;
```


### variable opposite_voltage

```cpp
float opposite_voltage = chassis.swing_opposite_voltage;
```


### variable settle_error

```cpp
float settle_error = chassis.swing_settle_error;
```


### variable settle_time

```cpp
float settle_time = chassis.swing_settle_time;
```


### variable slew

```cpp
float slew = chassis.swing_slew;
```


### variable timeout

```cpp
float timeout = chassis.swing_timeout;
```


### variable turn_direction

```cpp
mik::turn_direction turn_direction = mik::turn_direction::FASTEST;
```


### variable wait

```cpp
bool wait = true;
```


-------------------------------

Updated on 2026-03-02 at 17:21:01 -0600