#include "mikLib/ui.h"
#include "test.h"

using namespace mik;

UI_motors_screen::UI_motors_screen() {
    UI_crt_motors_scr();
}

void UI_motors_screen::UI_crt_motors_scr() {
    UI_motors_scr = UI_crt_scr(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT - 45);

    const int extra_buttons = 10; // Expands the screen to scroll
    const int extra_screen_height = 39 * extra_buttons + 5;
    UI_motors_scr = UI_crt_scr(0, 45, SCREEN_WIDTH, SCREEN_HEIGHT + extra_screen_height);
    UI_motors_scr->add_scroll_bar(UI_crt_rec(0, 0, 2, 40, config_scroll_bar_color, UI_distance_units::pixels), screen::alignment::RIGHT);
    auto bg = UI_crt_bg(UI_crt_rec(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, config_bg_color, UI_distance_units::pixels));
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

    auto motor_port_btn = UI_crt_btn(UI_crt_rec(x + 40, y, 40, 40, motors_left_drive_btn_bg_color, motors_port_btn_outline_color, 2), [](){});
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

std::shared_ptr<screen> UI_motors_screen::get_motors_screen() {
    return UI_motors_scr;
}
