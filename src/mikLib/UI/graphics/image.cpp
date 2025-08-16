#include "vex.h"

using namespace mik;

image::image(const std::string& file_name, float x, float y, float w, float h, UI_distance_units units) :
    file_name(file_name), units(units)
{
    this->x = to_pixels(x, units);
    this->y = to_pixels(y, units);
    this->w = to_pixels(w, units);
    this->h = to_pixels(h, units);

    using_SD = true;

    if (!Brain.SDcard.exists(file_name.c_str()) && file_name != "") {  
        no_image_found = true;
        static std::mt19937 gen(
        static_cast<std::uint32_t>(std::random_device{}()) ^
        static_cast<std::uint32_t>(std::chrono::high_resolution_clock::now().time_since_epoch().count()));
        uint32_t color = std::uniform_int_distribution<uint32_t>{0, 0x7FFFFFFF}(gen);
        image_no_texture = UI_crt_rec(x, y, w, h, color, units);
    }
};

image::image(uint8_t* img_binary, float x, float y, float w, float h, UI_distance_units units) :
    file_name(""), img_binary(img_binary), units(units)
{
    this->x = to_pixels(x, units);
    this->y = to_pixels(y, units);
    this->w = to_pixels(w, units);
    this->h = to_pixels(h, units);
    
    using_SD = false;
}

int image::get_x_pos() { return(x); }
int image::get_y_pos() { return(y); }
int image::get_width() { return(w); }
int image::get_height() { return(h); }
void image::set_x_pos(int x) { 
    this->x = x;
    if (no_image_found) {
        image_no_texture->set_x_pos(x);
    }
}
void image::set_y_pos(int y) {
    this->y = y; 
    if (no_image_found) {
        image_no_texture->set_y_pos(y);
    }
}
void image::set_position(int x, int y) { 
    this->x = x; 
    this->y = y; 
    if (no_image_found) {
        image_no_texture->set_position(x, y);
    }
}
void image::set_width(int w) { 
    this->w = w;
    if (no_image_found) {
        image_no_texture->set_width(w);
    }
}
void image::set_height(int h) { 
    this->h = h;
    if (no_image_found) {
        image_no_texture->set_height(h);
    }
}

void image::render() {
    if (no_image_found) {
        image_no_texture->render();
        return;
    }
    if (using_SD) {
        Brain.Screen.drawImageFromFile(file_name.c_str(), x, y);
        return;
    }
    Brain.Screen.drawImageFromBuffer(img_binary, x, y, w * h);

}
