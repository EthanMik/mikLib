#include "vex.h"

toggle::toggle(std::shared_ptr<drawable> toggle_graphic) :
    toggle_graphic(toggle_graphic)
{
    unique_id = UI_create_ID(UI_Toggle_ID);

    this->x = get_x_pos();
    this->y = get_y_pos();
    this->w = get_width();
    this->h = get_height();
};

toggle::toggle(std::shared_ptr<drawable> toggle_graphic, std::function<void()> callback) :
    toggle_graphic(toggle_graphic),
    callback(std::move(callback))
{
    unique_id = UI_create_ID(UI_Toggle_ID);
    
    this->x = get_x_pos();
    this->y = get_y_pos();
    this->w = get_width();
    this->h = get_height();
};

toggle::toggle(std::shared_ptr<drawable> toggle_graphic, std::function<void()> callback, int id) :
    toggle_graphic(toggle_graphic),
    callback(std::move(callback)),
    id(id)
{
    unique_id = UI_create_ID(UI_Toggle_ID, id);

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

    if (toggled_graphic) {
        toggled_graphic->set_x_pos(x);
    }
    if (pressing_toggle_graphic) {
        pressing_toggle_graphic->set_x_pos(x);
    }

    needs_render_update = true;
    pressed = false; 
    this->x = x;
}

void toggle::set_y_pos(int y) { 
    toggle_graphic->set_y_pos(y); 

    if (toggled_graphic) {
        toggled_graphic->set_y_pos(y);
    }
    if (pressing_toggle_graphic) {
        pressing_toggle_graphic->set_y_pos(y);
    }

    needs_render_update = true;
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
void toggle::set_states(std::shared_ptr<drawable> pressing_state, std::shared_ptr<drawable> triggered) {
    pressing_toggle_graphic = pressing_state; 
    toggled_graphic = triggered; 
}

void toggle::lock_toggle() { locked = true; }
void toggle::unlock_toggle() { locked = false; }

bool toggle::needs_update() {
    if (state != prev_state) {
        needs_render_update = true;
    }
    prev_state = state;

    if (needs_render_update) {
        needs_render_update = false;
        return true;
    }
    return false;
}

void toggle::render() {
    switch (state)
    {
    case toggle_state::INACTIVE:
        toggle_graphic->render();
        break;    
    case toggle_state::PRESSING:
        if (pressing_toggle_graphic) {
            pressing_toggle_graphic->render();
        } else {
            toggle_graphic->render();
        }
        break;    
    case toggle_state::TOGGLED:
        if (toggled_graphic) {
            toggled_graphic->render();
        } else {
            toggle_graphic->render();
        }
        break;    
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

            if (pressing_toggle_graphic) {
                state = toggle_state::PRESSING;
            }

            render();
        } else if (pressed && !is_touch_within_toggle) {
            pressed = false;
            state = toggle_state::INACTIVE;
            render();
        }
    } else if (pressed && is_touch_within_toggle) {
            pressed = false;

            if (toggled_graphic && !is_toggled) {
                state = toggle_state::TOGGLED;
            } else {
                state = toggle_state::INACTIVE;
            } 

            render();

            is_toggled = !is_toggled;
            execute();
    }
}

void toggle::unpress() {
    locked = false;
    is_toggled = false;
    pressed = false;
    state = toggle_state::INACTIVE;
}

void toggle::execute() {
    if (callback && is_toggled) {
        callback();
    }
}

bool toggle::get_toggle_state() {
    return(is_toggled);
}