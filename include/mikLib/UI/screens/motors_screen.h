#pragma once

#include "mikLib/ui.h"
#include "mikLib/Devices/motors.h"

namespace mik {

class UI_motors_screen {
public:
    UI_motors_screen();
    std::shared_ptr<screen> get_motors_screen();
    void update_motors_screen();
    void init_motors();

private:
    void UI_crt_motors_scr();
    void crt_motor_btns(mik::motor* mtr, int x, int y);

    float set_voltage;
    float toggles_active = 0;
    std::vector<std::pair<mik::textbox*, mik::motor*>> motor_texts;
    std::vector<std::pair<mik::toggle*, char>> volt_toggles;
    std::shared_ptr<screen> UI_motors_scr = nullptr;
};
}