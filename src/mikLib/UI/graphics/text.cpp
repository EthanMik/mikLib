#include "vex.h"

using namespace mik;

text::text(const std::string& text_label, float x, float y, UI_distance_units units) :
    text_label(text_label), text_color(ClrWhite), bg_color(ClrBlack), text_color_hex(""), bg_color_hex(""), units(units)
{
    this->x = to_pixels(x, units);
    this->y = to_pixels(y, units);
    this->w = Brain.Screen.getStringWidth(text_label.c_str());
    this->h = Brain.Screen.getStringHeight(text_label.c_str());
    using_hex = false;
};

text::text(const std::string& text_label, float x, float y, uint32_t bg_color, UI_distance_units units) :
    text_label(text_label), text_color(ClrWhite), bg_color(bg_color), text_color_hex(""), bg_color_hex(""), units(units)
{
    this->x = to_pixels(x, units);
    this->y = to_pixels(y, units);
    this->w = Brain.Screen.getStringWidth(text_label.c_str());
    this->h = Brain.Screen.getStringHeight(text_label.c_str());
    using_hex = false;
};

text::text(const std::string& text_label, float x, float y, uint32_t text_color, uint32_t bg_color, UI_distance_units units) :
    text_label(text_label), text_color(text_color), bg_color(bg_color), text_color_hex(""), bg_color_hex(""), units(units)
{
    this->x = to_pixels(x, units);
    this->y = to_pixels(y, units);
    this->w = Brain.Screen.getStringWidth(text_label.c_str());
    this->h = Brain.Screen.getStringHeight(text_label.c_str());
    using_hex = false;
};


text::text(const std::string& text_label, float x, float y, const std::string& bg_color, UI_distance_units units) :
    text_label(text_label), text_color(ClrWhite), bg_color(ClrBlack), text_color_hex("#FFFFFF"), bg_color_hex(bg_color), units(units)
{
    this->x = to_pixels(x, units);
    this->y = to_pixels(y, units);
    this->w = Brain.Screen.getStringWidth(text_label.c_str());
    this->h = Brain.Screen.getStringHeight(text_label.c_str());
    using_hex = true;
}

text::text(const std::string& text_label, float x, float y, const std::string& text_color, const std::string& bg_color, UI_distance_units units) :
    text_label(text_label), text_color(ClrWhite), bg_color(ClrBlack), text_color_hex(text_color), bg_color_hex(bg_color), units(units)
{
    this->x = to_pixels(x, units);
    this->y = to_pixels(y, units);
    this->w = Brain.Screen.getStringWidth(text_label.c_str());
    this->h = Brain.Screen.getStringHeight(text_label.c_str());  
    using_hex = true;
}

int text::get_x_pos() { return(x); }
int text::get_y_pos() { return(y); }
int text::get_width() { return(Brain.Screen.getStringWidth(text_label.c_str())); }
int text::get_height() { return(h); }
std::string text::get_text() { return(text_label); }

void text::set_x_pos(int x) { this->x = x; }
void text::set_y_pos(int y) { this->y = y; }
void text::set_position(int x, int y) { this->x = x; this->y = y; }
void text::set_width(int w) { this->w = w; }
void text::set_height(int h) { this->h = h; }
void text::set_text(std::string text_label) { this->text_label = text_label; }

void text::render() {
    if (using_hex) {
        Brain.Screen.setFillColor(bg_color_hex.c_str());
        Brain.Screen.setPenColor(text_color_hex.c_str());
    } else {
        Brain.Screen.setFillColor(bg_color);
        Brain.Screen.setPenColor(text_color);
    }
    Brain.Screen.printAt(x, y, text_label.c_str());
}
