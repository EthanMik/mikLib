#pragma once

#include "vex.h"

class UI_auton_screen {
public:
    UI_auton_screen();
    std::shared_ptr<screen> get_auton_screen();

    void start_auton();

private:
    enum class autons { RED_BLUE, RINGS_GOAL, QUALS_ELIMS, OFF_SAWP };

    void UI_crt_auton_scr();
    void UI_select_auton(autons auton);
    void queue_autons(bool calibrating);
    void set_description();

    bool red_blue = false;
    bool rings_goal = false;
    bool quals_elims = false;
    bool off_sawp = false;
    
    int off_sawp_ID = 0;

    textbox* description_textbox; 
    std::function<void()> auton;
    std::shared_ptr<screen> UI_auton_scr = nullptr;
};