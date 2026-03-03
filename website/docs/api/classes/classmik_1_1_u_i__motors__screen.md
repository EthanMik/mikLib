---
title: mik::UI_motors_screen

---

# mik::UI_motors_screen






`#include <motors_screen.h>`

## Public Functions

|                | Name           |
| -------------- | -------------- |
| | **[UI_motors_screen](/api/classes/classmik_1_1_u_i__motors__screen#function-ui-motors-screen)**() |
| std::shared_ptr< [screen](/api/classes/classmik_1_1screen) > | **[get_motors_screen](/api/classes/classmik_1_1_u_i__motors__screen#function-get-motors-screen)**() |
| void | **[init_motors](/api/classes/classmik_1_1_u_i__motors__screen#function-init-motors)**() |
| void | **[reconstruct_motor](/api/classes/classmik_1_1_u_i__motors__screen#function-reconstruct-motor)**([mik::motor](/api/classes/classmik_1_1motor) * mtr, int new_port, vex::gearSetting new_cart, bool new_rev) |
| void | **[update_motors_screen](/api/classes/classmik_1_1_u_i__motors__screen#function-update-motors-screen)**() |
| void | **[update_reconstruct_screen](/api/classes/classmik_1_1_u_i__motors__screen#function-update-reconstruct-screen)**() |

## Public Functions Documentation

### function UI_motors_screen

```cpp
UI_motors_screen()
```


### function get_motors_screen

```cpp
std::shared_ptr< screen > get_motors_screen()
```


### function init_motors

```cpp
void init_motors()
```


### function reconstruct_motor

```cpp
void reconstruct_motor(
    mik::motor * mtr,
    int new_port,
    vex::gearSetting new_cart,
    bool new_rev
)
```


### function update_motors_screen

```cpp
void update_motors_screen()
```


### function update_reconstruct_screen

```cpp
void update_reconstruct_screen()
```


-------------------------------

Updated on 2026-03-02 at 17:21:01 -0600