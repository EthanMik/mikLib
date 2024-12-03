#include "vex.h"

button::button(std::shared_ptr<drawable> button_graphic, std::shared_ptr<drawable> pressed_button_graphic, std::function<void()> on_click_func) :
    button_graphic(button_graphic),
    pressed_button_graphic(pressed_button_graphic),
    on_click(std::move(on_click_func))
{    
    this->x = get_x_pos();
    this->y = get_y_pos();
    this->w = get_width();
    this->h = get_height();
};

int button::get_x_pos() { return(button_graphic->get_x_pos()); }
int button::get_y_pos() { return(button_graphic->get_y_pos()); }
int button::get_width() { return(button_graphic->get_width()); }
int button::get_height() { return(button_graphic->get_height()); }

void button::set_x_pos(int x) { 
    button_graphic->set_x_pos(x);
    pressed_button_graphic->set_x_pos(x); 
    pressed = false; 
    this->x = x;
}

void button::set_y_pos(int y) { 
    button_graphic->set_y_pos(y); 
    pressed_button_graphic->set_y_pos(y); 
    pressed = false; 
    this->y = y;
}

void button::set_position(int x, int y) { 
    set_x_pos(x);
    set_y_pos(y);
}

void button::render() {
    if (pressed) {
        pressed_button_graphic->render();
    } else {
        button_graphic->render();
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