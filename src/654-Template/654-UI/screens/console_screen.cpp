#include "vex.h"

std::shared_ptr<screen> UI_console_scr = nullptr;
std::shared_ptr<UI_component> UI_console_scr_border_sides = nullptr;
std::shared_ptr<UI_component> UI_console_scr_border_bottom = nullptr;

int text_start_pos_x = 10;
int text_start_pos_y = 27;

void UI_crt_console_scr() {

    // auto main_bg = UI_crt_bg(UI_crt_img("background_main.png", 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT - 45, UI_distance_units::pixels));
    auto main_bg = UI_crt_bg(UI_crt_rec(0, 0 , SCREEN_WIDTH, SCREEN_HEIGHT - 45, 0x00000000, UI_distance_units::pixels));

    UI_console_scr = UI_crt_scr(0, 45, SCREEN_WIDTH, SCREEN_HEIGHT - 45);
    UI_console_scr->add_scroll_bar(UI_crt_rec(0, 0, 3, 40, 0x00434343, UI_distance_units::pixels), screen::alignment::RIGHT);

    auto top_border = UI_crt_rec(3, 5, 465, 3, 0x00666666, UI_distance_units::pixels);
    auto left_border = UI_crt_rec(3, 5, 3, 180, 0x00666666, UI_distance_units::pixels);
    auto right_border = UI_crt_rec(465, 5, 3, 180, 0x00666666, UI_distance_units::pixels);
    auto bottom_border = UI_crt_rec(3, 185, 465, 3, 0x00666666, UI_distance_units::pixels);

    auto screen_border_top = UI_crt_gfx({top_border});
    UI_console_scr_border_sides = UI_crt_gfx({left_border, right_border});
    UI_console_scr_border_bottom = UI_crt_gfx({bottom_border});
    UI_console_scr->add_UI_components({main_bg, screen_border_top, UI_console_scr_border_sides, UI_console_scr_border_bottom});
    
}

void UI_console_scr_add() {
    auto lbl = UI_crt_lbl("Guys the Coordinates are: ", [](){ return chassis.get_X_position(); }, text_start_pos_x, text_start_pos_y, UI_distance_units::pixels);

    auto s = text_start_pos_y - 15;
    auto remove_lbl_btn = UI_crt_btn(
        UI_crt_rec(10, s, lbl->get_width(), 20, 0x00000000, UI_distance_units::pixels),
        UI_crt_rec(10, s, lbl->get_width(), 20, 0x006B6B6B, UI_distance_units::pixels),
        [](){}
    );
    text_start_pos_y += 20;


    if (lbl->get_y_pos() > UI_console_scr->get_height()) {
        int height_decrease = lbl->get_height();

        UI_console_scr->set_height(UI_console_scr->get_height() + height_decrease);
        UI_console_scr_border_sides->set_height(UI_console_scr_border_sides->get_height() + height_decrease);
        UI_console_scr_border_bottom->set_y_pos(UI_console_scr_border_bottom->get_y_pos() + height_decrease);
    }
    // auto lbl2 = UI_crt_lbl("Chat the coordinates are: ", [](){ return chassis.turn_kd; }, 13, 90, UI_distance_units::pixels);
    UI_console_scr->add_UI_components({remove_lbl_btn, lbl});

}