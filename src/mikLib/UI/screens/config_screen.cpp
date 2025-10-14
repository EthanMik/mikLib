#include "vex.h"

using namespace mik;

UI_config_screen::UI_config_screen() {
    UI_crt_config_scr();
    UI_crt_pnematics_scr();
}

std::shared_ptr<screen> UI_config_screen::get_config_screen() {
    return(UI_config_scr);
}

#define test_slot_x_position 322
#define data_slot_x_position 163
#define macro_slot_x_position 4

#define text_box_offset 2
#define y_start_position 13
#define y_offset 39

#define text_alignment text_align::CENTER

void UI_config_screen::UI_crt_config_scr() {
    UI_config_scr = UI_crt_scr(0, 45, SCREEN_WIDTH, SCREEN_HEIGHT + y_offset*2 + 5);
    UI_config_scr->add_scroll_bar(UI_crt_rec(0, 0, 2, 40, config_scroll_bar_color, UI_distance_units::pixels), screen::alignment::RIGHT);
    auto bg = UI_crt_bg(UI_crt_rec(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, config_bg_color, UI_distance_units::pixels));

// MACRO SLOTS

    // Runs selected auto in test mode, with 3 second countdown
    auto macro_1 = UI_crt_txtbox("Run Auto", config_text_color, config_macro_btn_bg_color, text_alignment, UI_crt_rec(macro_slot_x_position+text_box_offset, y_start_position+text_box_offset+y_offset*1, 150, 31, config_macro_btn_bg_color, UI_distance_units::pixels));
    auto macro_1_bg = UI_crt_btn(UI_crt_rec(macro_slot_x_position, y_start_position+y_offset*1, 154, 35, config_btn_outline_color, UI_distance_units::pixels), [this, macro_1](){ 
        countdown(macro_1, [](){ auton_scr->start_auton_test(); });
    });
    macro_1_bg->set_states(UI_crt_rec(macro_slot_x_position, y_start_position+y_offset*1, 154, 35, config_btn_outline_pressing_color, UI_distance_units::pixels), UI_crt_rec(macro_slot_x_position, y_start_position+y_offset*1, 154, 35, config_btn_outline_pressed_color, UI_distance_units::pixels));

    // Adds a 15 or 60 second limiter to autons
    macro_4_bg_tgl = UI_crt_tgl(UI_crt_rec(macro_slot_x_position, y_start_position+y_offset*2, 154, 35, config_btn_outline_color, UI_distance_units::pixels), [](){});
    auto macro_4_bg = UI_crt_btn(UI_crt_rec(macro_slot_x_position, y_start_position+y_offset*2, 154, 35, config_btn_outline_color, UI_distance_units::pixels), [](){ 
        auton_scr->enable_time_limit(); 
        auton_scr->flip_toggle_controller({3, 0}, auton_scr->time_limit); 
        auton_scr->save_auton_SD();
    });
    macro_4_bg_tgl->set_states(UI_crt_rec(macro_slot_x_position, y_start_position+y_offset*2, 154, 35, config_btn_outline_pressing_color, UI_distance_units::pixels), UI_crt_rec(macro_slot_x_position, y_start_position+y_offset*2, 154, 35, config_btn_outline_pressed_color, UI_distance_units::pixels));
    auto macro_4 = UI_crt_txtbox("Time Cap Auto", config_text_color, config_macro_btn_bg_color, text_alignment, UI_crt_rec(macro_slot_x_position+text_box_offset, y_start_position+text_box_offset+y_offset*2, 150, 31, config_macro_btn_bg_color, UI_distance_units::pixels));

    // Runs a driver skills match
    auto macro_7_bg = UI_crt_btn(UI_crt_rec(macro_slot_x_position, y_start_position+y_offset*3, 154, 35, config_btn_outline_color, UI_distance_units::pixels), [](){ 
        config_skills_driver_run(); 
    });
    macro_7_bg->set_states(UI_crt_rec(macro_slot_x_position, y_start_position+y_offset*3, 154, 35, config_btn_outline_pressing_color, UI_distance_units::pixels), UI_crt_rec(macro_slot_x_position, y_start_position+y_offset*3, 154, 35, config_btn_outline_pressed_color, UI_distance_units::pixels));
    auto macro_7 = UI_crt_txtbox("Driver Skills", config_text_color, config_macro_btn_bg_color, text_alignment, UI_crt_rec(macro_slot_x_position+text_box_offset, y_start_position+text_box_offset+y_offset*3, 150, 31, config_macro_btn_bg_color, UI_distance_units::pixels));

    // Selects auto skills to be run
    macro_10_bg_tgl = UI_crt_tgl(UI_crt_rec(macro_slot_x_position, y_start_position+y_offset*4, 154, 35, config_btn_outline_color, UI_distance_units::pixels), [](){});
    auto macro_10_bg = UI_crt_btn(UI_crt_rec(macro_slot_x_position, y_start_position+y_offset*4, 154, 35, config_btn_outline_color, UI_distance_units::pixels), [](){ 
        auton_scr->UI_select_auton(autons::OFF_SKILLS); 
        auton_scr->flip_toggle_controller({1, 1}, auton_scr->off_skills); 
        auton_scr->save_auton_SD(); 
    });
    macro_10_bg_tgl->set_states(UI_crt_rec(macro_slot_x_position, y_start_position+y_offset*4, 154, 35, config_btn_outline_pressing_color, UI_distance_units::pixels), UI_crt_rec(macro_slot_x_position, y_start_position+y_offset*4, 154, 35, config_btn_outline_pressed_color, UI_distance_units::pixels));
    auto macro_10 = UI_crt_txtbox("Auto Skills", config_text_color, config_macro_btn_bg_color, text_alignment, UI_crt_rec(macro_slot_x_position+text_box_offset, y_start_position+text_box_offset+y_offset*4, 150, 31, config_macro_btn_bg_color, UI_distance_units::pixels));

    // Spins each motor forwards for half a second
    auto macro_13_bg = UI_crt_btn(UI_crt_rec(macro_slot_x_position, y_start_position+y_offset*5, 154, 35, config_btn_outline_color, UI_distance_units::pixels), [](){ 
        config_spin_all_motors(); 
    });
    macro_13_bg->set_states(UI_crt_rec(macro_slot_x_position, y_start_position+y_offset*5, 154, 35, config_btn_outline_pressing_color, UI_distance_units::pixels), UI_crt_rec(macro_slot_x_position, y_start_position+y_offset*5, 154, 35, config_btn_outline_pressed_color, UI_distance_units::pixels));
    auto macro_13 = UI_crt_txtbox("Spin Motors", config_text_color, config_macro_btn_bg_color, text_alignment, UI_crt_rec(macro_slot_x_position+text_box_offset, y_start_position+text_box_offset+y_offset*5, 150, 31, config_macro_btn_bg_color, UI_distance_units::pixels));

    // Opens pnematic menu
    auto macro_16_bg = UI_crt_btn(UI_crt_rec(macro_slot_x_position, y_start_position+y_offset*6, 154, 35, config_btn_outline_color, UI_distance_units::pixels), [this](){ 
        UI_swap_screens({UI_pnematics_scr}); 
        disable_user_control(); 
    });
    macro_16_bg->set_states(UI_crt_rec(macro_slot_x_position, y_start_position+y_offset*6, 154, 35, config_btn_outline_pressing_color, UI_distance_units::pixels), UI_crt_rec(macro_slot_x_position, y_start_position+y_offset*6, 154, 35, config_btn_outline_pressed_color, UI_distance_units::pixels));
    auto macro_16 = UI_crt_txtbox("Pnematic Menu", config_text_color, config_macro_btn_bg_color, text_alignment, UI_crt_rec(macro_slot_x_position+text_box_offset, y_start_position+text_box_offset+y_offset*6, 150, 31, config_macro_btn_bg_color, UI_distance_units::pixels));


    auto macro_19_bg = UI_crt_btn(UI_crt_rec(macro_slot_x_position, y_start_position+y_offset*7, 154, 35, config_btn_outline_color, UI_distance_units::pixels), [](){ 
        wipe_SD_file("pid_data.txt"); 
    });
    macro_19_bg->set_states(UI_crt_rec(macro_slot_x_position, y_start_position+y_offset*7, 154, 35, config_btn_outline_pressing_color, UI_distance_units::pixels), UI_crt_rec(macro_slot_x_position, y_start_position+y_offset*7, 154, 35, config_btn_outline_pressed_color, UI_distance_units::pixels));
    auto macro_19 = UI_crt_txtbox("Wipe PID Data", config_text_color, config_macro_btn_bg_color, text_alignment, UI_crt_rec(macro_slot_x_position+text_box_offset, y_start_position+text_box_offset+y_offset*7, 150, 31, config_macro_btn_bg_color, UI_distance_units::pixels));


    auto macro_22_bg = UI_crt_btn(UI_crt_rec(macro_slot_x_position, y_start_position+y_offset*8, 154, 35, config_btn_outline_color, UI_distance_units::pixels), [](){ 
        wipe_SD_file("auton.txt"); 
    });
    macro_22_bg->set_states(UI_crt_rec(macro_slot_x_position, y_start_position+y_offset*8, 154, 35, config_btn_outline_pressing_color, UI_distance_units::pixels), UI_crt_rec(macro_slot_x_position, y_start_position+y_offset*8, 154, 35, config_btn_outline_pressed_color, UI_distance_units::pixels));
    auto macro_22 = UI_crt_txtbox("Wipe Sel Auto", config_text_color, config_macro_btn_bg_color, text_alignment, UI_crt_rec(macro_slot_x_position+text_box_offset, y_start_position+text_box_offset+y_offset*8, 150, 31, config_macro_btn_bg_color, UI_distance_units::pixels));



// DATA SLOTS

    // Add unplugged devices at program init to console
    auto macro_2_bg = UI_crt_btn(UI_crt_rec(data_slot_x_position, y_start_position+y_offset*1, 154, 35, config_btn_outline_color, UI_distance_units::pixels), [](){ 
        config_error_data();
     });
    macro_2_bg->set_states(UI_crt_rec(data_slot_x_position, y_start_position+y_offset*1, 154, 35, config_btn_outline_pressing_color, UI_distance_units::pixels), UI_crt_rec(data_slot_x_position, y_start_position+y_offset*1, 154, 35, config_btn_outline_pressed_color, UI_distance_units::pixels));
    auto macro_2 = UI_crt_txtbox("Error Data", config_text_color, config_data_btn_bg_color, text_alignment, UI_crt_rec(data_slot_x_position+text_box_offset, 54, 150, 31, config_data_btn_bg_color, UI_distance_units::pixels));

     // Add motor tempurature values to console
    auto macro_5_bg = UI_crt_btn(UI_crt_rec(data_slot_x_position, y_start_position+y_offset*2, 154, 35, config_btn_outline_color, UI_distance_units::pixels), [](){ 
        config_motor_temp(); 
    });
    macro_5_bg->set_states(UI_crt_rec(data_slot_x_position, y_start_position+y_offset*2, 154, 35, config_btn_outline_pressing_color, UI_distance_units::pixels), UI_crt_rec(data_slot_x_position, y_start_position+y_offset*2, 154, 35, config_btn_outline_pressed_color, UI_distance_units::pixels));
    auto macro_5 = UI_crt_txtbox("Motor Temps", config_text_color, config_data_btn_bg_color, text_alignment, UI_crt_rec(data_slot_x_position+text_box_offset, y_start_position+text_box_offset+y_offset*2, 150, 31, config_data_btn_bg_color, UI_distance_units::pixels));

    // Add motor wattage values to console
    auto macro_8_bg = UI_crt_btn(UI_crt_rec(data_slot_x_position, y_start_position+y_offset*3, 154, 35, config_btn_outline_color, UI_distance_units::pixels), [](){ 
        config_motor_wattage(); 
    });
    macro_8_bg->set_states(UI_crt_rec(data_slot_x_position, y_start_position+y_offset*3, 154, 35, config_btn_outline_pressing_color, UI_distance_units::pixels), UI_crt_rec(data_slot_x_position, y_start_position+y_offset*3, 154, 35, config_btn_outline_pressed_color, UI_distance_units::pixels));
    auto macro_8 = UI_crt_txtbox("Motor Wattage", config_text_color, config_data_btn_bg_color, text_alignment, UI_crt_rec(data_slot_x_position+text_box_offset, y_start_position+text_box_offset+y_offset*3, 150, 31, config_data_btn_bg_color, UI_distance_units::pixels));

    // Add odom data to console
    auto macro_11_bg = UI_crt_btn(UI_crt_rec(data_slot_x_position, y_start_position+y_offset*4, 154, 35, config_btn_outline_color, UI_distance_units::pixels), [](){ 
        config_odom_data(); 
    });
    macro_11_bg->set_states(UI_crt_rec(data_slot_x_position, y_start_position+y_offset*4, 154, 35, config_btn_outline_pressing_color, UI_distance_units::pixels), UI_crt_rec(data_slot_x_position, y_start_position+y_offset*4, 154, 35, config_btn_outline_pressed_color, UI_distance_units::pixels));
    auto macro_11 = UI_crt_txtbox("Odom Data", config_text_color, config_data_btn_bg_color, text_alignment, UI_crt_rec(data_slot_x_position+text_box_offset, y_start_position+text_box_offset+y_offset*4, 150, 31, config_data_btn_bg_color, UI_distance_units::pixels));

    // Add updated pid values from pid_tuner to console
    auto macro_14_bg = UI_crt_btn(UI_crt_rec(data_slot_x_position, y_start_position+y_offset*5, 154, 35, config_btn_outline_color, UI_distance_units::pixels), [](){ 
        config_add_pid_output_SD_console(); 
    });
    macro_14_bg->set_states(UI_crt_rec(data_slot_x_position, y_start_position+y_offset*5, 154, 35, config_btn_outline_pressing_color, UI_distance_units::pixels), UI_crt_rec(data_slot_x_position, y_start_position+y_offset*5, 154, 35, config_btn_outline_pressed_color, UI_distance_units::pixels));
    auto macro_14 = UI_crt_txtbox("PID Data", config_text_color, config_data_btn_bg_color, text_alignment, UI_crt_rec(data_slot_x_position+text_box_offset, y_start_position+text_box_offset+y_offset*5, 150, 31, config_data_btn_bg_color, UI_distance_units::pixels));


    auto macro_17_bg = UI_crt_btn(UI_crt_rec(data_slot_x_position, y_start_position+y_offset*6, 154, 35, config_btn_outline_color, UI_distance_units::pixels), [](){ 
        config_motor_torque();
    });
    macro_17_bg->set_states(UI_crt_rec(data_slot_x_position, y_start_position+y_offset*6, 154, 35, config_btn_outline_pressing_color, UI_distance_units::pixels), UI_crt_rec(data_slot_x_position, y_start_position+y_offset*6, 154, 35, config_btn_outline_pressed_color, UI_distance_units::pixels));
    auto macro_17 = UI_crt_txtbox("Motor Torque", config_text_color, config_data_btn_bg_color, text_alignment, UI_crt_rec(data_slot_x_position+text_box_offset, y_start_position+text_box_offset+y_offset*6, 150, 31, config_data_btn_bg_color, UI_distance_units::pixels));


    auto macro_20_bg = UI_crt_btn(UI_crt_rec(data_slot_x_position, y_start_position+y_offset*7, 154, 35, config_btn_outline_color, UI_distance_units::pixels), [](){ 
        config_motor_efficiency();
    });
    macro_20_bg->set_states(UI_crt_rec(data_slot_x_position, y_start_position+y_offset*7, 154, 35, config_btn_outline_pressing_color, UI_distance_units::pixels), UI_crt_rec(data_slot_x_position, y_start_position+y_offset*7, 154, 35, config_btn_outline_pressed_color, UI_distance_units::pixels));
    auto macro_20 = UI_crt_txtbox("Motor Eff", config_text_color, config_data_btn_bg_color, text_alignment, UI_crt_rec(data_slot_x_position+text_box_offset, y_start_position+text_box_offset+y_offset*7, 150, 31, config_data_btn_bg_color, UI_distance_units::pixels));


    auto macro_23_bg = UI_crt_btn(UI_crt_rec(data_slot_x_position, y_start_position+y_offset*8, 154, 35, config_btn_outline_color, UI_distance_units::pixels), [](){ 
        config_motor_current();
    });
    macro_23_bg->set_states(UI_crt_rec(data_slot_x_position, y_start_position+y_offset*8, 154, 35, config_btn_outline_pressing_color, UI_distance_units::pixels), UI_crt_rec(data_slot_x_position, y_start_position+y_offset*8, 154, 35, config_btn_outline_pressed_color, UI_distance_units::pixels));
    auto macro_23 = UI_crt_txtbox("Motor Current", config_text_color, config_data_btn_bg_color, text_alignment, UI_crt_rec(data_slot_x_position+text_box_offset, y_start_position+text_box_offset+y_offset*8, 150, 31, config_data_btn_bg_color, UI_distance_units::pixels));


// TEST/TUNE SLOTS
    auto macro_3 = UI_crt_txtbox("Tune Mode", config_text_color, config_test_btn_bg_color, text_alignment, UI_crt_rec(test_slot_x_position+text_box_offset, 54, 150, 31, config_test_btn_bg_color, UI_distance_units::pixels));
    auto macro_3_bg = UI_crt_btn(UI_crt_rec(test_slot_x_position, y_start_position+y_offset*1, 154, 35, config_btn_outline_color, UI_distance_units::pixels), [this, macro_3](){ 
        bool mode = config_swap_test_mode();
        swap_mode(macro_3, mode);
    });
    macro_3_bg->set_states(UI_crt_rec(test_slot_x_position, y_start_position+y_offset*1, 154, 35, config_btn_outline_pressing_color, UI_distance_units::pixels), UI_crt_rec(test_slot_x_position, y_start_position+y_offset*1, 154, 35, config_btn_outline_pressed_color, UI_distance_units::pixels));


    auto macro_6_bg = UI_crt_btn(UI_crt_rec(test_slot_x_position, y_start_position+y_offset*2, 154, 35, config_btn_outline_color, UI_distance_units::pixels), [](){ 
        config_tune_drive(); 
    });
    macro_6_bg->set_states(UI_crt_rec(test_slot_x_position, y_start_position+y_offset*2, 154, 35, config_btn_outline_pressing_color, UI_distance_units::pixels), UI_crt_rec(test_slot_x_position, y_start_position+y_offset*2, 154, 35, config_btn_outline_pressed_color, UI_distance_units::pixels));
    auto macro_6 = UI_crt_txtbox("Tune Drive", config_text_color, config_test_btn_bg_color, text_alignment, UI_crt_rec(test_slot_x_position+text_box_offset, y_start_position+text_box_offset+y_offset*2, 150, 31, config_test_btn_bg_color, UI_distance_units::pixels));


    auto macro_9_bg = UI_crt_btn(UI_crt_rec(test_slot_x_position, y_start_position+y_offset*3, 154, 35, config_btn_outline_color, UI_distance_units::pixels), [](){ 
        config_tune_heading(); 
    });
    macro_9_bg->set_states(UI_crt_rec(test_slot_x_position, y_start_position+y_offset*3, 154, 35, config_btn_outline_pressing_color, UI_distance_units::pixels), UI_crt_rec(test_slot_x_position, y_start_position+y_offset*3, 154, 35, config_btn_outline_pressed_color, UI_distance_units::pixels));
    auto macro_9 = UI_crt_txtbox("Tune Heading", config_text_color, config_test_btn_bg_color, text_alignment, UI_crt_rec(test_slot_x_position+text_box_offset, y_start_position+text_box_offset+y_offset*3, 150, 31, config_test_btn_bg_color, UI_distance_units::pixels));
    

    auto macro_12_bg = UI_crt_btn(UI_crt_rec(test_slot_x_position, y_start_position+y_offset*4, 154, 35, config_btn_outline_color, UI_distance_units::pixels), [](){ 
        config_tune_turn(); 
    });
    macro_12_bg->set_states(UI_crt_rec(test_slot_x_position, y_start_position+y_offset*4, 154, 35, config_btn_outline_pressing_color, UI_distance_units::pixels), UI_crt_rec(test_slot_x_position, y_start_position+y_offset*4, 154, 35, config_btn_outline_pressed_color, UI_distance_units::pixels));
    auto macro_12 = UI_crt_txtbox("Tune Turn", config_text_color, config_test_btn_bg_color, text_alignment, UI_crt_rec(test_slot_x_position+text_box_offset, y_start_position+text_box_offset+y_offset*4, 150, 31, config_test_btn_bg_color, UI_distance_units::pixels));
    

    auto macro_15_bg = UI_crt_btn(UI_crt_rec(test_slot_x_position, y_start_position+y_offset*5, 154, 35, config_btn_outline_color, UI_distance_units::pixels), [](){ 
        config_tune_swing(); 
    });
    macro_15_bg->set_states(UI_crt_rec(test_slot_x_position, y_start_position+y_offset*5, 154, 35, config_btn_outline_pressing_color, UI_distance_units::pixels), UI_crt_rec(test_slot_x_position, y_start_position+y_offset*5, 154, 35, config_btn_outline_pressed_color, UI_distance_units::pixels));
    auto macro_15 = UI_crt_txtbox("Tune Swing", config_text_color, config_test_btn_bg_color, text_alignment, UI_crt_rec(test_slot_x_position+text_box_offset, y_start_position+text_box_offset+y_offset*5, 150, 31, config_test_btn_bg_color, UI_distance_units::pixels));
    

    auto macro_18_bg = UI_crt_btn(UI_crt_rec(test_slot_x_position, y_start_position+y_offset*6, 154, 35, config_btn_outline_color, UI_distance_units::pixels), [](){ 
        if (config_is_testing_odom()) {
            test_odom_full();
        } else {
            test_full(); 
        }
    });
    macro_18_bg->set_states(UI_crt_rec(test_slot_x_position, y_start_position+y_offset*6, 154, 35, config_btn_outline_pressing_color, UI_distance_units::pixels), UI_crt_rec(test_slot_x_position, y_start_position+y_offset*6, 154, 35, config_btn_outline_pressed_color, UI_distance_units::pixels));
    auto macro_18 = UI_crt_txtbox("Test Full", config_text_color, config_test_btn_bg_color, text_alignment, UI_crt_rec(test_slot_x_position+text_box_offset, y_start_position+text_box_offset+y_offset*6, 150, 31, config_test_btn_bg_color, UI_distance_units::pixels));


    auto macro_21_bg = UI_crt_btn(UI_crt_rec(test_slot_x_position, y_start_position+y_offset*7, 154, 35, config_btn_outline_color, UI_distance_units::pixels), [](){ 
        test_boomerang(); 
    });
    macro_21_bg->set_states(UI_crt_rec(test_slot_x_position, y_start_position+y_offset*7, 154, 35, config_btn_outline_pressing_color, UI_distance_units::pixels), UI_crt_rec(test_slot_x_position, y_start_position+y_offset*7, 154, 35, config_btn_outline_pressed_color, UI_distance_units::pixels));
    auto macro_21 = UI_crt_txtbox("Test Boomeran", config_text_color, config_test_btn_bg_color, text_alignment, UI_crt_rec(test_slot_x_position+text_box_offset, y_start_position+text_box_offset+y_offset*7, 150, 31, config_test_btn_bg_color, UI_distance_units::pixels));


    auto macro_24_bg = UI_crt_btn(UI_crt_rec(test_slot_x_position, y_start_position+y_offset*8, 154, 35, config_btn_outline_color, UI_distance_units::pixels), [](){ 
        test_pursuit(); 
    });
    macro_24_bg->set_states(UI_crt_rec(test_slot_x_position, y_start_position+y_offset*8, 154, 35, config_btn_outline_pressing_color, UI_distance_units::pixels), UI_crt_rec(test_slot_x_position, y_start_position+y_offset*8, 154, 35, config_btn_outline_pressed_color, UI_distance_units::pixels));
    auto macro_24 = UI_crt_txtbox("Test Pursuit", config_text_color, config_test_btn_bg_color, text_alignment, UI_crt_rec(test_slot_x_position+text_box_offset, y_start_position+text_box_offset+y_offset*8, 150, 31, config_test_btn_bg_color, UI_distance_units::pixels));



    UI_config_scr->add_UI_components({bg, 
        macro_1_bg, macro_1, macro_2_bg, macro_2, macro_3_bg, macro_3,
        macro_4_bg, macro_4_bg_tgl, macro_4, macro_5_bg, macro_5, macro_6_bg, macro_6,
        macro_7_bg, macro_7, macro_8_bg, macro_8, macro_9_bg, macro_9,
        macro_10_bg, macro_10_bg_tgl, macro_10, macro_11_bg, macro_11, macro_12_bg, macro_12,
        macro_13_bg, macro_13, macro_14_bg, macro_14, macro_15_bg, macro_15,
        macro_16_bg, macro_16, macro_17_bg, macro_17, macro_18_bg, macro_18,
        macro_19_bg, macro_19, macro_20_bg, macro_20, macro_21_bg, macro_21, 
        macro_22_bg, macro_22, macro_23_bg, macro_23, macro_24_bg, macro_24
    });

    for (const auto& component : UI_config_scr->get_UI_components()) {
        component->set_y_pos(component->get_y_pos() - 45);
    }
}

void UI_config_screen::UI_crt_pnematics_scr() {
    UI_pnematics_scr = UI_crt_scr(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    auto bg = UI_crt_bg(UI_crt_rec(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, pnematic_bg_color, UI_distance_units::pixels));

    auto title_txt = UI_crt_gfx(UI_crt_txt("Pneumatics Menu", 169, 30,pnematic_text_color, pnematic_bg_color, UI_distance_units::pixels));

    const float txt_x = .34;
    const float txt_y = .45; 

    float x = .23;
    float y = .56;

    auto port_A_btn = UI_crt_btn(UI_crt_img("", x, y, .75, .75, UI_distance_units::inches), [](){ config_test_three_wire_port(PORT_A); });
    auto port_A = UI_crt_tgl(UI_crt_grp({ UI_crt_rec(x, y, .75, .75, pnematic_A_btn_bg_color, pnematic_port_btn_outline_color, 5, UI_distance_units::inches), UI_crt_txt("A", x+txt_x, y+txt_y, pnematic_text_color, pnematic_A_btn_bg_color, UI_distance_units::inches)}), [](){});
    port_A->set_states(
        UI_crt_grp({ UI_crt_rec(x, y, .75, .75, pnematic_A_btn_bg_color, pnematic_port_btn_outline_pressing_color, 5, UI_distance_units::inches), UI_crt_txt("A", x+txt_x, y+txt_y, pnematic_text_color, pnematic_A_btn_bg_color, UI_distance_units::inches)}),
        UI_crt_grp({ UI_crt_rec(x, y, .75, .75, pnematic_A_btn_bg_color, pnematic_port_btn_outline_pressed_color, 5, UI_distance_units::inches), UI_crt_txt("A", x+txt_x, y+txt_y, pnematic_text_color, pnematic_A_btn_bg_color, UI_distance_units::inches)})
    );

    x = 1.48;
    y = .56;

    auto port_B_btn = UI_crt_btn(UI_crt_img("", x, y, .75, .75, UI_distance_units::inches), [](){ config_test_three_wire_port(PORT_B); });
    auto port_B = UI_crt_tgl(UI_crt_grp({ UI_crt_rec(x, y, .75, .75, pnematic_B_btn_bg_color, pnematic_port_btn_outline_color, 5, UI_distance_units::inches), UI_crt_txt("B", x+txt_x, y+txt_y, pnematic_text_color, pnematic_B_btn_bg_color, UI_distance_units::inches)}), [](){});
    port_B->set_states(
        UI_crt_grp({ UI_crt_rec(x, y, .75, .75, pnematic_B_btn_bg_color, pnematic_port_btn_outline_pressing_color, 5, UI_distance_units::inches), UI_crt_txt("B", x+txt_x, y+txt_y, pnematic_text_color, pnematic_B_btn_bg_color, UI_distance_units::inches)}),
        UI_crt_grp({ UI_crt_rec(x, y, .75, .75, pnematic_B_btn_bg_color, pnematic_port_btn_outline_pressed_color, 5, UI_distance_units::inches), UI_crt_txt("B", x+txt_x, y+txt_y, pnematic_text_color, pnematic_B_btn_bg_color, UI_distance_units::inches)})
    );

    x = 2.73;
    y = .56;

    auto port_C_btn = UI_crt_btn(UI_crt_img("", x, y, .75, .75, UI_distance_units::inches), [](){ config_test_three_wire_port(PORT_C); });
    auto port_C = UI_crt_tgl(UI_crt_grp({ UI_crt_rec(x, y, .75, .75, pnematic_C_btn_bg_color, pnematic_port_btn_outline_color, 5, UI_distance_units::inches), UI_crt_txt("C", x+txt_x, y+txt_y, pnematic_text_color, pnematic_C_btn_bg_color, UI_distance_units::inches)}), [](){});
    port_C->set_states(
        UI_crt_grp({ UI_crt_rec(x, y, .75, .75, pnematic_C_btn_bg_color, pnematic_port_btn_outline_pressing_color, 5, UI_distance_units::inches), UI_crt_txt("C", x+txt_x, y+txt_y, pnematic_text_color, pnematic_C_btn_bg_color, UI_distance_units::inches)}),
        UI_crt_grp({ UI_crt_rec(x, y, .75, .75, pnematic_C_btn_bg_color, pnematic_port_btn_outline_pressed_color, 5, UI_distance_units::inches), UI_crt_txt("C", x+txt_x, y+txt_y, pnematic_text_color, pnematic_C_btn_bg_color, UI_distance_units::inches)})
    );

    x = 3.98;
    y = .56;

    auto port_D_btn = UI_crt_btn(UI_crt_img("", x, y, .75, .75, UI_distance_units::inches), [](){ config_test_three_wire_port(PORT_D); });
    auto port_D = UI_crt_tgl(UI_crt_grp({ UI_crt_rec(x, y, .75, .75, pnematic_D_btn_bg_color, pnematic_port_btn_outline_color, 5, UI_distance_units::inches), UI_crt_txt("D", x+txt_x, y+txt_y, pnematic_text_color, pnematic_D_btn_bg_color, UI_distance_units::inches)}), [](){});
    port_D->set_states(
        UI_crt_grp({ UI_crt_rec(x, y, .75, .75, pnematic_D_btn_bg_color, pnematic_port_btn_outline_pressing_color, 5, UI_distance_units::inches), UI_crt_txt("D", x+txt_x, y+txt_y, pnematic_text_color, pnematic_D_btn_bg_color, UI_distance_units::inches)}),
        UI_crt_grp({ UI_crt_rec(x, y, .75, .75, pnematic_D_btn_bg_color, pnematic_port_btn_outline_pressed_color, 5, UI_distance_units::inches), UI_crt_txt("D", x+txt_x, y+txt_y, pnematic_text_color, pnematic_D_btn_bg_color, UI_distance_units::inches)})
    );

    x = .23;
    y = 1.62;

    auto port_E_btn = UI_crt_btn(UI_crt_img("", x, y, .75, .75, UI_distance_units::inches), [](){ config_test_three_wire_port(PORT_E); });
    auto port_E = UI_crt_tgl(UI_crt_grp({ UI_crt_rec(x, y, .75, .75, pnematic_E_btn_bg_color, pnematic_port_btn_outline_color, 5, UI_distance_units::inches), UI_crt_txt("E", x+txt_x, y+txt_y, pnematic_text_color, pnematic_E_btn_bg_color, UI_distance_units::inches)}), [](){});
    port_E->set_states(
        UI_crt_grp({ UI_crt_rec(x, y, .75, .75, pnematic_E_btn_bg_color, pnematic_port_btn_outline_pressing_color, 5, UI_distance_units::inches), UI_crt_txt("E", x+txt_x, y+txt_y, pnematic_text_color, pnematic_E_btn_bg_color, UI_distance_units::inches)}),
        UI_crt_grp({ UI_crt_rec(x, y, .75, .75, pnematic_E_btn_bg_color, pnematic_port_btn_outline_pressed_color, 5, UI_distance_units::inches), UI_crt_txt("E", x+txt_x, y+txt_y, pnematic_text_color, pnematic_E_btn_bg_color, UI_distance_units::inches)})
    );

    x = 1.48;
    y = 1.62;

    auto port_F_btn = UI_crt_btn(UI_crt_img("", x, y, .75, .75, UI_distance_units::inches), [](){ config_test_three_wire_port(PORT_F); });
    auto port_F = UI_crt_tgl(UI_crt_grp({ UI_crt_rec(x, y, .75, .75, pnematic_F_btn_bg_color, pnematic_port_btn_outline_color, 5, UI_distance_units::inches), UI_crt_txt("F", x+txt_x, y+txt_y, pnematic_text_color, pnematic_F_btn_bg_color, UI_distance_units::inches)}), [](){});
    port_F->set_states(
        UI_crt_grp({ UI_crt_rec(x, y, .75, .75, pnematic_F_btn_bg_color, pnematic_port_btn_outline_pressing_color, 5, UI_distance_units::inches), UI_crt_txt("F", x+txt_x, y+txt_y, pnematic_text_color, pnematic_F_btn_bg_color, UI_distance_units::inches)}),
        UI_crt_grp({ UI_crt_rec(x, y, .75, .75, pnematic_F_btn_bg_color, pnematic_port_btn_outline_pressed_color, 5, UI_distance_units::inches), UI_crt_txt("F", x+txt_x, y+txt_y, pnematic_text_color, pnematic_F_btn_bg_color, UI_distance_units::inches)})
    );

    x = 2.73;
    y = 1.62;

    auto port_G_btn = UI_crt_btn(UI_crt_img("", x, y, .75, .75, UI_distance_units::inches), [](){ config_test_three_wire_port(PORT_G); });
    auto port_G = UI_crt_tgl(UI_crt_grp({ UI_crt_rec(x, y, .75, .75, pnematic_G_btn_bg_color, pnematic_port_btn_outline_color, 5, UI_distance_units::inches), UI_crt_txt("G", x+txt_x, y+txt_y, pnematic_text_color, pnematic_G_btn_bg_color, UI_distance_units::inches)}), [](){});
    port_G->set_states(
        UI_crt_grp({ UI_crt_rec(x, y, .75, .75, pnematic_G_btn_bg_color, pnematic_port_btn_outline_pressing_color, 5, UI_distance_units::inches), UI_crt_txt("G", x+txt_x, y+txt_y, pnematic_text_color, pnematic_G_btn_bg_color, UI_distance_units::inches)}),
        UI_crt_grp({ UI_crt_rec(x, y, .75, .75, pnematic_G_btn_bg_color, pnematic_port_btn_outline_pressed_color, 5, UI_distance_units::inches), UI_crt_txt("G", x+txt_x, y+txt_y, pnematic_text_color, pnematic_G_btn_bg_color, UI_distance_units::inches)})
    );

    x = 3.98;
    y = 1.62;

    auto port_H_btn = UI_crt_btn(UI_crt_img("", x, y, .75, .75, UI_distance_units::inches), [](){ config_test_three_wire_port(PORT_H); });
    auto port_H = UI_crt_tgl(UI_crt_grp({ UI_crt_rec(x, y, .75, .75, pnematic_H_btn_bg_color, pnematic_port_btn_outline_color, 5, UI_distance_units::inches), UI_crt_txt("H", x+txt_x, y+txt_y, pnematic_text_color, pnematic_H_btn_bg_color, UI_distance_units::inches)}), [](){});
    port_H->set_states(
        UI_crt_grp({ UI_crt_rec(x, y, .75, .75, pnematic_H_btn_bg_color, pnematic_port_btn_outline_pressing_color, 5, UI_distance_units::inches), UI_crt_txt("H", x+txt_x, y+txt_y, pnematic_text_color, pnematic_H_btn_bg_color, UI_distance_units::inches)}),
        UI_crt_grp({ UI_crt_rec(x, y, .75, .75, pnematic_H_btn_bg_color, pnematic_port_btn_outline_pressed_color, 5, UI_distance_units::inches), UI_crt_txt("H", x+txt_x, y+txt_y, pnematic_text_color, pnematic_H_btn_bg_color, UI_distance_units::inches)})
    );

    
    auto exit_bg = UI_crt_btn(UI_crt_rec(2, 2, 40, 40, pnematic_close_btn_bg_color, pnematic_close_btn_outline_color, 2, UI_distance_units::pixels), [](){ UI_select_scr(config_scr->get_config_screen()); enable_user_control(); });
        exit_bg->set_states(UI_crt_rec(2, 2, 40, 40, pnematic_close_btn_bg_color, pnematic_close_btn_pressing_color, 2, UI_distance_units::pixels), UI_crt_rec(2, 2, 40, 40, pnematic_close_btn_bg_color, pnematic_close_btn_pressed_color, 2, UI_distance_units::pixels));
    auto exit_txt = UI_crt_gfx({UI_crt_rec(4, 4, 36, 36, pnematic_close_btn_bg_color, UI_distance_units::pixels), UI_crt_txt("X", 17, 27, pnematic_text_color, pnematic_close_btn_bg_color, mik::UI_distance_units::pixels)});
    
    UI_pnematics_scr->add_UI_components({bg, title_txt, exit_bg, exit_txt, port_A_btn, port_A, port_B_btn, port_B, port_C_btn,  port_C, port_D_btn, port_D, port_E_btn,port_E, port_F_btn, port_F, port_G_btn, port_G, port_H_btn, port_H});
}

void UI_config_screen::swap_mode(std::shared_ptr<UI_component> txtbox, bool mode) {
    auto* txtbx = static_cast<textbox*>(txtbox.get());
    if (mode) {
        txtbx->set_text("Tune Odom");
    } else {
        txtbx->set_text("Tune Relative");
    }
}

void UI_config_screen::countdown(std::shared_ptr<UI_component> txtbox, std::function<void()> func) {
    auto* txtbx = static_cast<textbox*>(txtbox.get());
    txtbox_task_data = txtbx;
    func_task = func;
    vex::task count([](){
        int count = 3;
        std::string original_txt = config_scr->txtbox_task_data->get_text();
        while(count >= 0) {
            config_scr->txtbox_task_data->set_text(to_string(count));
            vex::task::sleep(1000);
            count--;
        }
        
        config_scr->txtbox_task_data->set_text(original_txt);
        config_scr->func_task();
        return 0;
    });

}
