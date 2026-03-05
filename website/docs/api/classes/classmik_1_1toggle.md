---
title: mik::toggle

---

# mik::toggle






`#include <toggle.h>`

Inherits from [mik::UI_component](/api/classes/classmik_1_1_u_i__component)

## Public Functions

|                | Name           |
| -------------- | -------------- |
| void | **[execute](/api/classes/classmik_1_1toggle#function-execute)**() |
| virtual int | **[get_height](/api/classes/classmik_1_1toggle#function-get-height)**() override |
| bool | **[get_toggle_state](/api/classes/classmik_1_1toggle#function-get-toggle-state)**() |
| virtual int | **[get_width](/api/classes/classmik_1_1toggle#function-get-width)**() override |
| virtual int | **[get_x_pos](/api/classes/classmik_1_1toggle#function-get-x-pos)**() override |
| virtual int | **[get_y_pos](/api/classes/classmik_1_1toggle#function-get-y-pos)**() override |
| bool | **[is_locked](/api/classes/classmik_1_1toggle#function-is-locked)**() |
| virtual void | **[is_pressing](/api/classes/classmik_1_1toggle#function-is-pressing)**([input_type](/api/namespaces/namespacemik#enum-input-type) input_type) override |
| void | **[is_pressing_controller](/api/classes/classmik_1_1toggle#function-is-pressing-controller)**() |
| void | **[is_pressing_touch](/api/classes/classmik_1_1toggle#function-is-pressing-touch)**() |
| void | **[lock_toggle](/api/classes/classmik_1_1toggle#function-lock-toggle)**() |
| virtual bool | **[needs_update](/api/classes/classmik_1_1toggle#function-needs-update)**() override |
| void | **[press](/api/classes/classmik_1_1toggle#function-press)**() |
| virtual void | **[render](/api/classes/classmik_1_1toggle#function-render)**() override |
| virtual void | **[set_callback](/api/classes/classmik_1_1toggle#function-set-callback)**(std::function< void()> cb, bool call_once =true) override |
| virtual void | **[set_position](/api/classes/classmik_1_1toggle#function-set-position)**(int x, int y) override |
| virtual void | **[set_states](/api/classes/classmik_1_1toggle#function-set-states)**(std::shared_ptr< [drawable](/api/classes/classmik_1_1drawable) > pressing_state, std::shared_ptr< [drawable](/api/classes/classmik_1_1drawable) > triggered) override |
| virtual void | **[set_x_pos](/api/classes/classmik_1_1toggle#function-set-x-pos)**(int x) override |
| virtual void | **[set_y_pos](/api/classes/classmik_1_1toggle#function-set-y-pos)**(int y) override |
| | **[toggle](/api/classes/classmik_1_1toggle#function-toggle)**(std::shared_ptr< [drawable](/api/classes/classmik_1_1drawable) > toggle_graphic, std::function< void()> callback, int id) |
| | **[toggle](/api/classes/classmik_1_1toggle#function-toggle)**(std::shared_ptr< [drawable](/api/classes/classmik_1_1drawable) > toggle_graphic, std::function< void()> callback) |
| | **[toggle](/api/classes/classmik_1_1toggle#function-toggle)**(std::shared_ptr< [drawable](/api/classes/classmik_1_1drawable) > toggle_graphic) |
| void | **[unlock_toggle](/api/classes/classmik_1_1toggle#function-unlock-toggle)**() |
| void | **[unpress](/api/classes/classmik_1_1toggle#function-unpress)**() |

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


## Public Functions Documentation

### function execute

```cpp
void execute()
```


### function get_height

```cpp
virtual int get_height() override
```


**Reimplements**: [mik::UI_component::get_height](/api/classes/classmik_1_1_u_i__component#function-get-height)


### function get_toggle_state

```cpp
bool get_toggle_state()
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


### function is_locked

```cpp
bool is_locked()
```


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


### function lock_toggle

```cpp
void lock_toggle()
```


### function needs_update

```cpp
virtual bool needs_update() override
```


**Reimplements**: [mik::UI_component::needs_update](/api/classes/classmik_1_1_u_i__component#function-needs-update)


### function press

```cpp
void press()
```


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
    std::shared_ptr< drawable > triggered
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


### function toggle

```cpp
toggle(
    std::shared_ptr< drawable > toggle_graphic,
    std::function< void()> callback,
    int id
)
```


### function toggle

```cpp
toggle(
    std::shared_ptr< drawable > toggle_graphic,
    std::function< void()> callback
)
```


### function toggle

```cpp
toggle(
    std::shared_ptr< drawable > toggle_graphic
)
```


### function unlock_toggle

```cpp
void unlock_toggle()
```


### function unpress

```cpp
void unpress()
```


-------------------------------

Updated on 2026-03-02 at 17:21:01 -0600