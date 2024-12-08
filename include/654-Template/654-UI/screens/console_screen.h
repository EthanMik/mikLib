#pragma once

#include "vex.h"

extern std::shared_ptr<screen> UI_console_scr;
extern int text_start_pos_x;
extern int text_start_pos_y;

extern std::shared_ptr<UI_component> UI_console_scr_border_sides;
extern std::shared_ptr<UI_component> UI_console_scr_border_bottom;

void UI_crt_console_scr();

void UI_reposition_text(int position);

template <typename data_type>
void UI_console_scr_add_impl(const std::string& label_text, data_type&& data);

template <typename F>
void UI_console_scr_add(const std::string& label_text, F&& data);

template <typename F>
void UI_console_scr_add(F&& data);

template <typename T>
void UI_console_scr_add(const std::string& label_text, T& data);

template <typename T>
void UI_console_scr_add(T& data);


template <typename F>
void UI_console_scr_add(const std::string& label_text, F&& data) {
    UI_console_scr_add_impl(label_text, std::forward<F>(data));
}

template <typename F>
void UI_console_scr_add(F&& data) {
    UI_console_scr_add_impl("", std::forward<F>(data));
}

template <typename T>
void UI_console_scr_add(const std::string& label_text, T& data) {
    UI_console_scr_add_impl(label_text, data);
}

template <typename T>
void UI_console_scr_add(T& data) {
    UI_console_scr_add_impl("", data);
}


template <typename data_type>
void UI_console_scr_add_impl(const std::string& label_text, data_type&& data) {

    int delta_label_y_pos = text_start_pos_y + UI_console_scr->get_component_delta_pos() + UI_console_scr->get_y_pos();
    int delta_button_y_pos = text_start_pos_y + UI_console_scr->get_component_delta_pos() + UI_console_scr->get_y_pos() - 15;
    int screen_increase_factor = 20;

    auto lbl = UI_crt_lbl(label_text, std::forward<data_type>(data), text_start_pos_x, delta_label_y_pos, UI_distance_units::pixels);

    int button_width = std::max(lbl->get_width(), 50);

    auto remove_lbl_btn = UI_crt_btn(
        UI_crt_rec(10, delta_button_y_pos, button_width, 20, 0x00000000, UI_distance_units::pixels),
        nullptr
    );

    int btn_id = remove_lbl_btn->get_ID(); 
    int lbl_id = lbl->get_ID(); 

    remove_lbl_btn->set_callback([btn_id, lbl_id, lbl](){ 
        UI_reposition_text(lbl->get_y_pos());
        UI_console_scr->remove_UI_component({lbl_id, btn_id}); 
    });
    remove_lbl_btn->set_states(UI_crt_rec(10, delta_button_y_pos, button_width, 20, 0x006B6B6B, UI_distance_units::pixels), nullptr);

    UI_console_scr->add_UI_components({remove_lbl_btn, lbl});

    if (remove_lbl_btn->get_y_pos() + remove_lbl_btn->get_height() + UI_console_scr->get_component_delta_pos() > UI_console_scr_border_bottom->get_y_pos() + UI_console_scr->get_component_delta_pos()) {
        UI_console_scr->set_height(UI_console_scr->get_height() + screen_increase_factor);
        UI_console_scr_border_sides->set_height(UI_console_scr_border_sides->get_height() + screen_increase_factor);
        UI_console_scr_border_bottom->set_y_pos(UI_console_scr_border_bottom->get_y_pos() + screen_increase_factor);
    }

    text_start_pos_y += 20;
}
