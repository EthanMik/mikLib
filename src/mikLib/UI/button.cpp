#include "vex.h"

using namespace mik;

button::button(std::shared_ptr<drawable> button_graphic, std::function<void()> on_click_func) :
    button_graphic(button_graphic),
    on_click(std::move(on_click_func))
{    
    unique_id = UI_create_ID(UI_Button_ID);
    
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

    int delta_x = x - this->x;

    if (pressed_button_graphic) {
        pressed_button_graphic->set_x_pos(pressed_button_graphic->get_x_pos() + delta_x); 
    }
    if (triggered_button_graphic) {
        triggered_button_graphic->set_x_pos(triggered_button_graphic->get_x_pos() + delta_x);
    }

    needs_render_update = true;
    pressed = false; 
    this->x = x;
}

void button::set_y_pos(int y) { 
    button_graphic->set_y_pos(y);
    
    int delta_y = y - this->y;

    if (pressed_button_graphic) {
        pressed_button_graphic->set_y_pos(pressed_button_graphic->get_y_pos() + delta_y); 
    }
    if (triggered_button_graphic) {
        triggered_button_graphic->set_y_pos(triggered_button_graphic->get_y_pos() + delta_y);
    }

    needs_render_update = true;
    pressed = false; 
    this->y = y;
}

void button::set_position(int x, int y) { 
    set_x_pos(x);
    set_y_pos(y);
}

void button::set_states(std::shared_ptr<drawable> pressing_state, std::shared_ptr<drawable> triggered_state) {
    if (pressing_state) {
        pressed_button_graphic = pressing_state;
    }
    if (triggered_state) {
        triggered_button_graphic = triggered_state;
    }
}

void button::set_callback(std::function<void()> cb, bool call_once) {
    on_click = cb;
}

bool button::needs_update() {
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

void button::render() {
    switch (state)
    {
    case button_state::INACTIVE:
        button_graphic->render();
        break;    
    case button_state::PRESSING:
        if (pressed_button_graphic) {
            pressed_button_graphic->render();
        } else {
            button_graphic->render();
        }
        break;    
    case button_state::TRIGGERED:
        if (triggered_button_graphic) {
            triggered_button_graphic->render();
        } else {
            button_graphic->render();
        }
        break;    
    }
}

void button::is_pressing_touch() {
    if (cooldown && (int)Brain.Timer.time(vex::timeUnits::msec) - initial_msec <= cooldown_msec) {
        return;
    }
    cooldown = false;

    float touch_x = Brain.Screen.xPosition();
    float touch_y = Brain.Screen.yPosition();
    bool is_touch_within_button = touch_x >= x && touch_x <= x + w && touch_y >= y && touch_y <= y + h;
    
    if (Brain.Screen.pressing()) {
        if (!pressed && is_touch_within_button) {
            pressed = true;
            state = button_state::PRESSING;
        } else if (pressed && !is_touch_within_button) {
            pressed = false;
            state = button_state::INACTIVE;
        }
    } else if (pressed) {
        pressed = false;
        state = button_state::TRIGGERED;
        if (is_touch_within_button && on_click) {
            on_click();
        }
        cooldown = true;
        initial_msec = Brain.Timer.time(vex::timeUnits::msec);
    } else if (!pressed) {
        state = button_state::INACTIVE;
    }
}

void button::is_pressing_controller() {
    if (cooldown && (int)Brain.Timer.time(vex::timeUnits::msec) - initial_msec <= cooldown_msec) {
        return;
    }
    cooldown = false;


    float cursor_x = UI_get_cursor_x_position();
    float cursor_y = UI_get_cursor_y_position();
    bool is_cursor_within_button = cursor_x >= x && cursor_x <= x + w && cursor_y >= y && cursor_y <= y + h;
    
    if (Controller.ButtonB.pressing() && is_cursor_within_button) {
        state = button_state::TRIGGERED;
        if (is_cursor_within_button && on_click) {
            on_click();
        }
        cooldown = true;
        initial_msec = Brain.Timer.time(vex::timeUnits::msec);
    } else if (is_cursor_within_button) {
        state = button_state::PRESSING;
    } else if (!is_cursor_within_button) {
        state = button_state::INACTIVE;
    }
}

void button::is_pressing(input_type input_type) {
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