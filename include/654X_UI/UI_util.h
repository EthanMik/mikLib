#pragma once

#include "vex.h"

class screen;
class label;

int UI_get_cursor_x_position();
int UI_get_cursor_y_position();

int UI_create_ID(int component_type, int toggle_group = 0);

int UI_decode_component_type(int id);
int UI_decode_toggle_group(int id);
int UI_decode_unique_id(int id);

std::shared_ptr<UI_component> UI_to_component(std::shared_ptr<UI_component> component);

float to_pixels(float distance, UI_distance_units units);

std::shared_ptr<drawable> UI_crt_img(const std::string& file_name, float x, float y, float w, float h, UI_distance_units units);

std::shared_ptr<drawable> UI_crt_px(float x, float y, uint32_t hue, UI_distance_units units);

std::shared_ptr<drawable> UI_crt_ln(float x1, float y1, float x2, float y2, uint32_t hue, UI_distance_units units);

std::shared_ptr<drawable> UI_crt_px(float x, float y, uint32_t hue, UI_distance_units units);

std::shared_ptr<drawable> UI_crt_txt(const std::string& text_label, float x, float y, UI_distance_units units);
std::shared_ptr<drawable> UI_crt_txt(const std::string& text_label, float x, float y, uint32_t hue, UI_distance_units units);
std::shared_ptr<drawable> UI_crt_txt(const std::string& text_label, float x, float y, vex::color hue, UI_distance_units units);
    
std::shared_ptr<drawable> UI_crt_rec(float x, float y, float w, float h, uint32_t fill_color, uint32_t outline_color, UI_distance_units units);
std::shared_ptr<drawable> UI_crt_rec(float x, float y, float w, float h, vex::color fill_color, vex::color outline_color, UI_distance_units units);
std::shared_ptr<drawable> UI_crt_rec(float x, float y, float w, float h, uint32_t hue, UI_distance_units units);
std::shared_ptr<drawable> UI_crt_rec(float x, float y, float w, float h, vex::color hue, UI_distance_units units);

std::shared_ptr<drawable> UI_crt_grp(std::shared_ptr<drawable> graphic_);
std::shared_ptr<drawable> UI_crt_grp(std::vector<std::shared_ptr<drawable>> graphics);

std::shared_ptr<UI_component> UI_crt_tgl(std::shared_ptr<drawable> toggle_graphic, std::function<void()> callback, int id);
std::shared_ptr<UI_component> UI_crt_tgl(std::shared_ptr<drawable> toggle_graphic, std::function<void()> callback);
std::shared_ptr<UI_component> UI_crt_tgl(std::shared_ptr<drawable> toggle_graphic);

std::shared_ptr<UI_component> UI_crt_txtbox(std::string text, std::shared_ptr<drawable> box);
std::shared_ptr<UI_component> UI_crt_txtbox(std::string text, text_align text_alignment, std::shared_ptr<drawable> box);
std::shared_ptr<UI_component> UI_crt_txtbox(std::string text, uint32_t text_color, std::shared_ptr<drawable> box);
std::shared_ptr<UI_component> UI_crt_txtbox(std::string text, uint32_t text_color, text_align text_alignment, std::shared_ptr<drawable> box);

std::shared_ptr<UI_component> UI_crt_btn(std::shared_ptr<drawable> button_graphic, std::function<void()> on_click);

std::shared_ptr<UI_component> UI_crt_lbl(const std::string& label_text, float x, float y, UI_distance_units units);
template <typename T>
std::shared_ptr<UI_component> UI_crt_lbl(const std::string& label_text, T& data, float x, float y, UI_distance_units units);
template <typename F>
std::shared_ptr<UI_component> UI_crt_lbl(const std::string& label_text, F&& data_func, float x, float y, UI_distance_units units);

template <typename T>
std::shared_ptr<UI_component> UI_crt_lbl(const std::string& label_text, T& data, float x, float y, UI_distance_units units) {
    return std::make_shared<label>(label_text, data, x, y, units);
}

template <typename F>
std::shared_ptr<UI_component> UI_crt_lbl(const std::string& label_text, F&& data_func, float x, float y, UI_distance_units units) {
    return std::make_shared<label>(label_text, std::forward<F>(data_func), x, y, units);
}

std::shared_ptr<UI_component> UI_crt_gfx(std::shared_ptr<drawable> graphic_);
std::shared_ptr<UI_component> UI_crt_gfx(std::vector<std::shared_ptr<drawable>> graphics);

std::shared_ptr<UI_component> UI_crt_bg(std::shared_ptr<drawable> graphic);

std::shared_ptr<screen> UI_crt_scr(int x, int y, int w, int h);
