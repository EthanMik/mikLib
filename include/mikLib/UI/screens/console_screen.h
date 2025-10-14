#pragma once

#include "vex.h"

namespace mik {

class UI_console_screen
{
public:
    UI_console_screen();
 
    std::shared_ptr<screen> get_console_screen();
    void reset();

    void add(const std::string& label_text, bool txt);

    template <typename F>
    void add(const std::string& label_text, F&& data);

    template <typename F>
    void add(F&& data);

    template <typename T>
    void add(const std::string& label_text, T& data);

    template <typename T>
    void add(T& data);

    std::shared_ptr<screen> UI_console_scr;

private:
    void UI_crt_console_scr();

    void UI_reposition_text(int position);

    template <typename data_type>
    void add_impl(const std::string& label_text, data_type&& data);

    std::shared_ptr<UI_component> UI_console_scr_border_sides = nullptr;
    std::shared_ptr<UI_component> UI_console_scr_border_bottom = nullptr;

    int text_start_pos_x = 10;
    int text_start_pos_y = -18; 
};

template <typename F>
void UI_console_screen::add(const std::string& label_text, F&& data) {
    add_impl(label_text, std::forward<F>(data));
}

template <typename F>
void UI_console_screen::add(F&& data) {
    add_impl("", std::forward<F>(data));
}

template <typename T>
void UI_console_screen::add(const std::string& label_text, T& data) {
    add_impl(label_text, data);
}

template <typename T>
void UI_console_screen::add(T& data) {
    add_impl("", data);
}


template <typename data_type>
void UI_console_screen::add_impl(const std::string& label_text, data_type&& data) {
    int delta_label_y_pos = text_start_pos_y + this->UI_console_scr->get_component_delta_pos() + this->UI_console_scr->get_y_pos();
    int delta_button_y_pos = text_start_pos_y + this->UI_console_scr->get_component_delta_pos() + this->UI_console_scr->get_y_pos() - 15;
    int screen_increase_factor = 20;

    auto lbl = UI_crt_lbl(label_text, std::forward<data_type>(data), text_start_pos_x, delta_label_y_pos, console_text_color, console_bg_color, UI_distance_units::pixels);

    int button_width = std::max(lbl->get_width(), 50);

    auto remove_lbl_btn = UI_crt_btn(
        UI_crt_rec(10, delta_button_y_pos, button_width, 20, console_bg_color, UI_distance_units::pixels),
        nullptr
    );

    int btn_id = remove_lbl_btn->get_ID(); 
    int lbl_id = lbl->get_ID(); 

    remove_lbl_btn->set_callback([this, btn_id, lbl_id, lbl](){ 
        UI_reposition_text(lbl->get_y_pos());
        this->UI_console_scr->remove_UI_component({lbl_id, btn_id});
        UI_console_scr->refresh(); 
    });
    remove_lbl_btn->set_states(UI_crt_rec(10, delta_button_y_pos, button_width, 20, console_text_bg_color, UI_distance_units::pixels), nullptr);

    this->UI_console_scr->add_UI_components({remove_lbl_btn, lbl});

    if (remove_lbl_btn->get_y_pos() + remove_lbl_btn->get_height() + this->UI_console_scr->get_component_delta_pos() > UI_console_scr_border_bottom->get_y_pos() + this->UI_console_scr->get_component_delta_pos()) {
        this->UI_console_scr->set_height(this->UI_console_scr->get_height() + screen_increase_factor);
        UI_console_scr_border_sides->set_height(UI_console_scr_border_sides->get_height() + screen_increase_factor);
        UI_console_scr_border_bottom->set_y_pos(UI_console_scr_border_bottom->get_y_pos() + screen_increase_factor);
    }

    text_start_pos_y += 20;    
}
}
