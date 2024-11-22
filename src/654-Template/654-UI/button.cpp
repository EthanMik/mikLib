#include "vex.h"

button::button(const std::string& button_file_name, const std::string& pressed_button_file_name, int x, int y, int w, int h, distance_units units, std::function<void()> on_click) :
    button_file_name(button_file_name),
    pressed_button_file_name(pressed_button_file_name),
    x(x),
    y(y),
    w(w),
    h(h),
    units(units),
    on_click(on_click)
{
    this->x = to_pixels(x, units);
    this->y = to_pixels(y, units);
    this->w = to_pixels(w, units);
    this->h = to_pixels(h, units);
};

int button::get_x_pos() { return(x); }
int button::get_y_pos() { return(y); }
int button::get_w_pos() { return(w); }
int button::get_h_pos() { return(h); }
void button::set_x_pos(int x) { this->x = x; }
void button::set_y_pos(int y) { this->y = y; }

void button::render() {
    if (pressed) {
        Brain.Screen.drawImageFromFile(pressed_button_file_name.c_str(), x, y);
    }
    else {
        Brain.Screen.drawImageFromFile(button_file_name.c_str(), x, y);
    }
}

void button::is_pressing() {
    float touch_x = Brain.Screen.xPosition();
    float touch_y = Brain.Screen.yPosition();
    bool is_touch_within_button = touch_x >= x && touch_x <= x + w && touch_y >= y && touch_y <= y + h;

    if (Brain.Screen.pressing()) {
        if (!pressed && is_touch_within_button) {
            pressed = true;
            render();
        } else if (pressed && !is_touch_within_button) {
            pressed = false;
            render();
        }
    } else if (pressed) {
        pressed = false;
        render();
        if (is_touch_within_button && on_click) {
            on_click();
        }
    }
}