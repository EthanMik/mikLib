#pragma once

#include "mikLib/ui.h"
#include "mikLib/Devices/motors.h"

namespace mik {

class UI_motors_screen {
public:
    UI_motors_screen();
    std::shared_ptr<screen> get_motors_screen();
    void update_motors_screen();
    void update_reconstruct_screen();
    void init_motors();
    void reconstruct_motor(mik::motor* mtr, int new_port, vex::gearSetting new_cart, bool new_rev);

private:
    void UI_crt_motors_scr();
    void UI_crt_reconstruct_scr();
    void crt_motor_btns(mik::motor* mtr, int x, int y);

    float set_voltage;
    std::vector<std::pair<mik::textbox*, mik::motor*>> motor_texts;
    std::vector<std::pair<mik::toggle*, char>> volt_toggles;
    struct motor_toggle_entry {
        mik::toggle* left_tgl;
        mik::toggle* right_tgl;
        mik::motor* mtr;
        bool was_spinning = false;
        bool user_stopped = false;
        bool user_pressed = false;
    };
    std::vector<motor_toggle_entry> motor_toggles;

    std::shared_ptr<screen> UI_motors_scr = nullptr;

    // Port screen

    mik::motor* selected_mtr = nullptr;
    struct port_buttons {
        mik::button* port_btn;
        mik::textbox* port_txt;
    };
    std::array<port_buttons, 21> port_button_list;
    mik::textbox* motor_label;
    std::shared_ptr<screen> UI_reconstruct_scr = nullptr;
    
};
}