#include "vex.h"

rectangle::rectangle(int x, int y, int w, int h, uint32_t fill_color, uint32_t outline_color, UI_distance_units units) :
    x(x), y(y), w(w), h(h),
    fill_color(fill_color),
    outline_color(outline_color)
{
    this->x = to_pixels(x, units);
    this->y = to_pixels(y, units);
    this->w = to_pixels(w, units);
    this->h = to_pixels(h, units);
};

rectangle::rectangle(int x, int y, int w, int h, vex::color fill_color, vex::color outline_color, UI_distance_units units) :
    x(x), y(y), w(w), h(h),
    fill_color(fill_color),
    outline_color(outline_color)
{
    this->x = to_pixels(x, units);
    this->y = to_pixels(y, units);
    this->w = to_pixels(w, units);
    this->h = to_pixels(h, units);
};

rectangle::rectangle(int x, int y, int w, int h, uint32_t hue, UI_distance_units units) : 
    x(x), y(y), w(w), h(h),
    fill_color(hue),
    outline_color(hue)
{
    this->x = to_pixels(x, units);
    this->y = to_pixels(y, units);
    this->w = to_pixels(w, units);
    this->h = to_pixels(h, units);
};

rectangle::rectangle(int x, int y, int w, int h, vex::color hue, UI_distance_units units) : 
    x(x), y(y), w(w), h(h),
    fill_color(hue),
    outline_color(hue)
{
    this->x = to_pixels(x, units);
    this->y = to_pixels(y, units);
    this->w = to_pixels(w, units);
    this->h = to_pixels(h, units);
};

int rectangle::get_x_pos() { return(x); }
int rectangle::get_y_pos() { return(y); }
int rectangle::get_width() { return(w); }
int rectangle::get_height() { return(h); }
void rectangle::set_x_pos(int x) { this->x = x; }
void rectangle::set_y_pos(int y) { this->y = y; }
void rectangle::set_position(int x, int y) { this->x = x; this->y = y; }
void rectangle::set_width(int w) { this->w = w; }
void rectangle::set_height(int h) {this->h = h; }

void rectangle::render() {
    Brain.Screen.setPenWidth(1);
    Brain.Screen.setFillColor(fill_color);
    Brain.Screen.setPenColor(outline_color);
    Brain.Screen.drawRectangle(x, y, w, h);

    Brain.Screen.setPenColor(vex::color::white);
    Brain.Screen.setPenWidth(0);
}
