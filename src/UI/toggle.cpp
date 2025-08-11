#include "vex.h"

using namespace mik;

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

    int delta_x = x - this->x;

    if (toggled_graphic) {
        toggled_graphic->set_x_pos(toggled_graphic->get_x_pos() + delta_x);
    }
    if (pressing_toggle_graphic) {
        pressing_toggle_graphic->set_x_pos(pressing_toggle_graphic->get_x_pos() + delta_x);
    }

    needs_render_update = true;
    pressed = false; 
    this->x = x;
}

void toggle::set_y_pos(int y) { 
    toggle_graphic->set_y_pos(y); 

    int delta_y = y - this->y;

    if (toggled_graphic) {
        toggled_graphic->set_y_pos(toggled_graphic->get_y_pos() + delta_y);
    }
    if (pressing_toggle_graphic) {
        pressing_toggle_graphic->set_y_pos(pressing_toggle_graphic->get_y_pos() + delta_y);
    }

    needs_render_update = true;
    pressed = false; 
    this->y = y;
}

void toggle::set_position(int x, int y) { 
    set_x_pos(x);
    set_y_pos(y);
}

void toggle::set_callback(std::function<void()> cb, bool call_once) {
    callback = cb;
    this->call_once = call_once;
}
void toggle::set_states(std::shared_ptr<drawable> pressing_state, std::shared_ptr<drawable> triggered) {
    pressing_toggle_graphic = pressing_state; 
    toggled_graphic = triggered; 
}

bool toggle::is_locked() { return locked; }
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

void toggle::is_pressing(input_type input_type) {
    switch (input_type)
    {
    case input_type::CONTROLLER:
        is_pressing_controller();
        break;
    case input_type::TOUCHSCREEN:
        is_pressing_touch();
        break;
    }
}

void toggle::is_pressing_touch() {
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

        } else if (pressed && !is_touch_within_toggle) {
            pressed = false;
            state = toggle_state::INACTIVE;
        }
        
    } else if (pressed && is_touch_within_toggle) {
            pressed = false;

            if (toggled_graphic && !is_toggled) {
                state = toggle_state::TOGGLED;
            } else {
                state = toggle_state::INACTIVE;
            } 

            is_toggled = !is_toggled;
            execute();
    } else if (!is_touch_within_toggle) {
        if (is_toggled) {
            state = toggle_state::TOGGLED;
        } else {
            state = toggle_state::INACTIVE;
        } 
    }
}

void toggle::is_pressing_controller() {
    if (locked) { return; }
    if (cooldown && (int)Brain.Timer.time(vex::timeUnits::msec) - initial_msec <= cooldown_msec) {
        return;
    }
    cooldown = false;

    float cursor_x = UI_get_cursor_x_position();
    float cursor_y = UI_get_cursor_y_position();
    bool is_cursor_within_toggle = cursor_x >= x && cursor_x <= x + w && cursor_y >= y && cursor_y <= y + h;
    
    if (Controller.ButtonB.pressing() && is_cursor_within_toggle) {
        if (!is_toggled) {
            state = toggle_state::TOGGLED;
        } else {
            state = toggle_state::INACTIVE;
        } 

        is_toggled = !is_toggled;
        execute();

        cooldown = true;
        initial_msec = Brain.Timer.time(vex::timeUnits::msec);
    } else if (is_cursor_within_toggle) {
        state = toggle_state::PRESSING;
    } else if (!is_cursor_within_toggle) {
        if (is_toggled) {
            state = toggle_state::TOGGLED;
        } else {
            state = toggle_state::INACTIVE;
        } 
    }

}

void toggle::unpress() {
    locked = false;
    is_toggled = false;
    pressed = false;
    state = toggle_state::INACTIVE;
}

void toggle::press() {
    locked = false;
    is_toggled = true;
    pressed = false;
    state = toggle_state::TOGGLED;
}

void toggle::execute() {
    if (callback && !call_once) {
        callback();
        return;
    }
    if (callback && is_toggled) {
        callback();
    }
}

bool toggle::get_toggle_state() {
    return(is_toggled);
}