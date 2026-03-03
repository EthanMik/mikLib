---
title: mik::screen

---

# mik::screen






`#include <screen.h>`

## Public Types

|                | Name           |
| -------------- | -------------- |
| enum class| **[alignment](/api/classes/classmik_1_1screen#enum-alignment)** { BOTTOM, LEFT, RIGHT, TOP} |

## Public Functions

|                | Name           |
| -------------- | -------------- |
| void | **[add_UI_component](/api/classes/classmik_1_1screen#function-add-ui-component)**(std::shared_ptr< [UI_component](/api/classes/classmik_1_1_u_i__component) > component) |
| void | **[add_UI_components](/api/classes/classmik_1_1screen#function-add-ui-components)**(std::vector< std::shared_ptr< [UI_component](/api/classes/classmik_1_1_u_i__component) > > components) |
| void | **[add_render_callback](/api/classes/classmik_1_1screen#function-add-render-callback)**(std::function< void()> render_callback) |
| void | **[add_scroll_bar](/api/classes/classmik_1_1screen#function-add-scroll-bar)**(std::shared_ptr< [drawable](/api/classes/classmik_1_1drawable) > scroll_bar) |
| void | **[add_scroll_bar](/api/classes/classmik_1_1screen#function-add-scroll-bar)**(std::shared_ptr< [drawable](/api/classes/classmik_1_1drawable) > scroll_bar, [alignment](/api/classes/classmik_1_1screen#enum-alignment) scroll_bar_align) |
| const std::vector< std::shared_ptr< [UI_component](/api/classes/classmik_1_1_u_i__component) > > | **[get_UI_components](/api/classes/classmik_1_1screen#function-get-ui-components)**() |
| int | **[get_component_delta_pos](/api/classes/classmik_1_1screen#function-get-component-delta-pos)**() |
| int | **[get_height](/api/classes/classmik_1_1screen#function-get-height)**() |
| int | **[get_width](/api/classes/classmik_1_1screen#function-get-width)**() |
| int | **[get_x_pos](/api/classes/classmik_1_1screen#function-get-x-pos)**() |
| int | **[get_y_pos](/api/classes/classmik_1_1screen#function-get-y-pos)**() |
| bool | **[needs_full_refresh](/api/classes/classmik_1_1screen#function-needs-full-refresh)**() |
| bool | **[needs_update](/api/classes/classmik_1_1screen#function-needs-update)**() |
| void | **[refresh](/api/classes/classmik_1_1screen#function-refresh)**() |
| void | **[remove_UI_component](/api/classes/classmik_1_1screen#function-remove-ui-component)**(std::vector< int > id) |
| void | **[render](/api/classes/classmik_1_1screen#function-render)**(bool full_refresh) |
| | **[screen](/api/classes/classmik_1_1screen#function-screen)**(int x, int y, int w, int h) |
| void | **[set_UI_components](/api/classes/classmik_1_1screen#function-set-ui-components)**(std::vector< std::shared_ptr< [UI_component](/api/classes/classmik_1_1_u_i__component) > > components) |
| void | **[set_height](/api/classes/classmik_1_1screen#function-set-height)**(int h) |
| void | **[set_width](/api/classes/classmik_1_1screen#function-set-width)**(int w) |
| void | **[set_x_pos](/api/classes/classmik_1_1screen#function-set-x-pos)**(int x) |
| void | **[set_y_pos](/api/classes/classmik_1_1screen#function-set-y-pos)**(int y) |

## Public Attributes

|                | Name           |
| -------------- | -------------- |
| bool | **[lazy_render](/api/classes/classmik_1_1screen#variable-lazy-render)**  |

## Public Types Documentation

### enum alignment

| Enumerator | Value | Description |
| ---------- | ----- | ----------- |
| BOTTOM | |   |
| LEFT | |   |
| RIGHT | |   |
| TOP | |   |




## Public Functions Documentation

### function add_UI_component

```cpp
void add_UI_component(
    std::shared_ptr< UI_component > component
)
```


### function add_UI_components

```cpp
void add_UI_components(
    std::vector< std::shared_ptr< UI_component > > components
)
```


### function add_render_callback

```cpp
void add_render_callback(
    std::function< void()> render_callback
)
```


### function add_scroll_bar

```cpp
void add_scroll_bar(
    std::shared_ptr< drawable > scroll_bar
)
```


### function add_scroll_bar

```cpp
void add_scroll_bar(
    std::shared_ptr< drawable > scroll_bar,
    alignment scroll_bar_align
)
```


### function get_UI_components

```cpp
const std::vector< std::shared_ptr< UI_component > > get_UI_components()
```


### function get_component_delta_pos

```cpp
int get_component_delta_pos()
```


### function get_height

```cpp
int get_height()
```


### function get_width

```cpp
int get_width()
```


### function get_x_pos

```cpp
int get_x_pos()
```


### function get_y_pos

```cpp
int get_y_pos()
```


### function needs_full_refresh

```cpp
bool needs_full_refresh()
```


### function needs_update

```cpp
bool needs_update()
```


### function refresh

```cpp
void refresh()
```


### function remove_UI_component

```cpp
void remove_UI_component(
    std::vector< int > id
)
```


### function render

```cpp
void render(
    bool full_refresh
)
```


### function screen

```cpp
screen(
    int x,
    int y,
    int w,
    int h
)
```


### function set_UI_components

```cpp
void set_UI_components(
    std::vector< std::shared_ptr< UI_component > > components
)
```


### function set_height

```cpp
void set_height(
    int h
)
```


### function set_width

```cpp
void set_width(
    int w
)
```


### function set_x_pos

```cpp
void set_x_pos(
    int x
)
```


### function set_y_pos

```cpp
void set_y_pos(
    int y
)
```


## Public Attributes Documentation

### variable lazy_render

```cpp
bool lazy_render = false;
```


-------------------------------

Updated on 2026-03-02 at 17:21:01 -0600