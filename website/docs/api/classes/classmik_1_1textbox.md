---
title: mik::textbox

---

# mik::textbox






`#include <textbox.h>`

Inherits from [mik::UI_component](/api/classes/classmik_1_1_u_i__component)

## Public Functions

|                | Name           |
| -------------- | -------------- |
| virtual int | **[get_height](/api/classes/classmik_1_1textbox#function-get-height)**() override |
| std::string | **[get_text](/api/classes/classmik_1_1textbox#function-get-text)**() |
| const std::string & | **[get_text_color](/api/classes/classmik_1_1textbox#function-get-text-color)**() |
| virtual int | **[get_width](/api/classes/classmik_1_1textbox#function-get-width)**() override |
| virtual int | **[get_x_pos](/api/classes/classmik_1_1textbox#function-get-x-pos)**() override |
| virtual int | **[get_y_pos](/api/classes/classmik_1_1textbox#function-get-y-pos)**() override |
| virtual bool | **[needs_update](/api/classes/classmik_1_1textbox#function-needs-update)**() override |
| virtual void | **[render](/api/classes/classmik_1_1textbox#function-render)**() override |
| virtual void | **[set_height](/api/classes/classmik_1_1textbox#function-set-height)**(int h) override |
| virtual void | **[set_position](/api/classes/classmik_1_1textbox#function-set-position)**(int x, int y) override |
| void | **[set_text](/api/classes/classmik_1_1textbox#function-set-text)**(std::string text) |
| void | **[set_text_color](/api/classes/classmik_1_1textbox#function-set-text-color)**(const std::string & color) |
| virtual void | **[set_width](/api/classes/classmik_1_1textbox#function-set-width)**(int w) override |
| virtual void | **[set_x_pos](/api/classes/classmik_1_1textbox#function-set-x-pos)**(int x) override |
| virtual void | **[set_y_pos](/api/classes/classmik_1_1textbox#function-set-y-pos)**(int y) override |
| | **[textbox](/api/classes/classmik_1_1textbox#function-textbox)**(std::string text, std::shared_ptr< [drawable](/api/classes/classmik_1_1drawable) > box, vex::fontType font, int padding =10) |
| | **[textbox](/api/classes/classmik_1_1textbox#function-textbox)**(std::string text, [text_align](/api/namespaces/namespacemik#enum-text-align) text_alignment, std::shared_ptr< [drawable](/api/classes/classmik_1_1drawable) > box, vex::fontType font, int padding =10) |
| | **[textbox](/api/classes/classmik_1_1textbox#function-textbox)**(std::string text, [text_align](/api/namespaces/namespacemik#enum-text-align) text_alignment, const std::string & bg_color, std::shared_ptr< [drawable](/api/classes/classmik_1_1drawable) > box, vex::fontType font, int padding =10) |
| | **[textbox](/api/classes/classmik_1_1textbox#function-textbox)**(std::string text, const std::string & text_color, const std::string & bg_color, [text_align](/api/namespaces/namespacemik#enum-text-align) text_alignment, std::shared_ptr< [drawable](/api/classes/classmik_1_1drawable) > box, vex::fontType font, int padding =10) |
| void | **[wrap_text](/api/classes/classmik_1_1textbox#function-wrap-text)**() |

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

### function get_height

```cpp
virtual int get_height() override
```


**Reimplements**: [mik::UI_component::get_height](/api/classes/classmik_1_1_u_i__component#function-get-height)


### function get_text

```cpp
std::string get_text()
```


### function get_text_color

```cpp
const std::string & get_text_color()
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


### function set_text

```cpp
void set_text(
    std::string text
)
```


### function set_text_color

```cpp
void set_text_color(
    const std::string & color
)
```


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


### function textbox

```cpp
textbox(
    std::string text,
    std::shared_ptr< drawable > box,
    vex::fontType font,
    int padding =10
)
```


### function textbox

```cpp
textbox(
    std::string text,
    text_align text_alignment,
    std::shared_ptr< drawable > box,
    vex::fontType font,
    int padding =10
)
```


### function textbox

```cpp
textbox(
    std::string text,
    text_align text_alignment,
    const std::string & bg_color,
    std::shared_ptr< drawable > box,
    vex::fontType font,
    int padding =10
)
```


### function textbox

```cpp
textbox(
    std::string text,
    const std::string & text_color,
    const std::string & bg_color,
    text_align text_alignment,
    std::shared_ptr< drawable > box,
    vex::fontType font,
    int padding =10
)
```


### function wrap_text

```cpp
void wrap_text()
```


-------------------------------

Updated on 2026-03-02 at 17:21:01 -0600