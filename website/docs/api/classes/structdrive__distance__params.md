---
title: drive_distance_params

---

# drive_distance_params






`#include <chassis.h>`

## Public Attributes

|                | Name           |
| -------------- | -------------- |
| [drive_constants](/api/classes/structdrive__constants) | **[drive_k](/api/classes/structdrive__distance__params#variable-drive-k)**  |
| float | **[heading](/api/classes/structdrive__distance__params#variable-heading)**  |
| [heading_constants](/api/classes/structheading__constants) | **[heading_k](/api/classes/structdrive__distance__params#variable-heading-k)**  |
| float | **[heading_max_voltage](/api/classes/structdrive__distance__params#variable-heading-max-voltage)**  |
| float | **[heading_slew](/api/classes/structdrive__distance__params#variable-heading-slew)**  |
| float | **[max_voltage](/api/classes/structdrive__distance__params#variable-max-voltage)**  |
| float | **[min_voltage](/api/classes/structdrive__distance__params#variable-min-voltage)**  |
| float | **[settle_error](/api/classes/structdrive__distance__params#variable-settle-error)**  |
| float | **[settle_time](/api/classes/structdrive__distance__params#variable-settle-time)**  |
| float | **[slew](/api/classes/structdrive__distance__params#variable-slew)**  |
| float | **[timeout](/api/classes/structdrive__distance__params#variable-timeout)**  |
| bool | **[wait](/api/classes/structdrive__distance__params#variable-wait)**  |

## Public Attributes Documentation

### variable drive_k

```cpp
drive_constants drive_k = drive_constants{};
```


### variable heading

```cpp
float heading = chassis.get_absolute_heading();
```


### variable heading_k

```cpp
heading_constants heading_k = heading_constants{};
```


### variable heading_max_voltage

```cpp
float heading_max_voltage = chassis.heading_max_voltage;
```


### variable heading_slew

```cpp
float heading_slew = chassis.heading_slew;
```


### variable max_voltage

```cpp
float max_voltage = chassis.drive_max_voltage;
```


### variable min_voltage

```cpp
float min_voltage = chassis.drive_min_voltage;
```


### variable settle_error

```cpp
float settle_error = chassis.drive_settle_error;
```


### variable settle_time

```cpp
float settle_time = chassis.drive_settle_time;
```


### variable slew

```cpp
float slew = chassis.drive_slew;
```


### variable timeout

```cpp
float timeout = chassis.drive_timeout;
```


### variable wait

```cpp
bool wait = true;
```


-------------------------------

Updated on 2026-03-02 at 17:21:01 -0600