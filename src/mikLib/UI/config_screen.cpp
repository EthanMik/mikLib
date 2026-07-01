#include "mikLib/ui.h"
#include "test.h"

using namespace mik;

UI_config_screen::UI_config_screen() {
    UI_crt_config_scr();
}

std::shared_ptr<screen> UI_config_screen::get_config_screen() {
    return UI_config_scr;
}

static constexpr int test_slot_x_position = 322;
static constexpr int data_slot_x_position = 163;
static constexpr int macro_slot_x_position = 4;

static constexpr int text_box_offset = 2;
static constexpr int y_start_position = 13;
static constexpr int y_offset = 39;

std::shared_ptr<UI_component> UI_config_screen::add_toggle(slot slot, std::string label, std::function<void()> func) {
    return add_button(slot, label, func, false);
}

std::shared_ptr<UI_component> UI_config_screen::add_button(slot slot, std::string label, std::function<void()> func, bool button = true) {
    return add_button(slot, label, [func](std::shared_ptr<UI_component>){ func(); }, button);
}

std::shared_ptr<UI_component> UI_config_screen::add_button(slot slot, std::string label, std::function<void(std::shared_ptr<UI_component>)> func, bool button = true) {
    int x;
    int row;
    auto bg_color = config_macro_btn_bg_color;

    switch (slot) {
        case slot::DATA:
            x = data_slot_x_position;
            row = data_row++;
            bg_color = config_data_btn_bg_color;
            break;
        case slot::MACRO:
            x = macro_slot_x_position;
            row = macro_row++;
            break;
        case slot::TEST:
            x = test_slot_x_position;
            row = test_row++;
            bg_color = config_test_btn_bg_color;
            break;
    }

    int y = y_start_position + (y_offset * row);
    auto tgl = UI_crt_tgl(UI_crt_rec(x, y, 154, 35, config_btn_outline_color, UI_distance_units::pixels), [](){});
    tgl->set_states(
        UI_crt_rec(x, y, 154, 35, config_btn_outline_pressing_color, UI_distance_units::pixels),
        UI_crt_rec(x, y, 154, 35, config_btn_outline_pressed_color, UI_distance_units::pixels));

    auto txt = UI_crt_txtbox(label, config_text_color, bg_color, text_align::CENTER,
        UI_crt_rec(x + text_box_offset, y + text_box_offset, 150, 31, bg_color, UI_distance_units::pixels));
    auto btn = UI_crt_btn(UI_crt_rec(x, y, 154, 35, config_btn_outline_color, UI_distance_units::pixels),
        [func, txt](){ func(txt); });
    btn->set_states(
        UI_crt_rec(x, y, 154, 35, config_btn_outline_pressing_color, UI_distance_units::pixels),
        UI_crt_rec(x, y, 154, 35, config_btn_outline_pressed_color, UI_distance_units::pixels));

    if (button) {
        UI_config_scr->add_UI_components({btn, txt});
        return btn;
    }

    UI_config_scr->add_UI_components({btn, tgl, txt});
    return tgl;
}


void UI_config_screen::UI_crt_config_scr() {
    const int extra_buttons = 3; // Expands the screen to scroll
    const int extra_screen_height = 39 * extra_buttons + 5;
    UI_config_scr = UI_crt_scr(0, 45, SCREEN_WIDTH, SCREEN_HEIGHT + extra_screen_height);
    UI_config_scr->add_scroll_bar(UI_crt_rec(0, 0, 2, 40, config_scroll_bar_color, UI_distance_units::pixels), screen::alignment::RIGHT);
    auto bg = UI_crt_bg(UI_crt_rec(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, config_bg_color, UI_distance_units::pixels));
    UI_config_scr->add_UI_component(bg);

// MACRO SLOTS

    // Runs selected auto in test mode, with 3 second countdown
    add_button(slot::MACRO, "Run Auto", [this](std::shared_ptr<UI_component> txt){
        countdown(txt, [](){ auton_scr->start_auton_test(); });
    });

    // Adds a 15 or 60 second limiter to autons
    time_cap_auto_tgl = add_toggle(slot::MACRO, "Time Cap Auto", [](){
        auton_scr->enable_time_limit(); 
        auton_scr->flip_toggle_controller({3, 0}, auton_scr->time_limit); 
        auton_scr->save_auton_SD();
    });

    // Runs a driver skills match
    add_button(slot::MACRO, "Driver Skills", [](){ config_skills_driver_run(); });

    // Selects auto skills to be run
    auto_skills_tgl = add_toggle(slot::MACRO, "Auto Skills", [](){
        auton_scr->UI_select_auton(autons::OFF_SKILLS); 
        auton_scr->flip_toggle_controller({1, 1}, auton_scr->off_skills); 
        auton_scr->save_auton_SD(); 
    });

    add_button(slot::MACRO, "Motor Menu", [](){ 
        UI_select_scr({motors_scr->get_motors_screen()});
        disable_user_control();
    });

    // Opens pnematic menu
    add_button(slot::MACRO, "Pneumatic Menu", [](){
        UI_select_scr(pneumatic_scr->get_pneumatic_screen()); 
        disable_user_control(); 
    });

    add_button(slot::MACRO, "Odom Offsets", [](){ config_measure_odometry_offsets(); });

    add_button(slot::MACRO, "Reset Offsets", [](){ config_measure_distance_reset_offsets(); });


    // Clears PID data off SD card
    add_button(slot::MACRO, "Wipe SD", [](){ 
        wipe_SD_file("auton.txt");
        wipe_SD_file("pid_data.txt");
    });

// DATA SLOTS

    // Add unplugged devices at program init to console
    add_button(slot::DATA, "Error Data", [](){ config_error_data(); });

    // Add motor tempurature values to console
    add_button(slot::DATA, "Motor Temps", [](){ config_motor_temp(); });

    // Add motor wattage values to console
    add_button(slot::DATA, "Motor Wattage", [](){ config_motor_wattage(); });

    // Add odom data to console
    add_button(slot::DATA, "Odom Data", [](){ config_odom_data(); });

    add_button(slot::DATA, "Reset Data", [](){ config_reset_data(); }); 

    // Add updated pid values from pid_tuner to console
    add_button(slot::DATA, "PID Data", [](){ config_add_pid_output_SD_console(); });

    // Add motor torque values
    add_button(slot::DATA, "Motor Torque", [](){ config_motor_torque(); });

    // Add motor efficiency values
    add_button(slot::DATA, "Motor Eff", [](){ config_motor_efficiency(); });

    // Add motor current values
    add_button(slot::DATA, "Motor Current", [](){ config_motor_current(); });

// TEST/TUNE SLOTS

    // Swaps the test mode to either test odom or test relative
    add_button(slot::TEST, "Tune Mode", [this](std::shared_ptr<UI_component> txt){
        bool mode = config_swap_test_mode();
        swap_mode(txt, mode);        
    });
    
    // Opens the tuner factory to tune drive
    add_button(slot::TEST, "Tune Drive", [](){ config_tune_drive(); });

    // Opens the tuner factory to tune heading
    add_button(slot::TEST, "Tune Heading", [](){ config_tune_heading(); });

    // Opens the tuner factory to tune turn
    add_button(slot::TEST, "Tune Turn", [](){ config_tune_turn(); });

    // Opens the tuner factory to tune swing
    add_button(slot::TEST, "Tune Swing", [](){ config_tune_swing(); });

    // Runs a test full test
    add_button(slot::TEST, "Test Full", [](){ 
        if (config_is_testing_odom()) {
            test_odom_full();
        } else {
            test_full(); 
        }
    });    
    
    // Runs a boomerang test
    add_button(slot::TEST, "Test Boomerng", [](){ test_boomerang(); });

    // Runs a motion chaininng test
    add_button(slot::TEST, "Test Chaining", [](){ 
        if (config_is_testing_odom()) {
            test_odom_motion_chaining();
        } else {
            test_motion_chaining(); 
        } 
    });

    add_button(slot::TEST, "Test Holonomic", [](){ test_holonomic(); });

    for (const auto& component : UI_config_scr->get_UI_components()) {
        component->set_y_pos(component->get_y_pos() - 45);
    }
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
