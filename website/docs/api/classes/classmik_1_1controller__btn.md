---
title: mik::controller_btn

---

# mik::controller_btn






`#include <c_button.h>`

## Public Functions

|                | Name           |
| -------------- | -------------- |
| void | **[change_state](/api/classes/classmik_1_1controller__btn#function-change-state)**(bool is_pressed) |
| | **[controller_btn](/api/classes/classmik_1_1controller__btn#function-controller-btn)**(bool is_btn, std::string unpressed_state, std::string pressed_state, std::function< void()> callback) |
| | **[controller_btn](/api/classes/classmik_1_1controller__btn#function-controller-btn)**(bool really_stupid_exception_that_shouldnt_exist_but_i_dont_want_to_make_another_class, std::function< void()> callback) |
| void | **[disable_full_override](/api/classes/classmik_1_1controller__btn#function-disable-full-override)**() |
| void | **[enable_full_override](/api/classes/classmik_1_1controller__btn#function-enable-full-override)**(std::string lbl) |
| int | **[get_cycle_state](/api/classes/classmik_1_1controller__btn#function-get-cycle-state)**() |
| bool | **[get_state](/api/classes/classmik_1_1controller__btn#function-get-state)**() |
| std::string | **[get_state_label](/api/classes/classmik_1_1controller__btn#function-get-state-label)**() |
| bool | **[push](/api/classes/classmik_1_1controller__btn#function-push)**() |
| void | **[set_cycle_state](/api/classes/classmik_1_1controller__btn#function-set-cycle-state)**() |
| void | **[unpush](/api/classes/classmik_1_1controller__btn#function-unpush)**() |

## Public Functions Documentation

### function change_state

```cpp
void change_state(
    bool is_pressed
)
```


### function controller_btn

```cpp
controller_btn(
    bool is_btn,
    std::string unpressed_state,
    std::string pressed_state,
    std::function< void()> callback
)
```


### function controller_btn

```cpp
controller_btn(
    bool really_stupid_exception_that_shouldnt_exist_but_i_dont_want_to_make_another_class,
    std::function< void()> callback
)
```


### function disable_full_override

```cpp
void disable_full_override()
```


### function enable_full_override

```cpp
void enable_full_override(
    std::string lbl
)
```


### function get_cycle_state

```cpp
int get_cycle_state()
```


### function get_state

```cpp
bool get_state()
```


### function get_state_label

```cpp
std::string get_state_label()
```


### function push

```cpp
bool push()
```


### function set_cycle_state

```cpp
void set_cycle_state()
```


### function unpush

```cpp
void unpush()
```


-------------------------------

Updated on 2026-03-02 at 17:21:01 -0600