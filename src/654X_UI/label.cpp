#include "vex.h"

label::label(const std::string& label, int x, int y, UI_distance_units units):
    label_text(label), x(x), y(y), units(units), data_func([](){ return ""; } )
{
    unique_id = UI_create_ID(UI_Label_ID);

    this->x = to_pixels(x, units);
    this->y = to_pixels(y, units);
    this->w = Brain.Screen.getStringWidth(label_text.c_str());
    this->h = Brain.Screen.getStringHeight(label_text.c_str());

    last_update_time = Brain.Timer.time(vex::timeUnits::msec);
};

int label::get_x_pos() { return(x); }
int label::get_y_pos() { return(y); }
int label::get_width() { return(Brain.Screen.getStringWidth((label_text + data_func()).c_str())); }
int label::get_height() { return(Brain.Screen.getStringHeight((label_text + data_func()).c_str())); }
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

    if (current_time - last_update_time >= update_interval_ms) {
        const std::string data = data_func();

        if (data != prev_data) {
            needs_render_update = true;
            prev_data = data;
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
    Brain.Screen.setPenColor(vex::color::white);
    Brain.Screen.setFillColor(vex::color::black);

    Brain.Screen.printAt(x, y, (label_text + data_func()).c_str());
}


