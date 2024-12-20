#pragma once

#include "vex.h"

#define UI_RED_BLUE_BIT     0
#define UI_RINGS_GOAL_BIT   1
#define UI_QUALS_ELIMS_BIT  2
#define UI_OFF_SKILLS_BIT   3

#define UI_RED_BLUE_MASK    (1 << 0)
#define UI_RINGS_GOAL_MASK  (1 << 1)
#define UI_QUALS_ELIMS_MASK (1 << 2)
#define UI_OFF_SKILLS_MASK  (1 << 3)

class UI_auton_screen {
public:
    UI_auton_screen();
    std::shared_ptr<screen> get_auton_screen();

private:
    void UI_crt_auton_scr();
    void UI_select_auton(int bit);

    std::shared_ptr<screen> UI_auton_scr = nullptr;
    std::vector<int> UI_toggle_IDs;
    unsigned int UI_auton_selected = 0;
};