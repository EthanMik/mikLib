---
title: mik::UI_auton_screen

---

# mik::UI_auton_screen






`#include <auton_screen.h>`

## Public Functions

|                | Name           |
| -------------- | -------------- |
| | **[UI_auton_screen](/api/classes/classmik_1_1_u_i__auton__screen#function-ui-auton-screen)**() |
| void | **[UI_select_auton](/api/classes/classmik_1_1_u_i__auton__screen#function-ui-select-auton)**([mik::autons](/api/namespaces/namespacemik#enum-autons) auton)<br>Selects the auton used by the auton screen.  |
| void | **[disable_controller_overlay](/api/classes/classmik_1_1_u_i__auton__screen#function-disable-controller-overlay)**()<br>Disables controller auton selector, enables user control.  |
| void | **[enable_controller_overlay](/api/classes/classmik_1_1_u_i__auton__screen#function-enable-controller-overlay)**()<br>Enables controller auton selector, disables user control.  |
| void | **[enable_odom_display](/api/classes/classmik_1_1_u_i__auton__screen#function-enable-odom-display)**()<br>While auton test is running, coordinates of the robot will be shown.  |
| void | **[enable_time_limit](/api/classes/classmik_1_1_u_i__auton__screen#function-enable-time-limit)**()<br>When start auton test is ran the auto will cutoff when 15 second time limit is reached time limit is set to 60 seconds during skills.  |
| void | **[flip_toggle_controller](/api/classes/classmik_1_1_u_i__auton__screen#function-flip-toggle-controller)**(std::pair< int, int > cursor_position)<br>Internal use, updates controller buttons.  |
| void | **[flip_toggle_controller](/api/classes/classmik_1_1_u_i__auton__screen#function-flip-toggle-controller)**(std::pair< int, int > cursor_position, bool state)<br>Internal use, updates controller buttons.  |
| [mik::alliance_colors](/api/namespaces/namespacemik#enum-alliance-colors) | **[get_alliance_color](/api/classes/classmik_1_1_u_i__auton__screen#function-get-alliance-color)**()<br>Returns the selected color in the UI.  |
| std::shared_ptr< [screen](/api/classes/classmik_1_1screen) > | **[get_auton_screen](/api/classes/classmik_1_1_u_i__auton__screen#function-get-auton-screen)**() |
| void | **[save_auton_SD](/api/classes/classmik_1_1_u_i__auton__screen#function-save-auton-sd)**(int count =0)<br>Internal use, saves selected auton to SD.  |
| void | **[start_auton](/api/classes/classmik_1_1_u_i__auton__screen#function-start-auton)**()<br>Starts selected auton, used from [main.cpp](), disables controller overlay, and will calibrate if not already done do.  |
| void | **[start_auton_test](/api/classes/classmik_1_1_u_i__auton__screen#function-start-auton-test)**()<br>Runs the auto from the UI, user control is disabled, time is displayed, and current ran auto can be stopped by pressing the B button on controller.  |

## Public Attributes

|                | Name           |
| -------------- | -------------- |
| bool | **[odom_display](/api/classes/classmik_1_1_u_i__auton__screen#variable-odom-display)**  |
| bool | **[off_skills](/api/classes/classmik_1_1_u_i__auton__screen#variable-off-skills)**  |
| bool | **[time_limit](/api/classes/classmik_1_1_u_i__auton__screen#variable-time-limit)**  |
| int | **[var_num](/api/classes/classmik_1_1_u_i__auton__screen#variable-var-num)**  |

## Public Functions Documentation

### function UI_auton_screen

```cpp
UI_auton_screen()
```


### function UI_select_auton

```cpp
void UI_select_auton(
    mik::autons auton
)
```

Selects the auton used by the auton screen. 

### function disable_controller_overlay

```cpp
void disable_controller_overlay()
```

Disables controller auton selector, enables user control. 

### function enable_controller_overlay

```cpp
void enable_controller_overlay()
```

Enables controller auton selector, disables user control. 

### function enable_odom_display

```cpp
void enable_odom_display()
```

While auton test is running, coordinates of the robot will be shown. 

### function enable_time_limit

```cpp
void enable_time_limit()
```

When start auton test is ran the auto will cutoff when 15 second time limit is reached time limit is set to 60 seconds during skills. 

### function flip_toggle_controller

```cpp
void flip_toggle_controller(
    std::pair< int, int > cursor_position
)
```

Internal use, updates controller buttons. 

### function flip_toggle_controller

```cpp
void flip_toggle_controller(
    std::pair< int, int > cursor_position,
    bool state
)
```

Internal use, updates controller buttons. 

### function get_alliance_color

```cpp
mik::alliance_colors get_alliance_color()
```

Returns the selected color in the UI. 

### function get_auton_screen

```cpp
std::shared_ptr< screen > get_auton_screen()
```


**Return**: The auton screen object 

### function save_auton_SD

```cpp
void save_auton_SD(
    int count =0
)
```

Internal use, saves selected auton to SD. 

### function start_auton

```cpp
void start_auton()
```

Starts selected auton, used from [main.cpp](), disables controller overlay, and will calibrate if not already done do. 

### function start_auton_test

```cpp
void start_auton_test()
```

Runs the auto from the UI, user control is disabled, time is displayed, and current ran auto can be stopped by pressing the B button on controller. 

## Public Attributes Documentation

### variable odom_display

```cpp
bool odom_display = false;
```


### variable off_skills

```cpp
bool off_skills = false;
```


### variable time_limit

```cpp
bool time_limit = false;
```


### variable var_num

```cpp
int var_num = 1;
```


-------------------------------

Updated on 2026-03-02 at 17:21:00 -0600