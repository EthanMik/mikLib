#include "vex.h"

std::shared_ptr<screen> UI_console_scr = nullptr;

void UI_crt_console_scr() {

    auto main_bg = UI_crt_bg(UI_crt_img("background_main.png", 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, UI_distance_units::inches));

    UI_console_scr = UI_crt_scr(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    UI_console_scr->add_scroll_bar(UI_crt_rec(0, 0, 3, 40, 0x00434343, UI_distance_units::pixels), screen::alignment::RIGHT);

    UI_console_scr->add_UI_component(main_bg);
}

void UI_console_scr_add() {
    auto lbl = UI_crt_lbl("Chat the coordinates are: ", [](){ return chassis.turn_kd; }, 10, 70, UI_distance_units::pixels);
    UI_console_scr->add_UI_component(lbl);

}