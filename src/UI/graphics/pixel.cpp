#include "vex.h"

using namespace mik;

pixel::pixel(float x, float y, uint32_t hue, UI_distance_units units) :
    hue(hue)
{
    this->x = to_pixels(x, units);
    this->y = to_pixels(y, units);
}

int pixel::get_x_pos() { return(x); }
int pixel::get_y_pos() { return(y); }
int pixel::get_width() { return(1); }
int pixel::get_height() { return(1); }
void pixel::set_x_pos(int x) { this->x = x; }
void pixel::set_y_pos(int y) { this->y = y; }
void pixel::set_position(int x, int y) { this->x = x; this->y = y; }
void pixel::set_width(int w) {}
void pixel::set_height(int h) {}

void pixel::render() {
    Brain.Screen.setFillColor(hue);
    Brain.Screen.drawRectangle(x, y, 1, 1);
    Brain.Screen.setFillColor(vex::color::white);
}
