#include "vex.h"

toggle::toggle(const std::string& toggle_file_name, const std::string& toggled_file_name, int x, int y, int w, int h, distance_units units) :
    toggle_file_name(toggle_file_name),
    toggled_file_name(toggled_file_name),
    x(x),
    y(y),
    w(x),
    h(h),
    units(units)
{
    this->x = to_pixels(x, units);
    this->y = to_pixels(y, units);
    this->w = to_pixels(w, units);
    this->h = to_pixels(h, units);
};

toggle::toggle(const std::string& toggle_file_name, const std::string& toggled_file_name, int x, int y, int w, int h, distance_units units, std::function<void()> callback) :
    toggle_file_name(toggle_file_name),
    toggled_file_name(toggled_file_name),
    x(x),
    y(y),
    w(x),
    h(h),
    units(units),
    callback(callback)
{
    this->x = to_pixels(x, units);
    this->y = to_pixels(y, units);
    this->w = to_pixels(w, units);
    this->h = to_pixels(h, units);
};

toggle::toggle(const std::string& toggle_file_name, const std::string& toggled_file_name, int x, int y, int w, int h, distance_units units, std::function<void()> callback, int id) :
    toggle_file_name(toggle_file_name),
    toggled_file_name(toggled_file_name),
    x(x),
    y(y),
    w(x),
    h(h),
    units(units),
    callback(callback),
    id(id)
{
    this->x = to_pixels(x, units);
    this->y = to_pixels(y, units);
    this->w = to_pixels(w, units);
    this->h = to_pixels(h, units);
};

int toggle::get_y_pos() { return(y); }
int toggle::get_x_pos() { return(x); }
int toggle::get_h_pos() { return(h); }
int toggle::get_w_pos() { return(w); }
void toggle::set_x_pos(int x) { this->x = x; }
void toggle::set_y_pos(int y) { this->y = y; }

void toggle::render() {
    if (is_toggled) {
        Brain.Screen.drawImageFromFile(toggled_file_name.c_str(), x, y);
    }
    else {
        Brain.Screen.drawImageFromFile(toggle_file_name.c_str(), x, y);
    }
}

void toggle::execute() {
    if (callback && is_toggled) {
        callback();
    }
}

bool toggle::get_toggle_state() {
    return(is_toggled);
}

int toggle::get_toggle_id() {
    return(id);
}
