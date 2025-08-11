#include "vex.h"

using namespace mik;

circle::circle(float x, float y, float w, float h, uint32_t fill_color, UI_distance_units units) :
    fill_color(fill_color), fill_color_hex("")
{
    this->x = to_pixels(x, units);
    this->y = to_pixels(y, units);
    this->r = w > h ? to_pixels(w * .5, units) : to_pixels(h * .5, units); 

    using_hex = false;
};

circle::circle(float x, float y, float w, float h, const std::string& fill_color_hex, UI_distance_units units) :
    fill_color(0), fill_color_hex(fill_color_hex)

{
    this->x = to_pixels(x, units);
    this->y = to_pixels(y, units);
    this->r = w > h ? to_pixels(w * .5, units) : to_pixels(h * .5, units); 

    using_hex = true;
};

int circle::get_x_pos() { return(x); }
int circle::get_y_pos() { return(y); }
int circle::get_width() { return(r * 2); }
int circle::get_height() { return(r * 2); }
void circle::set_x_pos(int x) { this->x = x; }
void circle::set_y_pos(int y) { this->y = y; }
void circle::set_position(int x, int y) { this->x = x; this->y = y; }
void circle::set_width(int w) { this->r = w * .5; }
void circle::set_height(int h) {this->r = h *.5; }

void circle::render() {
    Brain.Screen.setPenWidth(0);

    if (using_hex) {
        Brain.Screen.setFillColor(fill_color_hex.c_str());
    } else {
        Brain.Screen.setFillColor(fill_color);
    }

    Brain.Screen.drawCircle(x+r, y+r, r);

    Brain.Screen.setPenColor(vex::color::white);
}
