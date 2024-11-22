#pragma once

#include "vex.h"

class button : public UI_component 
{
public:
    template<typename T1, typename T2>
    button(const std::string& button_file_name, const std::string& pressed_button_file_name, int x, int y, int w, int h, distance_units units, std::function<void(T1, T2)> func, T1 data1, T2 data2);

    template<typename T>
    button(const std::string& button_file_name, const std::string& pressed_button_file_name, int x, int y, int w, int h, distance_units units, std::function<void(T)> func, T data);

    button(const std::string& button_file_name, const std::string& pressed_button_file_name, int x, int y, int w, int h, distance_units units, std::function<void()> on_click);

    void render() override;

    int get_x_pos() override;
    int get_y_pos() override;
    int get_w_pos() override;
    int get_h_pos() override;

    void set_x_pos(int x) override;
    void set_y_pos(int y) override;

    void is_pressing() override;

private:
    std::string button_file_name;
    std::string pressed_button_file_name;
    int x;
    int y;
    int w;
    int h;
    distance_units units;
    std::function<void()> on_click;
    bool pressed = false;
};

template<typename T1, typename T2>
button::button(const std::string& button_file_name, const std::string& pressed_button_file_name, int x, int y, int w, int h, distance_units units, std::function<void(T1, T2)> func, T1 data1, T2 data2) :
    button_file_name(button_file_name),
    pressed_button_file_name(pressed_button_file_name),
    x(x),
    y(y),
    w(w),
    h(h),
    units(units),
    on_click([=]() { func(data1, data2); })
{    
    this->x = to_pixels(x, units);
    this->y = to_pixels(y, units);
    this->w = to_pixels(w, units);
    this->h = to_pixels(h, units);
};

template<typename T>
button::button(const std::string& button_file_name, const std::string& pressed_button_file_name, int x, int y, int w, int h, distance_units units, std::function<void(T)> func, T data) :
    button_file_name(button_file_name),
    pressed_button_file_name(pressed_button_file_name),
    x(x),
    y(y),
    w(w),
    h(h),
    units(units),
    on_click([=]() { func(data); })
{
    this->x = to_pixels(x, units);
    this->y = to_pixels(y, units);
    this->w = to_pixels(w, units);
    this->h = to_pixels(h, units);
};
