---
title: mik::group

---

# mik::group






`#include <group.h>`

Inherits from [mik::drawable](/api/classes/classmik_1_1drawable)

## Public Functions

|                | Name           |
| -------------- | -------------- |
| void | **[calculate_bounds](/api/classes/classmik_1_1group#function-calculate-bounds)**() |
| virtual int | **[get_height](/api/classes/classmik_1_1group#function-get-height)**() override |
| int | **[get_size](/api/classes/classmik_1_1group#function-get-size)**() |
| virtual int | **[get_width](/api/classes/classmik_1_1group#function-get-width)**() override |
| virtual int | **[get_x_pos](/api/classes/classmik_1_1group#function-get-x-pos)**() override |
| virtual int | **[get_y_pos](/api/classes/classmik_1_1group#function-get-y-pos)**() override |
| | **[group](/api/classes/classmik_1_1group#function-group)**() |
| | **[group](/api/classes/classmik_1_1group#function-group)**(std::shared_ptr< [drawable](/api/classes/classmik_1_1drawable) > graphic) |
| | **[group](/api/classes/classmik_1_1group#function-group)**(std::vector< std::shared_ptr< [drawable](/api/classes/classmik_1_1drawable) > > graphics) |
| virtual void | **[render](/api/classes/classmik_1_1group#function-render)**() override |
| virtual void | **[set_height](/api/classes/classmik_1_1group#function-set-height)**(int h) override |
| virtual void | **[set_position](/api/classes/classmik_1_1group#function-set-position)**(int x, int y) override |
| virtual void | **[set_width](/api/classes/classmik_1_1group#function-set-width)**(int w) override |
| virtual void | **[set_x_pos](/api/classes/classmik_1_1group#function-set-x-pos)**(int x) override |
| virtual void | **[set_y_pos](/api/classes/classmik_1_1group#function-set-y-pos)**(int y) override |

## Additional inherited members

**Public Functions inherited from [mik::drawable](/api/classes/classmik_1_1drawable)**

|                | Name           |
| -------------- | -------------- |
| virtual const std::string & | **[get_fill_color](/api/classes/classmik_1_1drawable#function-get-fill-color)**() |
| virtual std::string | **[get_text](/api/classes/classmik_1_1drawable#function-get-text)**() |
| virtual void | **[set_fill_color](/api/classes/classmik_1_1drawable#function-set-fill-color)**(const std::string & color) |
| virtual void | **[set_text](/api/classes/classmik_1_1drawable#function-set-text)**(const std::string text_label) |
| virtual | **[~drawable](/api/classes/classmik_1_1drawable#function-~drawable)**() =default |


## Public Functions Documentation

### function calculate_bounds

```cpp
void calculate_bounds()
```


### function get_height

```cpp
virtual int get_height() override
```


**Reimplements**: [mik::drawable::get_height](/api/classes/classmik_1_1drawable#function-get-height)


### function get_size

```cpp
int get_size()
```


### function get_width

```cpp
virtual int get_width() override
```


**Reimplements**: [mik::drawable::get_width](/api/classes/classmik_1_1drawable#function-get-width)


### function get_x_pos

```cpp
virtual int get_x_pos() override
```


**Reimplements**: [mik::drawable::get_x_pos](/api/classes/classmik_1_1drawable#function-get-x-pos)


### function get_y_pos

```cpp
virtual int get_y_pos() override
```


**Reimplements**: [mik::drawable::get_y_pos](/api/classes/classmik_1_1drawable#function-get-y-pos)


### function group

```cpp
group()
```


### function group

```cpp
group(
    std::shared_ptr< drawable > graphic
)
```


### function group

```cpp
group(
    std::vector< std::shared_ptr< drawable > > graphics
)
```


### function render

```cpp
virtual void render() override
```


**Reimplements**: [mik::drawable::render](/api/classes/classmik_1_1drawable#function-render)


### function set_height

```cpp
virtual void set_height(
    int h
) override
```


**Reimplements**: [mik::drawable::set_height](/api/classes/classmik_1_1drawable#function-set-height)


### function set_position

```cpp
virtual void set_position(
    int x,
    int y
) override
```


**Reimplements**: [mik::drawable::set_position](/api/classes/classmik_1_1drawable#function-set-position)


### function set_width

```cpp
virtual void set_width(
    int w
) override
```


**Reimplements**: [mik::drawable::set_width](/api/classes/classmik_1_1drawable#function-set-width)


### function set_x_pos

```cpp
virtual void set_x_pos(
    int x
) override
```


**Reimplements**: [mik::drawable::set_x_pos](/api/classes/classmik_1_1drawable#function-set-x-pos)


### function set_y_pos

```cpp
virtual void set_y_pos(
    int y
) override
```


**Reimplements**: [mik::drawable::set_y_pos](/api/classes/classmik_1_1drawable#function-set-y-pos)


-------------------------------

Updated on 2026-03-02 at 17:21:01 -0600