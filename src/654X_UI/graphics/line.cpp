#include "vex.h"

line::line(float x1, float y1, float x2, float y2, uint32_t hue, UI_distance_units units) :
    hue(hue)
{
    this->x = to_pixels(x1, units);
    this->y = to_pixels(y1, units);
    this->w = to_pixels(x2, units);
    this->h = to_pixels(y2, units);
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
