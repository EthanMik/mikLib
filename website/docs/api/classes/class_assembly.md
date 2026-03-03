---
title: Assembly

---

# Assembly






`#include <assembly.h>`

## Public Functions

|                | Name           |
| -------------- | -------------- |
| void | **[control](/api/classes/class_assembly#function-control)**() |
| void | **[init](/api/classes/class_assembly#function-init)**() |
| void | **[lower_intake_control](/api/classes/class_assembly#function-lower-intake-control)**() |
| void | **[scraper_piston_control](/api/classes/class_assembly#function-scraper-piston-control)**() |
| void | **[upper_intake_control](/api/classes/class_assembly#function-upper-intake-control)**() |
| void | **[wing_piston_control](/api/classes/class_assembly#function-wing-piston-control)**() |

## Public Attributes

|                | Name           |
| -------------- | -------------- |
| vex::limit | **[limit_switch](/api/classes/class_assembly#variable-limit-switch)**  |
| [mik::motor_group](/api/classes/classmik_1_1motor__group) | **[lower_intake_motors](/api/classes/class_assembly#variable-lower-intake-motors)**  |
| vex::optical | **[optical_sensor](/api/classes/class_assembly#variable-optical-sensor)**  |
| vex::rotation | **[rotation_sensor](/api/classes/class_assembly#variable-rotation-sensor)**  |
| [mik::piston](/api/classes/classmik_1_1piston) | **[scraper_piston](/api/classes/class_assembly#variable-scraper-piston)**  |
| [mik::motor](/api/classes/classmik_1_1motor) | **[upper_intake_motor](/api/classes/class_assembly#variable-upper-intake-motor)**  |
| [mik::piston](/api/classes/classmik_1_1piston) | **[wing_piston](/api/classes/class_assembly#variable-wing-piston)**  |

## Public Functions Documentation

### function control

```cpp
void control()
```


### function init

```cpp
void init()
```


### function lower_intake_control

```cpp
void lower_intake_control()
```


### function scraper_piston_control

```cpp
void scraper_piston_control()
```


### function upper_intake_control

```cpp
void upper_intake_control()
```


### function wing_piston_control

```cpp
void wing_piston_control()
```


## Public Attributes Documentation

### variable limit_switch

```cpp
static vex::limit limit_switch;
```


### variable lower_intake_motors

```cpp
static mik::motor_group lower_intake_motors;
```


### variable optical_sensor

```cpp
static vex::optical optical_sensor;
```


### variable rotation_sensor

```cpp
static vex::rotation rotation_sensor;
```


### variable scraper_piston

```cpp
static mik::piston scraper_piston;
```


### variable upper_intake_motor

```cpp
static mik::motor upper_intake_motor;
```


### variable wing_piston

```cpp
static mik::piston wing_piston;
```


-------------------------------

Updated on 2026-03-02 at 17:21:00 -0600