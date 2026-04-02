#pragma once
#include "mikLib/ui.h"
#include <string>
#include <functional>

namespace mik
{

class controller_btn {
public:
    controller_btn(bool is_btn, std::string unpressed_state, std::string pressed_state, std::function<void()> callback);
    controller_btn(bool really_stupid_exception_that_shouldnt_exist_but_i_dont_want_to_make_another_class, std::function<void()> callback);
    bool push();
    void unpush();
    void change_state(bool is_pressed);
    void set_cycle_state();
    void enable_full_override(std::string lbl);
    void disable_full_override();
    std::string get_state_label();
    bool get_state();
    int get_cycle_state();
private:
    bool is_btn;
    bool state = false;
    std::string state_label;
    std::string unpressed_state;
    std::string pressed_state;
    std::function<void()> callback;
    bool exception = false;
    int cycle_state_num;
    bool full_override = false;
};

}
