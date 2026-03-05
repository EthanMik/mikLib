---
title: mik::UI_console_screen

---

# mik::UI_console_screen






`#include <console_screen.h>`

## Public Functions

|                | Name           |
| -------------- | -------------- |
| | **[UI_console_screen](/api/classes/classmik_1_1_u_i__console__screen#function-ui-console-screen)**() |
| void | **[add](/api/classes/classmik_1_1_u_i__console__screen#function-add)**(const std::string & label_text, bool txt) |
| template <typename F \> <br>void | **[add](/api/classes/classmik_1_1_u_i__console__screen#function-add)**(const std::string & label_text, F && data) |
| template <typename F \> <br>void | **[add](/api/classes/classmik_1_1_u_i__console__screen#function-add)**(F && data) |
| template <typename T \> <br>void | **[add](/api/classes/classmik_1_1_u_i__console__screen#function-add)**(const std::string & label_text, T & data) |
| template <typename T \> <br>void | **[add](/api/classes/classmik_1_1_u_i__console__screen#function-add)**(T & data) |
| std::shared_ptr< [screen](/api/classes/classmik_1_1screen) > | **[get_console_screen](/api/classes/classmik_1_1_u_i__console__screen#function-get-console-screen)**() |
| void | **[reset](/api/classes/classmik_1_1_u_i__console__screen#function-reset)**() |

## Public Attributes

|                | Name           |
| -------------- | -------------- |
| std::shared_ptr< [screen](/api/classes/classmik_1_1screen) > | **[UI_console_scr](/api/classes/classmik_1_1_u_i__console__screen#variable-ui-console-scr)**  |

## Public Functions Documentation

### function UI_console_screen

```cpp
UI_console_screen()
```


### function add

```cpp
void add(
    const std::string & label_text,
    bool txt
)
```


### function add

```cpp
template <typename F >
void add(
    const std::string & label_text,
    F && data
)
```


### function add

```cpp
template <typename F >
void add(
    F && data
)
```


### function add

```cpp
template <typename T >
void add(
    const std::string & label_text,
    T & data
)
```


### function add

```cpp
template <typename T >
void add(
    T & data
)
```


### function get_console_screen

```cpp
std::shared_ptr< screen > get_console_screen()
```


### function reset

```cpp
void reset()
```


## Public Attributes Documentation

### variable UI_console_scr

```cpp
std::shared_ptr< screen > UI_console_scr;
```


-------------------------------

Updated on 2026-03-02 at 17:21:01 -0600