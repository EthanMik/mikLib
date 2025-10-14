#include "vex.h"

using namespace mik;

label::label(const std::string& label, float x, float y, const std::string& text_color, const std::string& bg_color, UI_distance_units units):
    label_text(label), text_color(text_color), bg_color(bg_color), units(units), data_func([](){ return ""; } )
{
    unique_id = UI_create_ID(UI_Label_ID);

    this->x = to_pixels(x, units);
    this->y = to_pixels(y, units);
    this->w = Brain.Screen.getStringWidth(label_text.c_str());
    this->h = Brain.Screen.getStringHeight(label_text.c_str());
    
    last_update_time = Brain.Timer.time(vex::timeUnits::msec);
    formatted_data = "";
};

int label::get_x_pos() { return(x); }
int label::get_y_pos() { return(y); }
int label::get_width() { return(Brain.Screen.getStringWidth((label_text + formatted_data).c_str())); }
int label::get_height() { return(Brain.Screen.getStringHeight((label_text + formatted_data).c_str())); }
void label::set_x_pos(int x) { 
    needs_render_update = true;
    this->x = x;
}
void label::set_y_pos(int y) { 
    needs_render_update = true;
    this->y = y;
}
void label::set_position(int x, int y) { this->x = x; this->y = y; }

bool label::needs_update() {
    int current_time = Brain.Timer.time(vex::timeUnits::msec);

    if (current_time - last_update_time >= 50) {
        formatted_data = data_func();

        if (formatted_data != prev_data) {
            needs_render_update = true;
            prev_data = formatted_data;
        }

        last_update_time = current_time;
    }

    if (needs_render_update) {
        needs_render_update = false;
        return true;
    }
    return false;
} 

void label::render() {
    Brain.Screen.setPenColor(text_color.c_str());
    Brain.Screen.setFillColor(bg_color.c_str());
    Brain.Screen.printAt(x, y, (label_text + formatted_data).c_str());
}


