#include "vex.h"

line::line(int x, int y, int w, int h, uint32_t hue, UI_distance_units units) :
    x(x), y(y), w(w), h(h), hue(hue)
{
    this->x = to_pixels(x, units);
    this->y = to_pixels(y, units);
    this->w = to_pixels(w, units);
    this->h = to_pixels(h, units);
}

int line::get_x_pos() { return(x); }
int line::get_y_pos() { return(y); }
int line::get_width() { return(w); }
int line::get_height() { return(h); }
void line::set_x_pos(int x) { this->x = x; }
void line::set_y_pos(int y) { this->y = y; }
void line::set_position(int x, int y) { this->x = x; this->y = y; }
void line::set_width(int w) { this->w = w; }
void line::set_height(int h) { this->h = h; }

void line::render() {
    Brain.Screen.setPenColor(hue);
    Brain.Screen.setPenWidth(1);
    Brain.Screen.drawLine(x, y, w, h);
    Brain.Screen.setFillColor(vex::color::white);
}
