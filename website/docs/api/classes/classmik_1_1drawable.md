---
title: mik::drawable

---

# mik::drawable






`#include <drawable.h>`

Inherited by [mik::circle](/api/classes/classmik_1_1circle), [mik::group](/api/classes/classmik_1_1group), [mik::image](/api/classes/classmik_1_1image), [mik::line](/api/classes/classmik_1_1line), [mik::pixel](/api/classes/classmik_1_1pixel), [mik::rectangle](/api/classes/classmik_1_1rectangle), [mik::text](/api/classes/classmik_1_1text)

## Public Functions

|                | Name           |
| -------------- | -------------- |
| virtual const std::string & | **[get_fill_color](/api/classes/classmik_1_1drawable#function-get-fill-color)**() |
| virtual int | **[get_height](/api/classes/classmik_1_1drawable#function-get-height)**() =0 |
| virtual std::string | **[get_text](/api/classes/classmik_1_1drawable#function-get-text)**() |
| virtual int | **[get_width](/api/classes/classmik_1_1drawable#function-get-width)**() =0 |
| virtual int | **[get_x_pos](/api/classes/classmik_1_1drawable#function-get-x-pos)**() =0 |
| virtual int | **[get_y_pos](/api/classes/classmik_1_1drawable#function-get-y-pos)**() =0 |
| virtual void | **[render](/api/classes/classmik_1_1drawable#function-render)**() =0 |
| virtual void | **[set_fill_color](/api/classes/classmik_1_1drawable#function-set-fill-color)**(const std::string & color) |
| virtual void | **[set_height](/api/classes/classmik_1_1drawable#function-set-height)**(int h) =0 |
| virtual void | **[set_position](/api/classes/classmik_1_1drawable#function-set-position)**(int x, int y) =0 |
| virtual void | **[set_text](/api/classes/classmik_1_1drawable#function-set-text)**(const std::string text_label) |
| virtual void | **[set_width](/api/classes/classmik_1_1drawable#function-set-width)**(int w) =0 |
| virtual void | **[set_x_pos](/api/classes/classmik_1_1drawable#function-set-x-pos)**(int x) =0 |
| virtual void | **[set_y_pos](/api/classes/classmik_1_1drawable#function-set-y-pos)**(int y) =0 |
| virtual | **[~drawable](/api/classes/classmik_1_1drawable#function-~drawable)**() =default |

## Public Functions Documentation

### function get_fill_color

```cpp
inline virtual const std::string & get_fill_color()
```


**Reimplemented by**: [mik::rectangle::get_fill_color](/api/classes/classmik_1_1rectangle#function-get-fill-color)


### function get_height

```cpp
virtual int get_height() =0
```


**Reimplemented by**: [mik::circle::get_height](/api/classes/classmik_1_1circle#function-get-height), [mik::group::get_height](/api/classes/classmik_1_1group#function-get-height), [mik::image::get_height](/api/classes/classmik_1_1image#function-get-height), [mik::line::get_height](/api/classes/classmik_1_1line#function-get-height), [mik::pixel::get_height](/api/classes/classmik_1_1pixel#function-get-height), [mik::rectangle::get_height](/api/classes/classmik_1_1rectangle#function-get-height), [mik::text::get_height](/api/classes/classmik_1_1text#function-get-height)


### function get_text

```cpp
inline virtual std::string get_text()
```


**Reimplemented by**: [mik::text::get_text](/api/classes/classmik_1_1text#function-get-text)


### function get_width

```cpp
virtual int get_width() =0
```


**Reimplemented by**: [mik::circle::get_width](/api/classes/classmik_1_1circle#function-get-width), [mik::group::get_width](/api/classes/classmik_1_1group#function-get-width), [mik::image::get_width](/api/classes/classmik_1_1image#function-get-width), [mik::line::get_width](/api/classes/classmik_1_1line#function-get-width), [mik::pixel::get_width](/api/classes/classmik_1_1pixel#function-get-width), [mik::rectangle::get_width](/api/classes/classmik_1_1rectangle#function-get-width), [mik::text::get_width](/api/classes/classmik_1_1text#function-get-width)


### function get_x_pos

```cpp
virtual int get_x_pos() =0
```


**Reimplemented by**: [mik::circle::get_x_pos](/api/classes/classmik_1_1circle#function-get-x-pos), [mik::group::get_x_pos](/api/classes/classmik_1_1group#function-get-x-pos), [mik::image::get_x_pos](/api/classes/classmik_1_1image#function-get-x-pos), [mik::line::get_x_pos](/api/classes/classmik_1_1line#function-get-x-pos), [mik::pixel::get_x_pos](/api/classes/classmik_1_1pixel#function-get-x-pos), [mik::rectangle::get_x_pos](/api/classes/classmik_1_1rectangle#function-get-x-pos), [mik::text::get_x_pos](/api/classes/classmik_1_1text#function-get-x-pos)


### function get_y_pos

```cpp
virtual int get_y_pos() =0
```


**Reimplemented by**: [mik::circle::get_y_pos](/api/classes/classmik_1_1circle#function-get-y-pos), [mik::group::get_y_pos](/api/classes/classmik_1_1group#function-get-y-pos), [mik::image::get_y_pos](/api/classes/classmik_1_1image#function-get-y-pos), [mik::line::get_y_pos](/api/classes/classmik_1_1line#function-get-y-pos), [mik::pixel::get_y_pos](/api/classes/classmik_1_1pixel#function-get-y-pos), [mik::rectangle::get_y_pos](/api/classes/classmik_1_1rectangle#function-get-y-pos), [mik::text::get_y_pos](/api/classes/classmik_1_1text#function-get-y-pos)


### function render

```cpp
virtual void render() =0
```


**Reimplemented by**: [mik::circle::render](/api/classes/classmik_1_1circle#function-render), [mik::group::render](/api/classes/classmik_1_1group#function-render), [mik::image::render](/api/classes/classmik_1_1image#function-render), [mik::line::render](/api/classes/classmik_1_1line#function-render), [mik::pixel::render](/api/classes/classmik_1_1pixel#function-render), [mik::rectangle::render](/api/classes/classmik_1_1rectangle#function-render), [mik::text::render](/api/classes/classmik_1_1text#function-render)


### function set_fill_color

```cpp
inline virtual void set_fill_color(
    const std::string & color
)
```


**Reimplemented by**: [mik::rectangle::set_fill_color](/api/classes/classmik_1_1rectangle#function-set-fill-color), [mik::text::set_fill_color](/api/classes/classmik_1_1text#function-set-fill-color)


### function set_height

```cpp
virtual void set_height(
    int h
) =0
```


**Reimplemented by**: [mik::circle::set_height](/api/classes/classmik_1_1circle#function-set-height), [mik::group::set_height](/api/classes/classmik_1_1group#function-set-height), [mik::image::set_height](/api/classes/classmik_1_1image#function-set-height), [mik::line::set_height](/api/classes/classmik_1_1line#function-set-height), [mik::pixel::set_height](/api/classes/classmik_1_1pixel#function-set-height), [mik::rectangle::set_height](/api/classes/classmik_1_1rectangle#function-set-height), [mik::text::set_height](/api/classes/classmik_1_1text#function-set-height)


### function set_position

```cpp
virtual void set_position(
    int x,
    int y
) =0
```


**Reimplemented by**: [mik::circle::set_position](/api/classes/classmik_1_1circle#function-set-position), [mik::group::set_position](/api/classes/classmik_1_1group#function-set-position), [mik::image::set_position](/api/classes/classmik_1_1image#function-set-position), [mik::line::set_position](/api/classes/classmik_1_1line#function-set-position), [mik::pixel::set_position](/api/classes/classmik_1_1pixel#function-set-position), [mik::rectangle::set_position](/api/classes/classmik_1_1rectangle#function-set-position), [mik::text::set_position](/api/classes/classmik_1_1text#function-set-position)


### function set_text

```cpp
inline virtual void set_text(
    const std::string text_label
)
```


**Reimplemented by**: [mik::text::set_text](/api/classes/classmik_1_1text#function-set-text)


### function set_width

```cpp
virtual void set_width(
    int w
) =0
```


**Reimplemented by**: [mik::circle::set_width](/api/classes/classmik_1_1circle#function-set-width), [mik::group::set_width](/api/classes/classmik_1_1group#function-set-width), [mik::image::set_width](/api/classes/classmik_1_1image#function-set-width), [mik::line::set_width](/api/classes/classmik_1_1line#function-set-width), [mik::pixel::set_width](/api/classes/classmik_1_1pixel#function-set-width), [mik::rectangle::set_width](/api/classes/classmik_1_1rectangle#function-set-width), [mik::text::set_width](/api/classes/classmik_1_1text#function-set-width)


### function set_x_pos

```cpp
virtual void set_x_pos(
    int x
) =0
```


**Reimplemented by**: [mik::circle::set_x_pos](/api/classes/classmik_1_1circle#function-set-x-pos), [mik::group::set_x_pos](/api/classes/classmik_1_1group#function-set-x-pos), [mik::image::set_x_pos](/api/classes/classmik_1_1image#function-set-x-pos), [mik::line::set_x_pos](/api/classes/classmik_1_1line#function-set-x-pos), [mik::pixel::set_x_pos](/api/classes/classmik_1_1pixel#function-set-x-pos), [mik::rectangle::set_x_pos](/api/classes/classmik_1_1rectangle#function-set-x-pos), [mik::text::set_x_pos](/api/classes/classmik_1_1text#function-set-x-pos)


### function set_y_pos

```cpp
virtual void set_y_pos(
    int y
) =0
```


**Reimplemented by**: [mik::circle::set_y_pos](/api/classes/classmik_1_1circle#function-set-y-pos), [mik::group::set_y_pos](/api/classes/classmik_1_1group#function-set-y-pos), [mik::image::set_y_pos](/api/classes/classmik_1_1image#function-set-y-pos), [mik::line::set_y_pos](/api/classes/classmik_1_1line#function-set-y-pos), [mik::pixel::set_y_pos](/api/classes/classmik_1_1pixel#function-set-y-pos), [mik::rectangle::set_y_pos](/api/classes/classmik_1_1rectangle#function-set-y-pos), [mik::text::set_y_pos](/api/classes/classmik_1_1text#function-set-y-pos)


### function ~drawable

```cpp
virtual ~drawable() =default
```


-------------------------------

Updated on 2026-03-02 at 17:21:01 -0600