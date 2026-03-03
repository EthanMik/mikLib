---
title: mik::UI_component

---

# mik::UI_component






`#include <UI_component.h>`

Inherited by [mik::background](/api/classes/classmik_1_1background), [mik::button](/api/classes/classmik_1_1button), [mik::graphic](/api/classes/classmik_1_1graphic), [mik::label](/api/classes/classmik_1_1label), [mik::textbox](/api/classes/classmik_1_1textbox), [mik::toggle](/api/classes/classmik_1_1toggle)

## Public Functions

|                | Name           |
| -------------- | -------------- |
| virtual void | **[blacklist_ID](/api/classes/classmik_1_1_u_i__component#function-blacklist-id)**() |
| virtual int | **[get_ID](/api/classes/classmik_1_1_u_i__component#function-get-id)**() const |
| virtual int | **[get_height](/api/classes/classmik_1_1_u_i__component#function-get-height)**() =0 |
| virtual int | **[get_width](/api/classes/classmik_1_1_u_i__component#function-get-width)**() =0 |
| virtual int | **[get_x_pos](/api/classes/classmik_1_1_u_i__component#function-get-x-pos)**() =0 |
| virtual int | **[get_y_pos](/api/classes/classmik_1_1_u_i__component#function-get-y-pos)**() =0 |
| virtual void | **[is_pressing](/api/classes/classmik_1_1_u_i__component#function-is-pressing)**([input_type](/api/namespaces/namespacemik#enum-input-type) input_type) |
| virtual bool | **[needs_update](/api/classes/classmik_1_1_u_i__component#function-needs-update)**() =0 |
| virtual void | **[render](/api/classes/classmik_1_1_u_i__component#function-render)**() =0 |
| virtual void | **[set_ID](/api/classes/classmik_1_1_u_i__component#function-set-id)**(int id) |
| virtual void | **[set_callback](/api/classes/classmik_1_1_u_i__component#function-set-callback)**(std::function< void()> cb, bool call_once =true) |
| virtual void | **[set_height](/api/classes/classmik_1_1_u_i__component#function-set-height)**(int h) |
| virtual void | **[set_position](/api/classes/classmik_1_1_u_i__component#function-set-position)**(int x, int y) =0 |
| virtual void | **[set_states](/api/classes/classmik_1_1_u_i__component#function-set-states)**(std::shared_ptr< [drawable](/api/classes/classmik_1_1drawable) > pressing, std::shared_ptr< [drawable](/api/classes/classmik_1_1drawable) > triggered) |
| virtual void | **[set_width](/api/classes/classmik_1_1_u_i__component#function-set-width)**(int w) |
| virtual void | **[set_x_pos](/api/classes/classmik_1_1_u_i__component#function-set-x-pos)**(int x) =0 |
| virtual void | **[set_y_pos](/api/classes/classmik_1_1_u_i__component#function-set-y-pos)**(int y) =0 |
| virtual void | **[whitelist_ID](/api/classes/classmik_1_1_u_i__component#function-whitelist-id)**() |
| virtual | **[~UI_component](/api/classes/classmik_1_1_u_i__component#function-~ui-component)**() =default |

## Protected Attributes

|                | Name           |
| -------------- | -------------- |
| int | **[unique_id](/api/classes/classmik_1_1_u_i__component#variable-unique-id)**  |

## Public Functions Documentation

### function blacklist_ID

```cpp
inline virtual void blacklist_ID()
```


### function get_ID

```cpp
inline virtual int get_ID() const
```


### function get_height

```cpp
virtual int get_height() =0
```


**Reimplemented by**: [mik::background::get_height](/api/classes/classmik_1_1background#function-get-height), [mik::button::get_height](/api/classes/classmik_1_1button#function-get-height), [mik::graphic::get_height](/api/classes/classmik_1_1graphic#function-get-height), [mik::label::get_height](/api/classes/classmik_1_1label#function-get-height), [mik::textbox::get_height](/api/classes/classmik_1_1textbox#function-get-height), [mik::toggle::get_height](/api/classes/classmik_1_1toggle#function-get-height)


### function get_width

```cpp
virtual int get_width() =0
```


**Reimplemented by**: [mik::background::get_width](/api/classes/classmik_1_1background#function-get-width), [mik::button::get_width](/api/classes/classmik_1_1button#function-get-width), [mik::graphic::get_width](/api/classes/classmik_1_1graphic#function-get-width), [mik::label::get_width](/api/classes/classmik_1_1label#function-get-width), [mik::textbox::get_width](/api/classes/classmik_1_1textbox#function-get-width), [mik::toggle::get_width](/api/classes/classmik_1_1toggle#function-get-width)


### function get_x_pos

```cpp
virtual int get_x_pos() =0
```


**Reimplemented by**: [mik::background::get_x_pos](/api/classes/classmik_1_1background#function-get-x-pos), [mik::button::get_x_pos](/api/classes/classmik_1_1button#function-get-x-pos), [mik::graphic::get_x_pos](/api/classes/classmik_1_1graphic#function-get-x-pos), [mik::label::get_x_pos](/api/classes/classmik_1_1label#function-get-x-pos), [mik::textbox::get_x_pos](/api/classes/classmik_1_1textbox#function-get-x-pos), [mik::toggle::get_x_pos](/api/classes/classmik_1_1toggle#function-get-x-pos)


### function get_y_pos

```cpp
virtual int get_y_pos() =0
```


**Reimplemented by**: [mik::background::get_y_pos](/api/classes/classmik_1_1background#function-get-y-pos), [mik::button::get_y_pos](/api/classes/classmik_1_1button#function-get-y-pos), [mik::graphic::get_y_pos](/api/classes/classmik_1_1graphic#function-get-y-pos), [mik::label::get_y_pos](/api/classes/classmik_1_1label#function-get-y-pos), [mik::textbox::get_y_pos](/api/classes/classmik_1_1textbox#function-get-y-pos), [mik::toggle::get_y_pos](/api/classes/classmik_1_1toggle#function-get-y-pos)


### function is_pressing

```cpp
inline virtual void is_pressing(
    input_type input_type
)
```


**Reimplemented by**: [mik::button::is_pressing](/api/classes/classmik_1_1button#function-is-pressing), [mik::toggle::is_pressing](/api/classes/classmik_1_1toggle#function-is-pressing)


### function needs_update

```cpp
virtual bool needs_update() =0
```


**Reimplemented by**: [mik::background::needs_update](/api/classes/classmik_1_1background#function-needs-update), [mik::button::needs_update](/api/classes/classmik_1_1button#function-needs-update), [mik::graphic::needs_update](/api/classes/classmik_1_1graphic#function-needs-update), [mik::label::needs_update](/api/classes/classmik_1_1label#function-needs-update), [mik::textbox::needs_update](/api/classes/classmik_1_1textbox#function-needs-update), [mik::toggle::needs_update](/api/classes/classmik_1_1toggle#function-needs-update)


### function render

```cpp
virtual void render() =0
```


**Reimplemented by**: [mik::background::render](/api/classes/classmik_1_1background#function-render), [mik::button::render](/api/classes/classmik_1_1button#function-render), [mik::graphic::render](/api/classes/classmik_1_1graphic#function-render), [mik::label::render](/api/classes/classmik_1_1label#function-render), [mik::textbox::render](/api/classes/classmik_1_1textbox#function-render), [mik::toggle::render](/api/classes/classmik_1_1toggle#function-render)


### function set_ID

```cpp
inline virtual void set_ID(
    int id
)
```


### function set_callback

```cpp
inline virtual void set_callback(
    std::function< void()> cb,
    bool call_once =true
)
```


**Reimplemented by**: [mik::button::set_callback](/api/classes/classmik_1_1button#function-set-callback), [mik::toggle::set_callback](/api/classes/classmik_1_1toggle#function-set-callback)


### function set_height

```cpp
inline virtual void set_height(
    int h
)
```


**Reimplemented by**: [mik::graphic::set_height](/api/classes/classmik_1_1graphic#function-set-height), [mik::textbox::set_height](/api/classes/classmik_1_1textbox#function-set-height)


### function set_position

```cpp
virtual void set_position(
    int x,
    int y
) =0
```


**Reimplemented by**: [mik::background::set_position](/api/classes/classmik_1_1background#function-set-position), [mik::button::set_position](/api/classes/classmik_1_1button#function-set-position), [mik::graphic::set_position](/api/classes/classmik_1_1graphic#function-set-position), [mik::label::set_position](/api/classes/classmik_1_1label#function-set-position), [mik::textbox::set_position](/api/classes/classmik_1_1textbox#function-set-position), [mik::toggle::set_position](/api/classes/classmik_1_1toggle#function-set-position)


### function set_states

```cpp
inline virtual void set_states(
    std::shared_ptr< drawable > pressing,
    std::shared_ptr< drawable > triggered
)
```


**Reimplemented by**: [mik::button::set_states](/api/classes/classmik_1_1button#function-set-states), [mik::toggle::set_states](/api/classes/classmik_1_1toggle#function-set-states)


### function set_width

```cpp
inline virtual void set_width(
    int w
)
```


**Reimplemented by**: [mik::graphic::set_width](/api/classes/classmik_1_1graphic#function-set-width), [mik::textbox::set_width](/api/classes/classmik_1_1textbox#function-set-width)


### function set_x_pos

```cpp
virtual void set_x_pos(
    int x
) =0
```


**Reimplemented by**: [mik::background::set_x_pos](/api/classes/classmik_1_1background#function-set-x-pos), [mik::button::set_x_pos](/api/classes/classmik_1_1button#function-set-x-pos), [mik::graphic::set_x_pos](/api/classes/classmik_1_1graphic#function-set-x-pos), [mik::label::set_x_pos](/api/classes/classmik_1_1label#function-set-x-pos), [mik::textbox::set_x_pos](/api/classes/classmik_1_1textbox#function-set-x-pos), [mik::toggle::set_x_pos](/api/classes/classmik_1_1toggle#function-set-x-pos)


### function set_y_pos

```cpp
virtual void set_y_pos(
    int y
) =0
```


**Reimplemented by**: [mik::background::set_y_pos](/api/classes/classmik_1_1background#function-set-y-pos), [mik::button::set_y_pos](/api/classes/classmik_1_1button#function-set-y-pos), [mik::graphic::set_y_pos](/api/classes/classmik_1_1graphic#function-set-y-pos), [mik::label::set_y_pos](/api/classes/classmik_1_1label#function-set-y-pos), [mik::textbox::set_y_pos](/api/classes/classmik_1_1textbox#function-set-y-pos), [mik::toggle::set_y_pos](/api/classes/classmik_1_1toggle#function-set-y-pos)


### function whitelist_ID

```cpp
inline virtual void whitelist_ID()
```


### function ~UI_component

```cpp
virtual ~UI_component() =default
```


## Protected Attributes Documentation

### variable unique_id

```cpp
int unique_id = -1;
```


-------------------------------

Updated on 2026-03-02 at 17:21:01 -0600