#include "mikLib/ui.h"
#include "test.h"

using namespace mik;

UI_motors_screen::UI_motors_screen() {
    UI_crt_motors_scr();
    UI_crt_reconstruct_scr();
}

void UI_motors_screen::UI_crt_motors_scr() {
    UI_motors_scr = UI_crt_scr(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT - 45);

    const int extra_buttons = 10; // Expands the screen to scroll
    const int extra_screen_height = 39 * extra_buttons + 5;
    UI_motors_scr = UI_crt_scr(0, 45, SCREEN_WIDTH, SCREEN_HEIGHT + extra_screen_height);
    UI_motors_scr->add_scroll_bar(UI_crt_rec(0, 0, 2, 40, config_scroll_bar_color, UI_distance_units::pixels), screen::alignment::RIGHT);
    auto bg = UI_crt_bg(UI_crt_rec(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, motors_bg_color, UI_distance_units::pixels));
    UI_motors_scr->add_UI_component(bg);

    // Voltage control
    auto volt_label = UI_crt_txtbox("Volt", mik::text_align::CENTER, UI_crt_rec(423, 45, 45, 26, "#000000"), vex::fontType::mono20, 0);
    auto crt_voltage_btn = [this](const std::string& label, std::function<void()> callback, float y, char id){

        auto volt_12_btn = UI_crt_tgl(UI_crt_rec(426, y, 40, 40, motors_volt_btn_bg_color, motors_volt_btn_outline_color, 2), callback);
        volt_12_btn->set_states(UI_crt_rec(426, y, 40, 40, motors_volt_btn_bg_color, motors_volt_btn_pressed_color, 2), UI_crt_rec(426, y, 40, 40, motors_volt_btn_bg_color, motors_volt_btn_pressing_color, 2));
        auto volt_12_label = UI_crt_txtbox(label, text_align::CENTER, UI_crt_rec(429, y + 8, 33, 24, motors_volt_btn_bg_color), vex::fontType::mono20, 0);
        volt_toggles.push_back({ static_cast<mik::toggle*>(volt_12_btn.get()), id });

        UI_motors_scr->add_UI_components({
            volt_12_btn, volt_12_label
        });
    };

    auto toggle_voltage = [this](char volt_id, float set_volts, bool press = false){
        for (auto tgl : volt_toggles) {
            if (tgl.second == volt_id) {
                if (press) tgl.first->press();
                tgl.first->lock_toggle();
                continue;
            }
            tgl.first->unpress();
        }
        set_voltage = set_volts;
    };

    crt_voltage_btn("12", [toggle_voltage](){ toggle_voltage('1', 12); }, 80, '1');
    crt_voltage_btn("9", [toggle_voltage](){ toggle_voltage('2', 9); }, 80+50, '2');
    crt_voltage_btn("6", [toggle_voltage](){ toggle_voltage('3', 6); }, 80+100, '3');
    crt_voltage_btn("3", [toggle_voltage](){ toggle_voltage('4', 3); }, 80+150, '4');
    toggle_voltage('1', 12, true);

    auto left_drive_label = UI_crt_txtbox("Left Drive", mik::text_align::CENTER, UI_crt_rec(3, 45, 138, 26, "#000000"), vex::fontType::mono20, 0);
    auto right_drive_label = UI_crt_txtbox("Right Drive", mik::text_align::CENTER, UI_crt_rec(3+140, 45, 138, 26, "#000000"), vex::fontType::mono20, 0);
    auto assembly_label = UI_crt_txtbox("Assembly", mik::text_align::CENTER, UI_crt_rec(3+140*2, 45, 138, 26, "#000000"), vex::fontType::mono20, 0);

    // Create a motor button

    UI_motors_scr->add_UI_components({
        left_drive_label, volt_label, assembly_label, right_drive_label
    });

    for (const auto& component : UI_motors_scr->get_UI_components()) {
        component->set_y_pos(component->get_y_pos() - 45);
    }
}

void UI_motors_screen::crt_motor_btns(mik::motor* mtr, int x, int y) {
    auto move_motor_left = UI_crt_tgl(UI_crt_rec(x, y, 30, 40, motors_spin_left_bg_color, motors_spin_left_outline_color, 2), [](){});
    move_motor_left->set_states(UI_crt_rec(x, y, 30, 40, motors_spin_left_bg_color, motors_spin_left_pressing_color, 2), UI_crt_rec(x, y, 30, 40, motors_spin_left_bg_color, motors_spin_left_pressed_color, 2));
    auto left_arrow = UI_crt_txtbox("<", mik::text_align::CENTER, UI_crt_rec(x + 5, y + 5, 20, 20, motors_spin_left_bg_color), vex::fontType::mono20, 0);

    auto motor_port_btn = UI_crt_btn(UI_crt_rec(x + 40, y, 40, 40, motors_left_drive_btn_bg_color, motors_port_btn_outline_color, 2), [this](){ 
        UI_swap_screens({UI_reconstruct_scr});
    });


    auto motor_port_txt = UI_crt_txtbox("0", "#ffffff", motors_left_drive_btn_bg_color, text_align::CENTER, UI_crt_rec(x + 42, y + 5, 36, 24, motors_left_drive_btn_bg_color), vex::fontType::mono20, 0);

    auto move_motor_right = UI_crt_tgl(UI_crt_rec(x + 90, y, 30, 40, motors_spin_left_bg_color, motors_spin_left_outline_color, 2), [](){});
    move_motor_right->set_states(UI_crt_rec(x + 90, y, 30, 40, motors_spin_left_bg_color, motors_spin_left_pressing_color, 2), UI_crt_rec(x + 90, y, 30, 40, motors_spin_left_bg_color, motors_spin_left_pressed_color, 2));
    auto right_arrow = UI_crt_txtbox(">", mik::text_align::CENTER, UI_crt_rec(x + 95, y + 5, 20, 20, motors_spin_left_bg_color), vex::fontType::mono20, 0);

    auto* left_tgl = static_cast<mik::toggle*>(move_motor_left.get());
    auto* right_tgl = static_cast<mik::toggle*>(move_motor_right.get());

    this->motor_texts.push_back({static_cast<mik::textbox*>(motor_port_txt.get()), mtr});
    this->motor_toggles.push_back({left_tgl, right_tgl, mtr, false, false, false});
    int toggle_idx = this->motor_toggles.size() - 1;

    left_tgl->set_callback([this, mtr, right_tgl, toggle_idx](){
        right_tgl->unpress();
        mtr->spin(vex::reverse, set_voltage, vex::volt);
        motor_toggles[toggle_idx].user_pressed = true;
    });

    right_tgl->set_callback([this, mtr, left_tgl, toggle_idx](){
        left_tgl->unpress();
        mtr->spin(vex::fwd, set_voltage, vex::volt);
        motor_toggles[toggle_idx].user_pressed = true;
    });

    auto left_hidden_btn = UI_crt_btn(UI_crt_rec(x + 90, y, 30, 40, motors_spin_left_bg_color), [this, mtr, left_tgl, toggle_idx](){
        if (!left_tgl->get_toggle_state()) {
            mtr->stop(vex::coast);
            motor_toggles[toggle_idx].user_stopped = true;
            motor_toggles[toggle_idx].user_pressed = false;
        }
    });

    auto right_hidden_btn = UI_crt_btn(UI_crt_rec(x, y, 30, 40, motors_spin_left_bg_color), [this, mtr, right_tgl, toggle_idx](){
        if (!right_tgl->get_toggle_state()) {
            mtr->stop(vex::coast);
            motor_toggles[toggle_idx].user_stopped = true;
            motor_toggles[toggle_idx].user_pressed = false;
        }
    });

    UI_motors_scr->add_UI_components({
        left_hidden_btn, right_hidden_btn,
        move_motor_right, right_arrow,
        move_motor_left, left_arrow,
        motor_port_btn, motor_port_txt
    });
}

void UI_motors_screen::init_motors() {
    auto motors = config_get_motors();
    int idx = 0;

    for (; idx < chassis.left_drive.getMotors().size(); ++idx) {
        crt_motor_btns(motors[idx], 10, 35 + (int)(idx * 50));
    }
    for (int i = 0; idx < chassis.right_drive.getMotors().size() + chassis.left_drive.getMotors().size(); ++idx, ++i) {
        crt_motor_btns(motors[idx], 10+140, 35 + (int)(i * 50));
    }
    for (int i = 0; idx < motors.size(); ++idx, ++i) {
        crt_motor_btns(motors[idx], 10+140*2, 35 + (int)(i * 50));
    }

    UI_motors_scr->add_render_callback([this](){ update_motors_screen(); });
    UI_reconstruct_scr->add_render_callback([this](){ update_reconstruct_screen(); });
}

void UI_motors_screen::update_motors_screen() {
    for (auto& item : motor_texts) {
        item.first->set_text(to_string(item.second->index() + 1));

        if (!item.second->installed()) {
            item.first->set_text_color(UI_red);
        } else {
            item.first->set_text_color(UI_white);
        }
    }

    for (auto& entry : motor_toggles) {
        double velo = entry.mtr->velocity(vex::rpm);
        bool left_on = entry.left_tgl->get_toggle_state();
        bool right_on = entry.right_tgl->get_toggle_state();

        if (entry.user_stopped) {
            if (velo == 0) {
                entry.user_stopped = false;
                entry.was_spinning = false;
            }
            continue;
        }

        if (velo < 0 && !left_on) {
            if (right_on) { entry.right_tgl->unpress(); }
            entry.left_tgl->press();
            entry.was_spinning = true;
        } else if (velo > 0 && !right_on) {
            if (left_on) { entry.left_tgl->unpress(); }
            entry.right_tgl->press();
            entry.was_spinning = true;
        } else if (velo == 0 && entry.was_spinning) {
            entry.was_spinning = false;
            if (left_on) { entry.left_tgl->unpress(); }
            if (right_on) { entry.right_tgl->unpress(); }
        }
    }

    bool any_user_pressed = false;
    for (auto& entry : motor_toggles) {
        if (entry.user_pressed) { any_user_pressed = true; break; }
    }
    if (any_user_pressed) { disable_user_control(); }
    else { enable_user_control(); }
}

void UI_motors_screen::reconstruct_motor(mik::motor* mtr, int new_port, vex::gearSetting new_cart, bool new_rev) {
    mtr->stop(vex::coast);

    std::string name = mtr->name();

    mtr->~motor();
    new(mtr) mik::motor(new_port, new_rev, new_cart, name);
}

void UI_motors_screen::UI_crt_reconstruct_scr() {
    UI_reconstruct_scr = UI_crt_scr(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    auto bg = UI_crt_bg(UI_crt_rec(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, motors_bg_color, UI_distance_units::pixels));
    UI_reconstruct_scr->add_UI_component(bg);


    auto motor_label_component = UI_crt_txtbox("Motor X", mik::text_align::CENTER, UI_crt_rec(80, 20, 230, 25, motors_bg_color), vex::fontType::mono20, 0);
    motor_label = static_cast<mik::textbox*>(motor_label_component.get());

    auto exit_bg = UI_crt_btn(UI_crt_rec(2, 2, 40, 40, motors_bg_color, motors_close_button_outline_color, 2, UI_distance_units::pixels), [this](){ UI_select_scr(UI_motors_scr); });
        exit_bg->set_states(UI_crt_rec(2, 2, 40, 40, motors_bg_color, motors_close_button_pressing_color, 2, UI_distance_units::pixels), UI_crt_rec(2, 2, 40, 40, motors_bg_color, motors_close_button_pressed_color, 2, UI_distance_units::pixels));
    auto exit_txt = UI_crt_gfx({UI_crt_rec(4, 4, 36, 36, motors_bg_color, UI_distance_units::pixels), UI_crt_txt("X", 17, 27, motors_ports_text_color, motors_bg_color, mik::UI_distance_units::pixels)});
    UI_reconstruct_scr->add_UI_components({exit_bg, exit_txt, motor_label_component});
 
    const auto ports = 21;
    for (size_t i = 0; i < ports; ++i) {
        auto port_btn = UI_crt_btn(UI_crt_rec(50 + (i % 7) * 57, 65 + (i / 7) * 60, 40, 40, motors_ports_btn_bg, motors_ports_btn_current_color, 2), [](){});
        auto port_btn_text = UI_crt_txtbox(to_string(i + 1), text_align::CENTER, UI_crt_rec(55 + (i % 7) * 57, 70 + (i / 7) * 60, 30, 25, motors_ports_btn_bg), vex::fontType::mono20, 0);
        port_button_list.at(i) = {
            static_cast<mik::button*>(port_btn.get()),
            static_cast<mik::textbox*>(port_btn_text.get())
        };

        UI_reconstruct_scr->add_UI_components({port_btn, port_btn_text});
    }
}

void UI_motors_screen::update_reconstruct_screen() {
    // if (!selected_mtr) return;
    selected_mtr = config_get_motors()[0];

    const auto name = selected_mtr->name();
    const auto cart = selected_mtr->gear_cartridge();
    const auto rev = selected_mtr->reversed();
    const auto port = selected_mtr->index();
    
    motor_label->set_text(name);

    const size_t size = config_get_motors().size();
    std::vector<int> ports;
    for (auto& mtr : config_get_motors()) {
        if (mtr->index() != selected_mtr->index()) {
            ports.push_back(mtr->index());
        }
    }

    size_t port_idx = 0;
    const size_t port_amount = 21;
    for (auto& item : port_button_list) {
        const float btn_x = item.port_btn->get_x_pos();
        const float btn_y = item.port_btn->get_y_pos();
        const float btn_w = item.port_btn->get_width();
        const float btn_h = item.port_btn->get_height();

        std::string color = motors_ports_btn_open_color;

        if (port_idx == selected_mtr->index()) {
            color = motors_ports_btn_current_color;
            print(color);
        } else if (std::find(ports.begin(), ports.end(), port_idx) != ports.end()) {
            color = motors_ports_btn_closed_color;
            print(color);
        }

        item.port_btn->set_default_state(UI_crt_rec(btn_x, btn_y, btn_w, btn_h, motors_ports_btn_bg, color, 2));
        item.port_txt->set_text_color(color);
        port_idx++;
    }
}

std::shared_ptr<screen> UI_motors_screen::get_motors_screen() {
    return UI_motors_scr;
}
