#pragma once

#include "vex.h"

class screen;
class label;

int UI_create_ID(int component_type, int toggle_group = 0);

int UI_decode_component_type(int id);
int UI_decode_toggle_group(int id);
int UI_decode_unique_id(int id);

float to_pixels(float distance, UI_distance_units units);

void UI_img_exists(std::string file_name);

std::shared_ptr<drawable> UI_crt_img(const std::string& file_name, int x, int y, int w, int h, UI_distance_units units);

std::shared_ptr<drawable> UI_crt_txt(const std::string& text_label, int x, int y, UI_distance_units units);

std::shared_ptr<drawable> UI_crt_rec(int x, int y, int w, int h, uint32_t fill_color, uint32_t outline_color, UI_distance_units units);
std::shared_ptr<drawable> UI_crt_rec(int x, int y, int w, int h, vex::color fill_color, vex::color outline_color, UI_distance_units units);
std::shared_ptr<drawable> UI_crt_rec(int x, int y, int w, int h, uint32_t hue, UI_distance_units units);
std::shared_ptr<drawable> UI_crt_rec(int x, int y, int w, int h, vex::color hue, UI_distance_units units);

std::shared_ptr<UI_component> UI_crt_tgl(std::shared_ptr<drawable> toggle_graphic, std::function<void()> callback, int id);
std::shared_ptr<UI_component> UI_crt_tgl(std::shared_ptr<drawable> toggle_graphic, std::function<void()> callback);
std::shared_ptr<UI_component> UI_crt_tgl(std::shared_ptr<drawable> toggle_graphic);

std::shared_ptr<UI_component> UI_crt_btn(std::shared_ptr<drawable> button_graphic, std::function<void()> on_click);

std::shared_ptr<UI_component> UI_crt_lbl(const std::string& label_text, int x, int y, UI_distance_units units);
template <typename T>
std::shared_ptr<UI_component> UI_crt_lbl(const std::string& label_text, T& data, int x, int y, UI_distance_units units);
template <typename F>
std::shared_ptr<UI_component> UI_crt_lbl(const std::string& label_text, F&& data_func, int x, int y, UI_distance_units units);

template <typename T>
std::shared_ptr<UI_component> UI_crt_lbl(const std::string& label_text, T& data, int x, int y, UI_distance_units units) {
    return std::make_shared<label>(label_text, data, x, y, units);
}

template <typename F>
std::shared_ptr<UI_component> UI_crt_lbl(const std::string& label_text, F&& data_func, int x, int y, UI_distance_units units) {
    return std::make_shared<label>(label_text, std::forward<F>(data_func), x, y, units);
}


std::shared_ptr<UI_component> UI_crt_gfx(std::shared_ptr<drawable> graphic_);
std::shared_ptr<UI_component> UI_crt_gfx(std::vector<std::shared_ptr<drawable>> graphics);

std::shared_ptr<UI_component> UI_crt_bg(std::shared_ptr<drawable> graphic);

std::shared_ptr<screen> UI_crt_scr(int x, int y, int w, int h);
