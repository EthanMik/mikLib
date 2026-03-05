---
title: mik::UI_config_screen

---

# mik::UI_config_screen






`#include <config_screen.h>`

## Public Functions

|                | Name           |
| -------------- | -------------- |
| | **[UI_config_screen](/api/classes/classmik_1_1_u_i__config__screen#function-ui-config-screen)**() |
| std::shared_ptr< [screen](/api/classes/classmik_1_1screen) > | **[get_config_screen](/api/classes/classmik_1_1_u_i__config__screen#function-get-config-screen)**() |

## Public Attributes

|                | Name           |
| -------------- | -------------- |
| std::shared_ptr< [UI_component](/api/classes/classmik_1_1_u_i__component) > | **[auto_skills_tgl](/api/classes/classmik_1_1_u_i__config__screen#variable-auto-skills-tgl)**  |
| std::function< void()> | **[func_task](/api/classes/classmik_1_1_u_i__config__screen#variable-func-task)**  |
| std::shared_ptr< [UI_component](/api/classes/classmik_1_1_u_i__component) > | **[time_cap_auto_tgl](/api/classes/classmik_1_1_u_i__config__screen#variable-time-cap-auto-tgl)**  |
| [textbox](/api/classes/classmik_1_1textbox) * | **[txtbox_task_data](/api/classes/classmik_1_1_u_i__config__screen#variable-txtbox-task-data)**  |

## Public Functions Documentation

### function UI_config_screen

```cpp
UI_config_screen()
```


### function get_config_screen

```cpp
std::shared_ptr< screen > get_config_screen()
```


## Public Attributes Documentation

### variable auto_skills_tgl

```cpp
std::shared_ptr< UI_component > auto_skills_tgl;
```


### variable func_task

```cpp
std::function< void()> func_task;
```


### variable time_cap_auto_tgl

```cpp
std::shared_ptr< UI_component > time_cap_auto_tgl;
```


### variable txtbox_task_data

```cpp
textbox * txtbox_task_data;
```


-------------------------------

Updated on 2026-03-02 at 17:21:01 -0600