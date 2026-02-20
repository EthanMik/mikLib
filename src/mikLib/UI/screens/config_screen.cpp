#include "mikLib/ui.h"
#include "test.h"

using namespace mik;

UI_config_screen::UI_config_screen() {
    UI_crt_config_scr();
    UI_crt_pnematics_scr();
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
    const int extra_buttons = 2; // Expands the screen to scroll
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

    // Spins each motor forwards for half a second
    add_button(slot::MACRO, "Motor Menu", [](){ 
        UI_select_scr({motors_scr->get_motors_screen()}); 
    });

    // Opens pnematic menu
    add_button(slot::MACRO, "Pnematic Menu", [this](){
        UI_swap_screens({UI_pnematics_scr}); 
        disable_user_control(); 
    });

    add_button(slot::MACRO, "Get Offsets", [](){ config_measure_offsets(); });

    add_button(slot::MACRO, "Get Vel/Accel", [](){ config_measure_velocity_accel(); });

    // Clears PID data off SD card
    add_button(slot::MACRO, "Wipe PID Data", [](){ wipe_SD_file("pid_data.txt"); });

    // Wipes selected auto off the SD card
    add_button(slot::MACRO, "Wipe Sel Auto", [](){ wipe_SD_file("auton.txt"); });

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

    // Runs a pure pursuit test
    add_button(slot::TEST, "Test Pursuit", [](){ test_pursuit(); });


    for (const auto& component : UI_config_scr->get_UI_components()) {
        component->set_y_pos(component->get_y_pos() - 45);
    }
}

void UI_config_screen::UI_crt_pnematics_scr() {
    UI_pnematics_scr = UI_crt_scr(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    auto bg = UI_crt_bg(UI_crt_rec(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, pnematic_bg_color, UI_distance_units::pixels));

    auto title_txt = UI_crt_txtbox(
        "Pneumatics Menu",
        pnematic_text_color, pnematic_bg_color, text_align::CENTER,
        UI_crt_rec(50, 10, 200, 30, pnematic_bg_color, UI_distance_units::pixels)
    );

    const float txt_x = .34;
    const float txt_y = .45;

    auto expander_port_idx = std::make_shared<int>(0);

    float x = .23;
    float y = .60;

    auto port_A_btn = UI_crt_btn(UI_crt_img("", x, y, .75, .75, UI_distance_units::inches), [expander_port_idx](){ *expander_port_idx == 0 ? config_test_three_wire_port(PORT_A) : config_test_three_wire_port(*expander_port_idx, PORT_A); });
    auto port_A = UI_crt_tgl(UI_crt_grp({ UI_crt_rec(x, y, .75, .75, pnematic_A_btn_bg_color, pnematic_port_btn_outline_color, 5, UI_distance_units::inches), UI_crt_txt("A", x+txt_x, y+txt_y, pnematic_text_color, pnematic_A_btn_bg_color, UI_distance_units::inches)}), [](){});
    port_A->set_states(
        UI_crt_grp({ UI_crt_rec(x, y, .75, .75, pnematic_A_btn_bg_color, pnematic_port_btn_outline_pressing_color, 5, UI_distance_units::inches), UI_crt_txt("A", x+txt_x, y+txt_y, pnematic_text_color, pnematic_A_btn_bg_color, UI_distance_units::inches)}),
        UI_crt_grp({ UI_crt_rec(x, y, .75, .75, pnematic_A_btn_bg_color, pnematic_port_btn_outline_pressed_color, 5, UI_distance_units::inches), UI_crt_txt("A", x+txt_x, y+txt_y, pnematic_text_color, pnematic_A_btn_bg_color, UI_distance_units::inches)})
    );

    x = 1.48;
    y = .60;

    auto port_B_btn = UI_crt_btn(UI_crt_img("", x, y, .75, .75, UI_distance_units::inches), [expander_port_idx](){ *expander_port_idx == 0 ? config_test_three_wire_port(PORT_B) : config_test_three_wire_port(*expander_port_idx, PORT_B); });
    auto port_B = UI_crt_tgl(UI_crt_grp({ UI_crt_rec(x, y, .75, .75, pnematic_B_btn_bg_color, pnematic_port_btn_outline_color, 5, UI_distance_units::inches), UI_crt_txt("B", x+txt_x, y+txt_y, pnematic_text_color, pnematic_B_btn_bg_color, UI_distance_units::inches)}), [](){});
    port_B->set_states(
        UI_crt_grp({ UI_crt_rec(x, y, .75, .75, pnematic_B_btn_bg_color, pnematic_port_btn_outline_pressing_color, 5, UI_distance_units::inches), UI_crt_txt("B", x+txt_x, y+txt_y, pnematic_text_color, pnematic_B_btn_bg_color, UI_distance_units::inches)}),
        UI_crt_grp({ UI_crt_rec(x, y, .75, .75, pnematic_B_btn_bg_color, pnematic_port_btn_outline_pressed_color, 5, UI_distance_units::inches), UI_crt_txt("B", x+txt_x, y+txt_y, pnematic_text_color, pnematic_B_btn_bg_color, UI_distance_units::inches)})
    );

    x = 2.73;
    y = .60;

    auto port_C_btn = UI_crt_btn(UI_crt_img("", x, y, .75, .75, UI_distance_units::inches), [expander_port_idx](){ *expander_port_idx == 0 ? config_test_three_wire_port(PORT_C) : config_test_three_wire_port(*expander_port_idx, PORT_C); });
    auto port_C = UI_crt_tgl(UI_crt_grp({ UI_crt_rec(x, y, .75, .75, pnematic_C_btn_bg_color, pnematic_port_btn_outline_color, 5, UI_distance_units::inches), UI_crt_txt("C", x+txt_x, y+txt_y, pnematic_text_color, pnematic_C_btn_bg_color, UI_distance_units::inches)}), [](){});
    port_C->set_states(
        UI_crt_grp({ UI_crt_rec(x, y, .75, .75, pnematic_C_btn_bg_color, pnematic_port_btn_outline_pressing_color, 5, UI_distance_units::inches), UI_crt_txt("C", x+txt_x, y+txt_y, pnematic_text_color, pnematic_C_btn_bg_color, UI_distance_units::inches)}),
        UI_crt_grp({ UI_crt_rec(x, y, .75, .75, pnematic_C_btn_bg_color, pnematic_port_btn_outline_pressed_color, 5, UI_distance_units::inches), UI_crt_txt("C", x+txt_x, y+txt_y, pnematic_text_color, pnematic_C_btn_bg_color, UI_distance_units::inches)})
    );

    x = 3.98;
    y = .60;

    auto port_D_btn = UI_crt_btn(UI_crt_img("", x, y, .75, .75, UI_distance_units::inches), [expander_port_idx](){ *expander_port_idx == 0 ? config_test_three_wire_port(PORT_D) : config_test_three_wire_port(*expander_port_idx, PORT_D); });
    auto port_D = UI_crt_tgl(UI_crt_grp({ UI_crt_rec(x, y, .75, .75, pnematic_D_btn_bg_color, pnematic_port_btn_outline_color, 5, UI_distance_units::inches), UI_crt_txt("D", x+txt_x, y+txt_y, pnematic_text_color, pnematic_D_btn_bg_color, UI_distance_units::inches)}), [](){});
    port_D->set_states(
        UI_crt_grp({ UI_crt_rec(x, y, .75, .75, pnematic_D_btn_bg_color, pnematic_port_btn_outline_pressing_color, 5, UI_distance_units::inches), UI_crt_txt("D", x+txt_x, y+txt_y, pnematic_text_color, pnematic_D_btn_bg_color, UI_distance_units::inches)}),
        UI_crt_grp({ UI_crt_rec(x, y, .75, .75, pnematic_D_btn_bg_color, pnematic_port_btn_outline_pressed_color, 5, UI_distance_units::inches), UI_crt_txt("D", x+txt_x, y+txt_y, pnematic_text_color, pnematic_D_btn_bg_color, UI_distance_units::inches)})
    );

    x = .23;
    y = 1.62;

    auto port_E_btn = UI_crt_btn(UI_crt_img("", x, y, .75, .75, UI_distance_units::inches), [expander_port_idx](){ *expander_port_idx == 0 ? config_test_three_wire_port(PORT_E) : config_test_three_wire_port(*expander_port_idx, PORT_E); });
    auto port_E = UI_crt_tgl(UI_crt_grp({ UI_crt_rec(x, y, .75, .75, pnematic_E_btn_bg_color, pnematic_port_btn_outline_color, 5, UI_distance_units::inches), UI_crt_txt("E", x+txt_x, y+txt_y, pnematic_text_color, pnematic_E_btn_bg_color, UI_distance_units::inches)}), [](){});
    port_E->set_states(
        UI_crt_grp({ UI_crt_rec(x, y, .75, .75, pnematic_E_btn_bg_color, pnematic_port_btn_outline_pressing_color, 5, UI_distance_units::inches), UI_crt_txt("E", x+txt_x, y+txt_y, pnematic_text_color, pnematic_E_btn_bg_color, UI_distance_units::inches)}),
        UI_crt_grp({ UI_crt_rec(x, y, .75, .75, pnematic_E_btn_bg_color, pnematic_port_btn_outline_pressed_color, 5, UI_distance_units::inches), UI_crt_txt("E", x+txt_x, y+txt_y, pnematic_text_color, pnematic_E_btn_bg_color, UI_distance_units::inches)})
    );

    x = 1.48;
    y = 1.62;

    auto port_F_btn = UI_crt_btn(UI_crt_img("", x, y, .75, .75, UI_distance_units::inches), [expander_port_idx](){ *expander_port_idx == 0 ? config_test_three_wire_port(PORT_F) : config_test_three_wire_port(*expander_port_idx, PORT_F); });
    auto port_F = UI_crt_tgl(UI_crt_grp({ UI_crt_rec(x, y, .75, .75, pnematic_F_btn_bg_color, pnematic_port_btn_outline_color, 5, UI_distance_units::inches), UI_crt_txt("F", x+txt_x, y+txt_y, pnematic_text_color, pnematic_F_btn_bg_color, UI_distance_units::inches)}), [](){});
    port_F->set_states(
        UI_crt_grp({ UI_crt_rec(x, y, .75, .75, pnematic_F_btn_bg_color, pnematic_port_btn_outline_pressing_color, 5, UI_distance_units::inches), UI_crt_txt("F", x+txt_x, y+txt_y, pnematic_text_color, pnematic_F_btn_bg_color, UI_distance_units::inches)}),
        UI_crt_grp({ UI_crt_rec(x, y, .75, .75, pnematic_F_btn_bg_color, pnematic_port_btn_outline_pressed_color, 5, UI_distance_units::inches), UI_crt_txt("F", x+txt_x, y+txt_y, pnematic_text_color, pnematic_F_btn_bg_color, UI_distance_units::inches)})
    );

    x = 2.73;
    y = 1.62;

    auto port_G_btn = UI_crt_btn(UI_crt_img("", x, y, .75, .75, UI_distance_units::inches), [expander_port_idx](){ *expander_port_idx == 0 ? config_test_three_wire_port(PORT_G) : config_test_three_wire_port(*expander_port_idx, PORT_G); });
    auto port_G = UI_crt_tgl(UI_crt_grp({ UI_crt_rec(x, y, .75, .75, pnematic_G_btn_bg_color, pnematic_port_btn_outline_color, 5, UI_distance_units::inches), UI_crt_txt("G", x+txt_x, y+txt_y, pnematic_text_color, pnematic_G_btn_bg_color, UI_distance_units::inches)}), [](){});
    port_G->set_states(
        UI_crt_grp({ UI_crt_rec(x, y, .75, .75, pnematic_G_btn_bg_color, pnematic_port_btn_outline_pressing_color, 5, UI_distance_units::inches), UI_crt_txt("G", x+txt_x, y+txt_y, pnematic_text_color, pnematic_G_btn_bg_color, UI_distance_units::inches)}),
        UI_crt_grp({ UI_crt_rec(x, y, .75, .75, pnematic_G_btn_bg_color, pnematic_port_btn_outline_pressed_color, 5, UI_distance_units::inches), UI_crt_txt("G", x+txt_x, y+txt_y, pnematic_text_color, pnematic_G_btn_bg_color, UI_distance_units::inches)})
    );

    x = 3.98;
    y = 1.62;

    auto port_H_btn = UI_crt_btn(UI_crt_img("", x, y, .75, .75, UI_distance_units::inches), [expander_port_idx](){ *expander_port_idx == 0 ? config_test_three_wire_port(PORT_H) : config_test_three_wire_port(*expander_port_idx, PORT_H); });
    auto port_H = UI_crt_tgl(UI_crt_grp({ UI_crt_rec(x, y, .75, .75, pnematic_H_btn_bg_color, pnematic_port_btn_outline_color, 5, UI_distance_units::inches), UI_crt_txt("H", x+txt_x, y+txt_y, pnematic_text_color, pnematic_H_btn_bg_color, UI_distance_units::inches)}), [](){});
    port_H->set_states(
        UI_crt_grp({ UI_crt_rec(x, y, .75, .75, pnematic_H_btn_bg_color, pnematic_port_btn_outline_pressing_color, 5, UI_distance_units::inches), UI_crt_txt("H", x+txt_x, y+txt_y, pnematic_text_color, pnematic_H_btn_bg_color, UI_distance_units::inches)}),
        UI_crt_grp({ UI_crt_rec(x, y, .75, .75, pnematic_H_btn_bg_color, pnematic_port_btn_outline_pressed_color, 5, UI_distance_units::inches), UI_crt_txt("H", x+txt_x, y+txt_y, pnematic_text_color, pnematic_H_btn_bg_color, UI_distance_units::inches)})
    );

    auto reset_port_btns = [port_A, port_B, port_C, port_D, port_E, port_F, port_G, port_H]() {
        static_cast<toggle*>(port_A.get())->unpress();
        static_cast<toggle*>(port_B.get())->unpress();
        static_cast<toggle*>(port_C.get())->unpress();
        static_cast<toggle*>(port_D.get())->unpress();
        static_cast<toggle*>(port_E.get())->unpress();
        static_cast<toggle*>(port_F.get())->unpress();
        static_cast<toggle*>(port_G.get())->unpress();
        static_cast<toggle*>(port_H.get())->unpress();
    };

    int btn_height = 10;
    int btn_w = 30;
    int btn_h = 30;
    int txt_height = btn_height + 20;

    auto update_expander_txt = [](std::shared_ptr<UI_component> expander_txt, int idx) {
        auto* txt = static_cast<textbox*>(expander_txt.get());
        txt->set_text(idx == 0 ? "Brain" : "PORT" + to_string(idx));
    };

    auto expander_txt = UI_crt_txtbox(
        "Brain",
        pnematic_text_color, pnematic_bg_color, text_align::CENTER,
        UI_crt_rec(318, 10, 90, 30, pnematic_bg_color, UI_distance_units::pixels)
    );

    auto expander_minus7_btn = UI_crt_btn(
        UI_crt_rec(247, btn_height, btn_w, btn_h, pnematic_bg_color, pnematic_close_btn_outline_color, 2, UI_distance_units::pixels),
        [expander_port_idx, expander_txt, update_expander_txt, reset_port_btns](){
            *expander_port_idx = (*expander_port_idx - 7 + 22) % 22;
            update_expander_txt(expander_txt, *expander_port_idx);
            reset_port_btns();
        }
    );
    expander_minus7_btn->set_states(
        UI_crt_rec(247, btn_height, btn_w, btn_h, pnematic_bg_color, pnematic_close_btn_pressing_color, 2, UI_distance_units::pixels),
        UI_crt_rec(247, btn_height, btn_w, btn_h, pnematic_bg_color, pnematic_close_btn_pressed_color, 2, UI_distance_units::pixels)
    );
    auto expander_minus7_lbl = UI_crt_gfx(UI_crt_txt("-7", 252, txt_height, pnematic_text_color, pnematic_bg_color, UI_distance_units::pixels));

    auto expander_minus1_btn = UI_crt_btn(
        UI_crt_rec(285, btn_height, btn_w, btn_h, pnematic_bg_color, pnematic_close_btn_outline_color, 2, UI_distance_units::pixels),
        [expander_port_idx, expander_txt, update_expander_txt, reset_port_btns](){
            *expander_port_idx = (*expander_port_idx - 1 + 22) % 22;
            update_expander_txt(expander_txt, *expander_port_idx);
            reset_port_btns();
        }
    );
    expander_minus1_btn->set_states(
        UI_crt_rec(285, btn_height, btn_w, btn_h, pnematic_bg_color, pnematic_close_btn_pressing_color, 2, UI_distance_units::pixels),
        UI_crt_rec(285, btn_height, btn_w, btn_h, pnematic_bg_color, pnematic_close_btn_pressed_color, 2, UI_distance_units::pixels)
    );
    auto expander_minus1_lbl = UI_crt_gfx(UI_crt_txt("-1", 289, txt_height, pnematic_text_color, pnematic_bg_color, UI_distance_units::pixels));

    auto expander_plus1_btn = UI_crt_btn(
        UI_crt_rec(407, btn_height, btn_w, btn_h, pnematic_bg_color, pnematic_close_btn_outline_color, 2, UI_distance_units::pixels),
        [expander_port_idx, expander_txt, update_expander_txt, reset_port_btns](){
            *expander_port_idx = (*expander_port_idx + 1) % 22;
            update_expander_txt(expander_txt, *expander_port_idx);
            reset_port_btns();
        }
    );
    expander_plus1_btn->set_states(
        UI_crt_rec(407, btn_height, btn_w, btn_h, pnematic_bg_color, pnematic_close_btn_pressing_color, 2, UI_distance_units::pixels),
        UI_crt_rec(407, btn_height, btn_w, btn_h, pnematic_bg_color, pnematic_close_btn_pressed_color, 2, UI_distance_units::pixels)
    );
    auto expander_plus1_lbl = UI_crt_gfx(UI_crt_txt("+1", 412, txt_height, pnematic_text_color, pnematic_bg_color, UI_distance_units::pixels));

    auto expander_plus7_btn = UI_crt_btn(
        UI_crt_rec(445, btn_height, btn_w, btn_h, pnematic_bg_color, pnematic_close_btn_outline_color, 2, UI_distance_units::pixels),
        [expander_port_idx, expander_txt, update_expander_txt, reset_port_btns](){
            *expander_port_idx = (*expander_port_idx + 7) % 22;
            update_expander_txt(expander_txt, *expander_port_idx);
            reset_port_btns();
        }
    );
    expander_plus7_btn->set_states(
        UI_crt_rec(445, btn_height, btn_w, btn_h, pnematic_bg_color, pnematic_close_btn_pressing_color, 2, UI_distance_units::pixels),
        UI_crt_rec(445, btn_height, btn_w, btn_h, pnematic_bg_color, pnematic_close_btn_pressed_color, 2, UI_distance_units::pixels)
    );
    auto expander_plus7_lbl = UI_crt_gfx(UI_crt_txt("+7", 451, txt_height, pnematic_text_color, pnematic_bg_color, UI_distance_units::pixels));

    auto exit_bg = UI_crt_btn(UI_crt_rec(2, 2, 40, 40, pnematic_close_btn_bg_color, pnematic_close_btn_outline_color, 2, UI_distance_units::pixels), [](){ UI_select_scr(config_scr->get_config_screen()); enable_user_control(); });
        exit_bg->set_states(UI_crt_rec(2, 2, 40, 40, pnematic_close_btn_bg_color, pnematic_close_btn_pressing_color, 2, UI_distance_units::pixels), UI_crt_rec(2, 2, 40, 40, pnematic_close_btn_bg_color, pnematic_close_btn_pressed_color, 2, UI_distance_units::pixels));
    auto exit_txt = UI_crt_gfx({UI_crt_rec(4, 4, 36, 36, pnematic_close_btn_bg_color, UI_distance_units::pixels), UI_crt_txt("X", 17, 27, pnematic_text_color, pnematic_close_btn_bg_color, mik::UI_distance_units::pixels)});

    UI_pnematics_scr->add_UI_components({bg, title_txt, exit_bg, exit_txt, expander_txt, expander_minus7_btn, expander_minus7_lbl, expander_minus1_btn, expander_minus1_lbl, expander_plus1_btn, expander_plus1_lbl, expander_plus7_btn, expander_plus7_lbl, port_A_btn, port_A, port_B_btn, port_B, port_C_btn, port_C, port_D_btn, port_D, port_E_btn, port_E, port_F_btn, port_F, port_G_btn, port_G, port_H_btn, port_H});
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
