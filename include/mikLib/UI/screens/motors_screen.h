#pragma once

#include "mikLib/ui.h"

namespace mik {

class UI_motors_screen {
public:
    UI_motors_screen();
    std::shared_ptr<screen> get_motors_screen();

private:
    void UI_crt_motors_scr();

    float set_voltage;
    std::vector<std::pair<mik::toggle*, char>> volt_toggles;
    std::shared_ptr<screen> UI_motors_scr = nullptr;
};
}