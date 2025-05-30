#pragma once

#include "vex.h"

class UI_config_screen {
public:
    UI_config_screen();
    std::shared_ptr<screen> get_config_screen();

    textbox* txtbox_task_data;
    std::function<void()> func_task;
private:
    void countdown(std::shared_ptr<UI_component> txtbox, std::function<void()> func);

    void UI_crt_config_scr();
    void UI_crt_pnematics_scr();
    
    std::shared_ptr<screen> UI_config_scr = nullptr;
    std::shared_ptr<screen> UI_pnematics_scr = nullptr;
};