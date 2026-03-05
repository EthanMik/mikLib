---
title: mik::button

---

# mik::button






`#include <button.h>`

Inherits from [mik::UI_component](/api/classes/classmik_1_1_u_i__component)

## Public Types

|                | Name           |
| -------------- | -------------- |
| enum class| **[button_state](/api/classes/classmik_1_1button#enum-button-state)** { INACTIVE, PRESSING, TRIGGERED} |

## Public Functions

|                | Name           |
| -------------- | -------------- |
| | **[button](/api/classes/classmik_1_1button#function-button)**(std::shared_ptr< [drawable](/api/classes/classmik_1_1drawable) > button_graphic, std::function< void()> on_click_func) |
| virtual int | **[get_height](/api/classes/classmik_1_1button#function-get-height)**() override |
| [button_state](/api/classes/classmik_1_1button#enum-button-state) | **[get_state](/api/classes/classmik_1_1button#function-get-state)**() |
| virtual int | **[get_width](/api/classes/classmik_1_1button#function-get-width)**() override |
| virtual int | **[get_x_pos](/api/classes/classmik_1_1button#function-get-x-pos)**() override |
| virtual int | **[get_y_pos](/api/classes/classmik_1_1button#function-get-y-pos)**() override |
| virtual void | **[is_pressing](/api/classes/classmik_1_1button#function-is-pressing)**([input_type](/api/namespaces/namespacemik#enum-input-type) input_type) override |
| void | **[is_pressing_controller](/api/classes/classmik_1_1button#function-is-pressing-controller)**() |
| void | **[is_pressing_touch](/api/classes/classmik_1_1button#function-is-pressing-touch)**() |
| virtual bool | **[needs_update](/api/classes/classmik_1_1button#function-needs-update)**() override |
| virtual void | **[render](/api/classes/classmik_1_1button#function-render)**() override |
| virtual void | **[set_callback](/api/classes/classmik_1_1button#function-set-callback)**(std::function< void()> cb, bool call_once =true) override |
| void | **[set_default_state](/api/classes/classmik_1_1button#function-set-default-state)**(std::shared_ptr< [drawable](/api/classes/classmik_1_1drawable) > default_state) |
| virtual void | **[set_position](/api/classes/classmik_1_1button#function-set-position)**(int x, int y) override |
| virtual void | **[set_states](/api/classes/classmik_1_1button#function-set-states)**(std::shared_ptr< [drawable](/api/classes/classmik_1_1drawable) > pressing_state, std::shared_ptr< [drawable](/api/classes/classmik_1_1drawable) > triggered_state) override |
| virtual void | **[set_x_pos](/api/classes/classmik_1_1button#function-set-x-pos)**(int x) override |
| virtual void | **[set_y_pos](/api/classes/classmik_1_1button#function-set-y-pos)**(int y) override |

## Additional inherited members

**Public Functions inherited from [mik::UI_component](/api/classes/classmik_1_1_u_i__component)**

|                | Name           |
| -------------- | -------------- |
| virtual void | **[blacklist_ID](/api/classes/classmik_1_1_u_i__component#function-blacklist-id)**() |
| virtual int | **[get_ID](/api/classes/classmik_1_1_u_i__component#function-get-id)**() const |
| virtual void | **[set_ID](/api/classes/classmik_1_1_u_i__component#function-set-id)**(int id) |
| virtual void | **[set_height](/api/classes/classmik_1_1_u_i__component#function-set-height)**(int h) |
| virtual void | **[set_width](/api/classes/classmik_1_1_u_i__component#function-set-width)**(int w) |
| virtual void | **[whitelist_ID](/api/classes/classmik_1_1_u_i__component#function-whitelist-id)**() |
| virtual | **[~UI_component](/api/classes/classmik_1_1_u_i__component#function-~ui-component)**() =default |

**Protected Attributes inherited from [mik::UI_component](/api/classes/classmik_1_1_u_i__component)**

|                | Name           |
| -------------- | -------------- |
| int | **[unique_id](/api/classes/classmik_1_1_u_i__component#variable-unique-id)**  |


## Public Types Documentation

### enum button_state

| Enumerator | Value | Description |
| ---------- | ----- | ----------- |
| INACTIVE | |   |
| PRESSING | |   |
| TRIGGERED | |   |




## Public Functions Documentation

### function button

```cpp
button(
    std::shared_ptr< drawable > button_graphic,
    std::function< void()> on_click_func
)
```


### function get_height

```cpp
virtual int get_height() override
```


**Reimplements**: [mik::UI_component::get_height](/api/classes/classmik_1_1_u_i__component#function-get-height)


### function get_state

```cpp
button_state get_state()
```


### function get_width

```cpp
virtual int get_width() override
```


**Reimplements**: [mik::UI_component::get_width](/api/classes/classmik_1_1_u_i__component#function-get-width)


### function get_x_pos

```cpp
virtual int get_x_pos() override
```


**Reimplements**: [mik::UI_component::get_x_pos](/api/classes/classmik_1_1_u_i__component#function-get-x-pos)


### function get_y_pos

```cpp
virtual int get_y_pos() override
```


**Reimplements**: [mik::UI_component::get_y_pos](/api/classes/classmik_1_1_u_i__component#function-get-y-pos)


### function is_pressing

```cpp
virtual void is_pressing(
    input_type input_type
) override
```


**Reimplements**: [mik::UI_component::is_pressing](/api/classes/classmik_1_1_u_i__component#function-is-pressing)


### function is_pressing_controller

```cpp
void is_pressing_controller()
```


### function is_pressing_touch

```cpp
void is_pressing_touch()
```


### function needs_update

```cpp
virtual bool needs_update() override
```


**Reimplements**: [mik::UI_component::needs_update](/api/classes/classmik_1_1_u_i__component#function-needs-update)


### function render

```cpp
virtual void render() override
```


**Reimplements**: [mik::UI_component::render](/api/classes/classmik_1_1_u_i__component#function-render)


### function set_callback

```cpp
virtual void set_callback(
    std::function< void()> cb,
    bool call_once =true
) override
```


**Reimplements**: [mik::UI_component::set_callback](/api/classes/classmik_1_1_u_i__component#function-set-callback)


### function set_default_state

```cpp
void set_default_state(
    std::shared_ptr< drawable > default_state
)
```


### function set_position

```cpp
virtual void set_position(
    int x,
    int y
) override
```


**Reimplements**: [mik::UI_component::set_position](/api/classes/classmik_1_1_u_i__component#function-set-position)


### function set_states

```cpp
virtual void set_states(
    std::shared_ptr< drawable > pressing_state,
    std::shared_ptr< drawable > triggered_state
) override
```


**Reimplements**: [mik::UI_component::set_states](/api/classes/classmik_1_1_u_i__component#function-set-states)


### function set_x_pos

```cpp
virtual void set_x_pos(
    int x
) override
```


**Reimplements**: [mik::UI_component::set_x_pos](/api/classes/classmik_1_1_u_i__component#function-set-x-pos)


### function set_y_pos

```cpp
virtual void set_y_pos(
    int y
) override
```


**Reimplements**: [mik::UI_component::set_y_pos](/api/classes/classmik_1_1_u_i__component#function-set-y-pos)


-------------------------------

Updated on 2026-03-02 at 17:21:01 -0600