#pragma once

#include "vex.h"

enum class autons { RED_BLUE, RINGS_GOAL, QUALS_ELIMS, OFF_SAWP, OFF_SKILLS };

class UI_auton_screen {
public:

    UI_auton_screen();
    std::shared_ptr<screen> get_auton_screen();

    void start_auton();
    void enable_time_limit();
    void UI_select_auton(autons auton);
    
    int auto_max_time = 15;
private:

    void UI_crt_auton_scr();
    void queue_autons(bool calibrating, bool set_description, bool set_lineup);
    void set_description();
    void show_auton();

    void start_time_limit();

    bool red_blue = false;
    bool rings_goal = false;
    bool quals_elims = false;
    bool off_sawp = false;
    bool off_skills = false;
    
    std::string output;
    auto_variation var = auto_variation::ONE;

    bool time_limit;
    bool is_showing_auton;
    int off_sawp_ID = 0;

    textbox* description_textbox; 
    graphic* auton_img; 
    std::function<void()> auton;
    std::shared_ptr<screen> UI_auton_scr = nullptr;
};