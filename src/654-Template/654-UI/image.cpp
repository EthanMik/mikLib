#include "vex.h"

image::image(const char *file_name, int x, int y, int w, int h, distance_units units) :
    file_name(file_name),
    x(x),
    y(y),
    w(w),
    h(h),
    units(units)
{
    this->x = to_pixels(x, units);
    this->y = to_pixels(y, units);
    this->w = to_pixels(w, units);
    this->h = to_pixels(h, units);
};

int image::get_x_pos() { return(x); }
int image::get_y_pos() { return(y); }
int image::get_w_pos() { return(w); }
int image::get_h_pos() { return(h); }
void image::set_x_pos(int x) { /* this->x = x; */ }
void image::set_y_pos(int y) { /* this->y = y; */ }

void image::render() {
    Brain.Screen.drawImageFromFile(file_name.c_str(), x, y);
}

void image::draw() {
    Brain.Screen.drawImageFromFile(file_name.c_str(), x, y);
}