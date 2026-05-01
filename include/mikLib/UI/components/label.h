#pragma once

#include "mikLib/ui.h"

#ifndef FAST_COMPILE

namespace mik {

class label : public UI_component
{
public:
    label(const std::string& label, float x, float y, const std::string& text_color, const std::string& bg_color, UI_distance_units units);

    template<typename T>
    label(const std::string& label, T& data, float x, float y, const std::string& text_color, const std::string& bg_color, UI_distance_units units);
    
    template<typename F>
    label(const std::string& label, F&& data_func, float x, float y, const std::string& text_color, const std::string& bg_color, UI_distance_units units);

    int get_x_pos() override;
    int get_y_pos() override;
    int get_width() override;
    int get_height() override;

    void set_x_pos(int x) override;
    void set_y_pos(int y) override;
    void set_position(int x, int y) override;

    void set_text_color(const std::string& color);
    void set_fill_color(const std::string& color);

    bool needs_update() override;
    void render() override;

private:
    std::string label_text;
    std::string text_color;
    std::string bg_color;
    int x, y, w, h;
    UI_distance_units units;
    std::function<std::string()> data_func;
    
    std::string prev_data;
    std::string formatted_data;

    bool needs_render_update;

    int last_update_time = 0;
    const int update_interval_ms = 15;

};
}

template<typename T>
mik::label::label(const std::string& label, T& data, float x, float y, const std::string& text_color, const std::string& bg_color, UI_distance_units units):
    label_text(label),
    data_func([&data]() -> std::string {
        if constexpr (std::is_floating_point<T>::value) {
            return ::to_string_float(static_cast<float>(data), 5, false);
        } else {
            return ::to_string(data);
        }
    }),
    text_color(text_color),
    bg_color(bg_color),
    units(units)
{
    unique_id = UI_create_ID(UI_Label_ID);

    this->x = to_pixels(x, units);
    this->y = to_pixels(y, units);

    formatted_data = "";
};


template<typename F>
mik::label::label(const std::string& label, F&& data_func, float x, float y, const std::string& text_color, const std::string& bg_color, UI_distance_units units):
    label_text(label),
    data_func([data_func = std::forward<F>(data_func)]() -> std::string {
        auto value = data_func();
        if constexpr (std::is_floating_point<decltype(value)>::value) {
            return ::to_string_float(static_cast<float>(value), 5, false);
        } else {
            return ::to_string(value);
        }
    }),
    text_color(text_color),
    bg_color(bg_color),
    units(units) 
{
    unique_id = UI_create_ID(UI_Label_ID);

    this->x = to_pixels(x, units);
    this->y = to_pixels(y, units);

    formatted_data = "";
};

#endif