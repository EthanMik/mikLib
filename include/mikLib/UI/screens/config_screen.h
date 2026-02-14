#pragma once

#include "mikLib/ui.h"

namespace mik {

class UI_config_screen {
public:
    UI_config_screen();
    std::shared_ptr<screen> get_config_screen();

    textbox* txtbox_task_data;
    std::function<void()> func_task;
    std::shared_ptr<UI_component> auto_skills_tgl;
    std::shared_ptr<UI_component> time_cap_auto_tgl;
private:
    enum class slot { MACRO, DATA, TEST };


    std::shared_ptr<UI_component> add_button(slot slot, std::string label, std::function<void()> func, bool button);
    std::shared_ptr<UI_component> add_button(slot slot, std::string label, std::function<void(std::shared_ptr<UI_component>)> func, bool button);
    std::shared_ptr<UI_component> add_toggle(slot slot, std::string label, std::function<void()> func);
    void countdown(std::shared_ptr<UI_component> txtbox, std::function<void()> func);
    void swap_mode(std::shared_ptr<UI_component> txtbox, bool mode);

    void UI_crt_config_scr();
    void UI_crt_pnematics_scr();

    int macro_row = 1;
    int data_row = 1;
    int test_row = 1;

    std::shared_ptr<screen> UI_config_scr = nullptr;
    std::shared_ptr<screen> UI_pnematics_scr = nullptr;
    std::shared_ptr<screen> UI_motor_scr = nullptr;
};
}