#include "vex.h"

text::text(const std::string& text_label, int x, int y, UI_distance_units units) :
    text_label(text_label), x(x), y(y), hue(vex::color::black), units(units)
{
    this->w = Brain.Screen.getStringHeight(text_label.c_str());
    this->w = Brain.Screen.getStringWidth(text_label.c_str());
    
    this->x = to_pixels(x, units);
    this->y = to_pixels(y, units);
    this->w = to_pixels(w, units);
    this->h = to_pixels(h, units);
};

text::text(const std::string& text_label, int x, int y, uint32_t hue, UI_distance_units units) :
    text_label(text_label), x(x), y(y), hue(hue), units(units)
{
    this->w = Brain.Screen.getStringHeight(text_label.c_str());
    this->w = Brain.Screen.getStringWidth(text_label.c_str());
    
    this->x = to_pixels(x, units);
    this->y = to_pixels(y, units);
    this->w = to_pixels(w, units);
    this->h = to_pixels(h, units);
};

text::text(const std::string& text_label, int x, int y, vex::color hue, UI_distance_units units) :
    text_label(text_label), x(x), y(y), hue(hue), units(units)
{
    this->w = Brain.Screen.getStringHeight(text_label.c_str());
    this->w = Brain.Screen.getStringWidth(text_label.c_str());
    
    this->x = to_pixels(x, units);
    this->y = to_pixels(y, units);
    this->w = to_pixels(w, units);
    this->h = to_pixels(h, units);
};

int text::get_x_pos() { return(x); }
int text::get_y_pos() { return(y); }
int text::get_width() { return(w); }
int text::get_height() { return(h); }
std::string text::get_text() { return(text_label); }

void text::set_x_pos(int x) { this->x = x; }
void text::set_y_pos(int y) { this->y = y; }
void text::set_position(int x, int y) { this->x = x; this->y = y; }
void text::set_width(int w) { this->w = w; }
void text::set_height(int h) { this->h = h; }
void text::set_text(std::string text_label) { this->text_label = text_label; }

void text::render() {
    Brain.Screen.setFillColor(hue);
    Brain.Screen.printAt(x, y, text_label.c_str());
}
