---
title: turn_to_angle_params

---

# turn_to_angle_params






`#include <chassis.h>`

## Public Attributes

|                | Name           |
| -------------- | -------------- |
| [turn_constants](/api/classes/structturn__constants) | **[k](/api/classes/structturn__to__angle__params#variable-k)**  |
| float | **[max_voltage](/api/classes/structturn__to__angle__params#variable-max-voltage)**  |
| float | **[min_voltage](/api/classes/structturn__to__angle__params#variable-min-voltage)**  |
| float | **[settle_error](/api/classes/structturn__to__angle__params#variable-settle-error)**  |
| float | **[settle_time](/api/classes/structturn__to__angle__params#variable-settle-time)**  |
| float | **[slew](/api/classes/structturn__to__angle__params#variable-slew)**  |
| float | **[timeout](/api/classes/structturn__to__angle__params#variable-timeout)**  |
| [mik::turn_direction](/api/namespaces/namespacemik#enum-turn-direction) | **[turn_direction](/api/classes/structturn__to__angle__params#variable-turn-direction)**  |
| bool | **[wait](/api/classes/structturn__to__angle__params#variable-wait)**  |

## Public Attributes Documentation

### variable k

```cpp
turn_constants k = turn_constants{};
```


### variable max_voltage

```cpp
float max_voltage = chassis.turn_max_voltage;
```


### variable min_voltage

```cpp
float min_voltage = chassis.turn_min_voltage;
```


### variable settle_error

```cpp
float settle_error = chassis.turn_settle_error;
```


### variable settle_time

```cpp
float settle_time = chassis.turn_settle_time;
```


### variable slew

```cpp
float slew = chassis.turn_slew;
```


### variable timeout

```cpp
float timeout = chassis.turn_timeout;
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