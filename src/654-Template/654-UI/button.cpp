#include "vex.h"

button::button(std::shared_ptr<drawable> button_graphic, std::function<void()> on_click_func) :
    button_graphic(button_graphic),
    on_click(std::move(on_click_func))
{    
    unique_id = UI_create_ID(4);
    
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

    if (pressed_button_graphic) {
        pressed_button_graphic->set_x_pos(x); 
    }
    if (triggered_button_graphic) {
        triggered_button_graphic->set_x_pos(x);
    }

    needs_render_update = true;
    pressed = false; 
    this->x = x;
}

void button::set_y_pos(int y) { 
    button_graphic->set_y_pos(y);

    if (pressed_button_graphic) {
        pressed_button_graphic->set_y_pos(y); 
    }
    if (triggered_button_graphic) {
        triggered_button_graphic->set_y_pos(y);
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
    if (triggered_button_graphic) {
        triggered_button_graphic = triggered_state;
    }
}

void button::set_callback(std::function<void()> cb) {
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

void button::is_pressing() {
    float touch_x = Brain.Screen.xPosition();
    float touch_y = Brain.Screen.yPosition();
    bool is_touch_within_button = touch_x >= x && touch_x <= x + w && touch_y >= y && touch_y <= y + h;

    if (Brain.Screen.pressing()) {
        if (!pressed && is_touch_within_button) {
            pressed = true;
            state = button_state::PRESSING;
            render();
        } else if (pressed && !is_touch_within_button) {
            pressed = false;
            state = button_state::INACTIVE;
            render();
        }
    } else if (pressed) {
        pressed = false;
        state = button_state::TRIGGERED;
        render();
        if (is_touch_within_button && on_click) {
            on_click();
        }
    }
    if (!pressed) {
        state = button_state::INACTIVE;
        render();
    }
}