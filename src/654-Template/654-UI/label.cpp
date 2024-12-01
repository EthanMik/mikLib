#include "vex.h"

label::label(const std::string& label, int x, int y, UI_distance_units units):
    label_text(label), x(x), y(y), units(units), data_func([](){ return ""; } )
{
    this->x = to_pixels(x, units);
    this->y = to_pixels(y, units);
    this->w = Brain.Screen.getStringWidth(label_text.c_str());
    this->h = Brain.Screen.getStringHeight(label_text.c_str());
};

int label::get_x_pos() { return(x); }
int label::get_y_pos() { return(y); }
int label::get_width() { return(Brain.Screen.getStringWidth((label_text + data_func()).c_str())); }
int label::get_height() { return(Brain.Screen.getStringHeight((label_text + data_func()).c_str())); }
void label::set_x_pos(int x) { this->x = x; }
void label::set_y_pos(int y) { this->y = y; }
void label::set_position(int x, int y) { this->x = x; this->y = y; }

void label::render() {
    Brain.Screen.setPenColor(vex::color::white);
    Brain.Screen.setFillColor(vex::color::black);

    Brain.Screen.printAt(x, y, (label_text + data_func()).c_str());
}


