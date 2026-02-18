#pragma once

#include <memory>
#include <utility>
#include "mikLib/ui.h"

// Absolute garbage code, a full rewrite needs to be done

namespace mik {


class UI_auton_screen {
public:
    UI_auton_screen();

    /** @returns The auton screen object */
    std::shared_ptr<screen> get_auton_screen();

    /** @brief Starts selected auton, used from main.cpp, disables controller overlay, 
     * and will calibrate if not already done do */
    void start_auton();

    /** @brief Runs the auto from the UI, user control is disabled, time is displayed,
     * and current ran auto can be stopped by pressing the B button on controller
     */
    void start_auton_test();
    
    /** @brief When start auton test is ran the auto will cutoff when 15 second time limit is reached
     * time limit is set to 60 seconds during skills
     */
    void enable_time_limit();

    /** @brief While auton test is running, coordinates of the robot will be shown */
    void enable_odom_display();

    /** @brief Selects the auton used by the auton screen */
    void UI_select_auton(mik::autons auton);

    /** @brief Returns the selected color in the UI */
    mik::alliance_colors get_alliance_color();

    /** @brief Enables controller auton selector, disables user control */
    void enable_controller_overlay();

    /** @brief Disables controller auton selector, enables user control */
    void disable_controller_overlay();

    
    /** @brief Internal use, updates controller buttons */
    void flip_toggle_controller(std::pair<int, int> cursor_position);

    /** @brief Internal use, updates controller buttons */
    void flip_toggle_controller(std::pair<int, int> cursor_position, bool state);

    /** @brief Internal use, saves selected auton to SD */
    void save_auton_SD(int count = 0); 

    bool off_skills = false;
    bool time_limit = false;
    bool odom_display = false;
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

    bool auto_running = false;
    bool end_card = false;
    float auto_start_time = 0;
    int auto_max_time = 15;

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
    bool restoring_from_sd = false;
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