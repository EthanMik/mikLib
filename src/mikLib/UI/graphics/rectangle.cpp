#include "vex.h"

using namespace mik;

rectangle::rectangle(float x, float y, float w, float h, uint32_t fill_color, uint32_t outline_color, UI_distance_units units) :
    pen_width(1),
    fill_color(fill_color),
    outline_color(outline_color),
    fill_color_hex(""),
    outline_color_hex("")
{
    this->x = to_pixels(x, units);
    this->y = to_pixels(y, units);
    this->w = to_pixels(w, units);
    this->h = to_pixels(h, units);

    using_hex = false;
};

rectangle::rectangle(float x, float y, float w, float h, const std::string& fill_color, const std::string& outline_color, int pen_width, UI_distance_units units) :
    pen_width(pen_width),
    fill_color_hex(fill_color),
    outline_color_hex(outline_color)
{
    this->x = to_pixels(x, units);
    this->y = to_pixels(y, units);
    this->w = to_pixels(w, units);
    this->h = to_pixels(h, units);

    using_hex = true;
};

rectangle::rectangle(float x, float y, float w, float h, uint32_t hue, UI_distance_units units) : 
    pen_width(1),
    fill_color(hue),
    outline_color(hue),
    fill_color_hex(""),
    outline_color_hex("")
{
    this->x = to_pixels(x, units);
    this->y = to_pixels(y, units);
    this->w = to_pixels(w, units);
    this->h = to_pixels(h, units);

    using_hex = false;
};

rectangle::rectangle(float x, float y, float w, float h, const std::string& hue, UI_distance_units units) : 
    pen_width(1),
    fill_color_hex(hue),
    outline_color_hex(hue)
{
    this->x = to_pixels(x, units);
    this->y = to_pixels(y, units);
    this->w = to_pixels(w, units);
    this->h = to_pixels(h, units);

    using_hex = true;
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
    Brain.Screen.setPenWidth(pen_width);
    if (using_hex) {
        Brain.Screen.setFillColor(fill_color_hex.c_str());
        Brain.Screen.setPenColor(outline_color_hex.c_str());
    } else {
        Brain.Screen.setFillColor(fill_color);
        Brain.Screen.setPenColor(outline_color);
    }
    Brain.Screen.drawRectangle(x, y, w, h);

    Brain.Screen.setPenColor(vex::color::white);
    Brain.Screen.setPenWidth(0);
}
