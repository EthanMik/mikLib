#include "vex.h"

toggle::toggle(std::shared_ptr<drawable> toggle_graphic, std::shared_ptr<drawable> pressed_toggle_graphic) :
    toggle_graphic(toggle_graphic),
    pressed_toggle_graphic(pressed_toggle_graphic)
{
    this->x = get_x_pos();
    this->y = get_y_pos();
    this->w = get_width();
    this->h = get_height();
};

toggle::toggle(std::shared_ptr<drawable> toggle_graphic, std::shared_ptr<drawable> pressed_toggle_graphic, std::function<void()> callback) :
    toggle_graphic(toggle_graphic),
    pressed_toggle_graphic(pressed_toggle_graphic),
    callback(std::move(callback))
{
    this->x = get_x_pos();
    this->y = get_y_pos();
    this->w = get_width();
    this->h = get_height();
};

toggle::toggle(std::shared_ptr<drawable> toggle_graphic, std::shared_ptr<drawable> pressed_toggle_graphic, std::function<void()> callback, int id) :
    toggle_graphic(toggle_graphic),
    pressed_toggle_graphic(pressed_toggle_graphic),
    callback(std::move(callback)),
    id(id)
{
    if (id <= 0) { 
        Brain.Screen.printAt(30, 30, "CANNOT HAVE TOGGLE WITH ID 0 OR LESS"); 
        exit(1);
    }

    this->x = get_x_pos();
    this->y = get_y_pos();
    this->w = get_width();
    this->h = get_height();
};

int toggle::get_x_pos() { return(toggle_graphic->get_x_pos()); }
int toggle::get_y_pos() { return(toggle_graphic->get_y_pos()); }
int toggle::get_width() { return(toggle_graphic->get_width()); }
int toggle::get_height() { return(toggle_graphic->get_height()); }

void toggle::set_x_pos(int x) { 
    toggle_graphic->set_x_pos(x); 
    pressed_toggle_graphic->set_x_pos(x);
    pressed = false; 
    this->x = x;
}

void toggle::set_y_pos(int y) { 
    toggle_graphic->set_y_pos(y); 
    pressed_toggle_graphic->set_y_pos(y);
    pressed = false; 
    this->y = y;
}

void toggle::set_position(int x, int y) { 
    set_x_pos(x);
    set_y_pos(y);
}

void toggle::set_callback(std::function<void()> cb) {
    callback = cb;
}

void toggle::lock_toggle() { locked = true; }
void toggle::unlock_toggle() { locked = false; }

void toggle::render() {
    if (is_toggled) {
        pressed_toggle_graphic->render();
    } else {
        toggle_graphic->render();
    }
}

void toggle::is_pressing() {
    if (locked) { return; }
    
    float touch_x = Brain.Screen.xPosition();
    float touch_y = Brain.Screen.yPosition();
    bool is_touch_within_toggle = touch_x >= x && touch_x <= x + w && touch_y >= y && touch_y <= y + h;

    if (Brain.Screen.pressing()) {
        if (!pressed && is_touch_within_toggle) {
            pressed = true;
            render();
        } else if (pressed && !is_touch_within_toggle) {
            pressed = false;
            render();
        }
    } else if (pressed) {
        pressed = false;
        render();
        if (is_touch_within_toggle) {
            is_toggled = !is_toggled;
            execute();
        }
    }
}

void toggle::unpress() {
    locked = false;
    is_toggled = false;
    pressed = false;
}

void toggle::execute() {
    if (callback && is_toggled) {
        callback();
    }
}

bool toggle::get_toggle_state() {
    return(is_toggled);
}

int toggle::get_ID() {
    return(id);
}
