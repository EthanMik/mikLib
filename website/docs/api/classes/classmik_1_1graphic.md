---
title: mik::graphic

---

# mik::graphic






`#include <graphic.h>`

Inherits from [mik::UI_component](/api/classes/classmik_1_1_u_i__component)

## Public Functions

|                | Name           |
| -------------- | -------------- |
| void | **[add_graphic](/api/classes/classmik_1_1graphic#function-add-graphic)**(std::shared_ptr< [drawable](/api/classes/classmik_1_1drawable) > graphic) |
| void | **[calculate_bounds](/api/classes/classmik_1_1graphic#function-calculate-bounds)**() |
| virtual int | **[get_height](/api/classes/classmik_1_1graphic#function-get-height)**() override |
| int | **[get_size](/api/classes/classmik_1_1graphic#function-get-size)**() |
| virtual int | **[get_width](/api/classes/classmik_1_1graphic#function-get-width)**() override |
| virtual int | **[get_x_pos](/api/classes/classmik_1_1graphic#function-get-x-pos)**() override |
| virtual int | **[get_y_pos](/api/classes/classmik_1_1graphic#function-get-y-pos)**() override |
| | **[graphic](/api/classes/classmik_1_1graphic#function-graphic)**() |
| | **[graphic](/api/classes/classmik_1_1graphic#function-graphic)**(std::shared_ptr< [drawable](/api/classes/classmik_1_1drawable) > graphic) |
| | **[graphic](/api/classes/classmik_1_1graphic#function-graphic)**(std::vector< std::shared_ptr< [drawable](/api/classes/classmik_1_1drawable) > > graphics) |
| virtual bool | **[needs_update](/api/classes/classmik_1_1graphic#function-needs-update)**() override |
| void | **[remove_first_graphic](/api/classes/classmik_1_1graphic#function-remove-first-graphic)**() |
| virtual void | **[render](/api/classes/classmik_1_1graphic#function-render)**() override |
| void | **[replace_graphic](/api/classes/classmik_1_1graphic#function-replace-graphic)**(std::shared_ptr< [drawable](/api/classes/classmik_1_1drawable) > graphic) |
| void | **[replace_graphic](/api/classes/classmik_1_1graphic#function-replace-graphic)**(std::vector< std::shared_ptr< [drawable](/api/classes/classmik_1_1drawable) > > graphic) |
| virtual void | **[set_height](/api/classes/classmik_1_1graphic#function-set-height)**(int h) override |
| virtual void | **[set_position](/api/classes/classmik_1_1graphic#function-set-position)**(int x, int y) override |
| virtual void | **[set_width](/api/classes/classmik_1_1graphic#function-set-width)**(int w) override |
| virtual void | **[set_x_pos](/api/classes/classmik_1_1graphic#function-set-x-pos)**(int x) override |
| virtual void | **[set_y_pos](/api/classes/classmik_1_1graphic#function-set-y-pos)**(int y) override |

## Additional inherited members

**Public Functions inherited from [mik::UI_component](/api/classes/classmik_1_1_u_i__component)**

|                | Name           |
| -------------- | -------------- |
| virtual void | **[blacklist_ID](/api/classes/classmik_1_1_u_i__component#function-blacklist-id)**() |
| virtual int | **[get_ID](/api/classes/classmik_1_1_u_i__component#function-get-id)**() const |
| virtual void | **[is_pressing](/api/classes/classmik_1_1_u_i__component#function-is-pressing)**([input_type](/api/namespaces/namespacemik#enum-input-type) input_type) |
| virtual void | **[set_ID](/api/classes/classmik_1_1_u_i__component#function-set-id)**(int id) |
| virtual void | **[set_callback](/api/classes/classmik_1_1_u_i__component#function-set-callback)**(std::function< void()> cb, bool call_once =true) |
| virtual void | **[set_states](/api/classes/classmik_1_1_u_i__component#function-set-states)**(std::shared_ptr< [drawable](/api/classes/classmik_1_1drawable) > pressing, std::shared_ptr< [drawable](/api/classes/classmik_1_1drawable) > triggered) |
| virtual void | **[whitelist_ID](/api/classes/classmik_1_1_u_i__component#function-whitelist-id)**() |
| virtual | **[~UI_component](/api/classes/classmik_1_1_u_i__component#function-~ui-component)**() =default |

**Protected Attributes inherited from [mik::UI_component](/api/classes/classmik_1_1_u_i__component)**

|                | Name           |
| -------------- | -------------- |
| int | **[unique_id](/api/classes/classmik_1_1_u_i__component#variable-unique-id)**  |


## Public Functions Documentation

### function add_graphic

```cpp
void add_graphic(
    std::shared_ptr< drawable > graphic
)
```


### function calculate_bounds

```cpp
void calculate_bounds()
```


### function get_height

```cpp
virtual int get_height() override
```


**Reimplements**: [mik::UI_component::get_height](/api/classes/classmik_1_1_u_i__component#function-get-height)


### function get_size

```cpp
int get_size()
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


### function graphic

```cpp
graphic()
```


### function graphic

```cpp
graphic(
    std::shared_ptr< drawable > graphic
)
```


### function graphic

```cpp
graphic(
    std::vector< std::shared_ptr< drawable > > graphics
)
```


### function needs_update

```cpp
virtual bool needs_update() override
```


**Reimplements**: [mik::UI_component::needs_update](/api/classes/classmik_1_1_u_i__component#function-needs-update)


### function remove_first_graphic

```cpp
void remove_first_graphic()
```


### function render

```cpp
virtual void render() override
```


**Reimplements**: [mik::UI_component::render](/api/classes/classmik_1_1_u_i__component#function-render)


### function replace_graphic

```cpp
void replace_graphic(
    std::shared_ptr< drawable > graphic
)
```


### function replace_graphic

```cpp
void replace_graphic(
    std::vector< std::shared_ptr< drawable > > graphic
)
```


### function set_height

```cpp
virtual void set_height(
    int h
) override
```


**Reimplements**: [mik::UI_component::set_height](/api/classes/classmik_1_1_u_i__component#function-set-height)


### function set_position

```cpp
virtual void set_position(
    int x,
    int y
) override
```


**Reimplements**: [mik::UI_component::set_position](/api/classes/classmik_1_1_u_i__component#function-set-position)


### function set_width

```cpp
virtual void set_width(
    int w
) override
```


**Reimplements**: [mik::UI_component::set_width](/api/classes/classmik_1_1_u_i__component#function-set-width)


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