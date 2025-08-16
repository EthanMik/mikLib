#pragma once

#include "vex.h"

// Absolute garbage code, a full rewrite needs to be done

namespace mik {

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

class UI_auton_screen {
public:
    UI_auton_screen();
    std::shared_ptr<screen> get_auton_screen();

    void start_auton();
    void start_auton_test();
    void enable_time_limit();
    void enable_odom_display();
    void UI_select_auton(mik::autons auton);
    void enable_controller_overlay();
    void disable_controller_overlay();
    void flip_toggle_controller(std::pair<int, int> cursor_position);
    void flip_toggle_controller(std::pair<int, int> cursor_position, bool state);
    void save_auton_SD(int count = 0); 
    bool off_skills = false;
    bool time_limit = false;
    bool odom_display = false;
    
    bool auto_running = false;
    bool end_card = false;
    float auto_start_time = 0;
    int auto_max_time = 15;
    int var_num = 1;

private:
    void UI_crt_auton_scr();
    void queue_autons(bool calibrating, bool set_description);
    bool set_description();
    void set_description(std::string text);
    void next_var();
    void prev_var();
    void update_var_display();
    void flip_toggle(std::shared_ptr<UI_component> tgl, bool state);
    void exit_auton_task();
    void set_previous_selected_auto();
    void controller_default_scr();
    void restart_controller_overlay();
    void controller_description_scr();
    void controller_calibrate_scr();
    void controller_selector_scr();

    auto_variation int_to_auto_variation(int num);

    void start_time_limit();

    bool robot_is_calibrated = false;

    bool red_blue = false;
    bool rings_goal = false;
    bool quals_elims = false;
    bool off_sawp = false;

    int controller_row_min = 0;
    int controller_row_max = 3;
    std::pair<int, int> cursor_position = {0, 0};
    std::vector<std::vector<controller_btn>> control_panel;
    bool input_overlay = false;
    vex::task controller_scr_overlay;
    vex::task controller_scr_input;
    vex::task auton_run;
    
    std::string output;
    std::string description_output;
    auto_variation var = auto_variation::ONE;

    bool is_showing_auton;
    int off_sawp_ID = 0;

    std::shared_ptr<UI_component> red_blue_tgl;
    std::shared_ptr<UI_component> rings_goal_tgl;
    std::shared_ptr<UI_component> quals_elims_tgl;
    std::shared_ptr<UI_component> off_sawp_tgl;

    textbox* description_textbox; 
    graphic* auto_var_num_txt;

    std::function<void()> auton;
    std::shared_ptr<screen> UI_auton_scr = nullptr;
};
}