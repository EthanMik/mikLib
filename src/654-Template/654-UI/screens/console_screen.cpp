#include "vex.h"

std::shared_ptr<screen> UI_console_scr = nullptr;
std::shared_ptr<UI_component> UI_console_scr_border_sides = nullptr;
std::shared_ptr<UI_component> UI_console_scr_border_bottom = nullptr;

int text_start_pos_x = 10;
int text_start_pos_y = -18;

void UI_crt_console_scr() {
    auto bg = UI_crt_bg(UI_crt_rec(0, 0 , SCREEN_WIDTH, SCREEN_HEIGHT - 45, 0x00000000, UI_distance_units::pixels));

    UI_console_scr = UI_crt_scr(0, 45, SCREEN_WIDTH, SCREEN_HEIGHT - 45);
    UI_console_scr->add_scroll_bar(UI_crt_rec(0, 0, 3, 40, 0x00434343, UI_distance_units::pixels), screen::alignment::RIGHT);

    auto top_border = UI_crt_rec(3, 5, 465, 3, 0x00666666, UI_distance_units::pixels);
    auto left_border = UI_crt_rec(3, 5, 3, 180, 0x00666666, UI_distance_units::pixels);
    auto right_border = UI_crt_rec(465, 5, 3, 180, 0x00666666, UI_distance_units::pixels);
    auto bottom_border = UI_crt_rec(3, 185, 465, 3, 0x00666666, UI_distance_units::pixels);

    auto screen_border_top = UI_crt_gfx({top_border});
    UI_console_scr_border_sides = UI_crt_gfx({left_border, right_border});
    UI_console_scr_border_bottom = UI_crt_gfx({bottom_border});
    UI_console_scr->add_UI_components({bg, screen_border_top, UI_console_scr_border_sides, UI_console_scr_border_bottom});
}

void UI_reposition_text(int position) {
    text_start_pos_y -= 20;

    for (const auto& component : UI_console_scr->get_UI_components()) {
        int id = UI_decode_component_type(component->get_ID());
        if (id == 3) {
            if (component->get_y_pos() > position) {
                component->set_y_pos(component->get_y_pos() - 20);
            }
        }
        if (id == 4) {
            if (component->get_y_pos() > (position - 15)) {
                component->set_y_pos(component->get_y_pos() - 20);
            }
        }
    }
}