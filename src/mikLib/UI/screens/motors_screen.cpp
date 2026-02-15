#include "mikLib/ui.h"

using namespace mik;

UI_motors_screen::UI_motors_screen() {
    UI_crt_motors_scr();
}

void UI_motors_screen::UI_crt_motors_scr() {
    UI_motors_scr = UI_crt_scr(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT - 45);

    const int extra_buttons = 2; // Expands the screen to scroll
    const int extra_screen_height = 39 * extra_buttons + 5;
    UI_motors_scr = UI_crt_scr(0, 45, SCREEN_WIDTH, SCREEN_HEIGHT + extra_screen_height);
    UI_motors_scr->add_scroll_bar(UI_crt_rec(0, 0, 2, 40, config_scroll_bar_color, UI_distance_units::pixels), screen::alignment::RIGHT);
    auto bg = UI_crt_bg(UI_crt_rec(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, config_bg_color, UI_distance_units::pixels));

    auto left_drive_lab = UI_crt_txtbox("Left Drive", UI_crt_rec(9, 55, 138, 20, "#000000"));
    
    // Create a motor menu

    auto move_motor_left = UI_crt_btn(UI_crt_rec(23, 84, 30, 40, "#000000", "#666666", 2), [](){});
    // move_motor_left->set_states()


    UI_motors_scr->add_UI_components({
        bg, left_drive_lab
    });

    for (const auto& component : UI_motors_scr->get_UI_components()) {
        component->set_y_pos(component->get_y_pos() - 45);
    }
}

std::shared_ptr<screen> UI_motors_screen::get_motors_screen() {
    return UI_motors_scr;
}
