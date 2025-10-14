#include "vex.h"

using namespace mik;

UI_console_screen::UI_console_screen() {
    UI_crt_console_scr();
}

void UI_console_screen::add(const std::string& label_text, bool txt) {
    add_impl(label_text, [](){ return ""; });
}

std::shared_ptr<screen> UI_console_screen::get_console_screen() {
    return(this->UI_console_scr);
}

void UI_console_screen::UI_crt_console_scr() {
    auto bg = UI_crt_bg(UI_crt_rec(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT - 45, console_bg_color, UI_distance_units::pixels));

    this->UI_console_scr = UI_crt_scr(0, 45, SCREEN_WIDTH, SCREEN_HEIGHT - 45);
    UI_console_scr->add_scroll_bar(UI_crt_rec(0, 0, 3, 40, console_scroll_bar_color, UI_distance_units::pixels), screen::alignment::RIGHT);

    auto top_border = UI_crt_rec(3, 5, 465, 3, console_outline_color, UI_distance_units::pixels);
    auto left_border = UI_crt_rec(3, 5, 3, 180, console_outline_color, UI_distance_units::pixels);
    auto right_border = UI_crt_rec(465, 5, 3, 180, console_outline_color, UI_distance_units::pixels);
    auto bottom_border = UI_crt_rec(3, 185, 465, 3, console_outline_color, UI_distance_units::pixels);

    auto screen_border_top = UI_crt_gfx({top_border});
    UI_console_scr_border_sides = UI_crt_gfx({left_border, right_border});
    UI_console_scr_border_bottom = UI_crt_gfx({bottom_border});
    this->UI_console_scr->add_UI_components({bg, screen_border_top, UI_console_scr_border_sides, UI_console_scr_border_bottom});
}
    
void UI_console_screen::reset() {
    std::vector<int> remove_components;
    for (const auto& component : this->UI_console_scr->get_UI_components()) {
        int id = UI_decode_component_type(component->get_ID());
        if (id == 3 || id == 4) {
            remove_components.push_back(component->get_ID());
        }
    }
    UI_console_scr->remove_UI_component(remove_components);
    text_start_pos_x = 10;
    text_start_pos_y = -18; 
}

void UI_console_screen::UI_reposition_text(int position) {
    text_start_pos_y -= 20;

    for (const auto& component : this->UI_console_scr->get_UI_components()) {
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