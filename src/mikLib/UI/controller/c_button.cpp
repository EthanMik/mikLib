#include "mikLib/ui.h"

using namespace mik;

controller_btn::controller_btn(bool is_btn, std::string unpressed_state, std::string pressed_state, std::function<void()> callback) :
    is_btn(is_btn), unpressed_state(unpressed_state), pressed_state(pressed_state), callback(callback)
{
    state_label = unpressed_state;
};

controller_btn::controller_btn(bool really_stupid_exception_that_shouldnt_exist_but_i_dont_want_to_make_another_class, std::function<void()> callback) :
    callback(callback), exception(really_stupid_exception_that_shouldnt_exist_but_i_dont_want_to_make_another_class)
{
    cycle_state_num = auton_scr->var_num;
    state_label = "[" + to_string(cycle_state_num) + "]";
};

std::string controller_btn::get_state_label() { return state_label; }
bool controller_btn::get_state() { 
    if (exception) {
        return exception;
    }
    return state;
}
void controller_btn::unpush() { state = true; push(); }
void controller_btn::enable_full_override(std::string lbl) { state_label = lbl; full_override = true; }
void controller_btn::change_state(bool is_pressed) {
    if (is_pressed) {
        state = true;
        state_label = pressed_state;
    } else {
        state = false;
        state_label = unpressed_state;
    }
}
void controller_btn::disable_full_override() { 
    full_override = false;
    if (state) {
        state_label = pressed_state;
    } else {
        state_label = unpressed_state;
    } 
}

bool controller_btn::push() {
    if (full_override) {
        return false;
    }
    if (exception) {
        callback();
        cycle_state_num = auton_scr->var_num;
        state_label = "[" + to_string(cycle_state_num) + "]";
        return false;
    }

    state = !state;
    if (state) {
        state_label = pressed_state;
    } else {
        state_label = unpressed_state;
    }
    if (is_btn && state) {
        state_label = unpressed_state;
        state = false;
        callback();
        return state;
    }
    callback();

    return state;
}

void controller_btn::set_cycle_state() {
    if (exception) {
        cycle_state_num = auton_scr->var_num;
        state_label = "[" + to_string(cycle_state_num) + "]";
    }
}

int controller_btn::get_cycle_state() {
    return cycle_state_num;
}
