#include "vex.h"

float to_pixels(float distance, UI_distance_units units) {
    switch(units) {
      case UI_distance_units::inches:
          return(96 * distance);
      case UI_distance_units::centimeters: 
          return(37.79527559 * distance);
      case UI_distance_units::pixels:
          return(1 * distance);
  }
}

void UI_img_exists(std::string file_name) {
    if (!Brain.SDcard.isInserted()) {
        Brain.Screen.printAt(30, 30, "SD CARD NOT INSERTED DUMMY");
    }
    if (!Brain.SDcard.exists(file_name.c_str())) {
        Brain.Screen.printAt(30, 30, (file_name + " IMG DOES NOT EXIST").c_str());
    }
}

std::shared_ptr<drawable> UI_crt_img(const std::string& file_name, int x, int y, int w, int h, UI_distance_units units) {
    return std::make_shared<image>(file_name, x, y, w, h, units);
}


std::shared_ptr<drawable> UI_crt_rec(int x, int y, int w, int h, uint32_t fill_color, uint32_t outline_color, UI_distance_units units) {
    return std::make_shared<rectangle>(x, y, w, h, fill_color, outline_color, units);
}

std::shared_ptr<drawable> UI_crt_rec(int x, int y, int w, int h, vex::color fill_color, vex::color outline_color, UI_distance_units units) {
    return std::make_shared<rectangle>(x, y, w, h, fill_color, outline_color, units);
}

std::shared_ptr<drawable> UI_crt_rec(int x, int y, int w, int h, uint32_t hue, UI_distance_units units) {
    return std::make_shared<rectangle>(x, y, w, h, hue, units);
}

std::shared_ptr<drawable> UI_crt_rec(int x, int y, int w, int h, vex::color hue, UI_distance_units units) {
    return std::make_shared<rectangle>(x, y, w, h, hue, units);
}


std::shared_ptr<UI_component> UI_crt_tgl(std::shared_ptr<drawable> toggle_graphic, std::shared_ptr<drawable> pressed_toggle_graphic, std::function<void()> callback, int id) {
    return std::make_shared<toggle>(toggle_graphic, pressed_toggle_graphic, callback, id);
}

std::shared_ptr<UI_component> UI_crt_tgl(std::shared_ptr<drawable> toggle_graphic, std::shared_ptr<drawable> pressed_toggle_graphic, std::function<void()> callback) {
    return std::make_shared<toggle>(toggle_graphic, pressed_toggle_graphic, callback);
}

std::shared_ptr<UI_component> UI_crt_tgl(std::shared_ptr<drawable> toggle_graphic, std::shared_ptr<drawable> pressed_toggle_graphic) {
    return std::make_shared<toggle>(toggle_graphic, pressed_toggle_graphic);
}

std::shared_ptr<UI_component> UI_crt_btn(std::shared_ptr<drawable> button_graphic, std::shared_ptr<drawable> pressed_button_graphic, std::function<void()> on_click) {
    return std::make_shared<button>(button_graphic, pressed_button_graphic, on_click);
}


std::shared_ptr<UI_component> UI_crt_lbl(const std::string& label_text, int x, int y, UI_distance_units units) {
    return std::make_shared<label>(label_text, x, y, units);
}


std::shared_ptr<UI_component> UI_crt_gfx(std::shared_ptr<drawable> graphic_) {
    return std::make_shared<graphic>(graphic_);
}

std::shared_ptr<UI_component> UI_crt_gfx(std::vector<std::shared_ptr<drawable>> graphics) {
    return std::make_shared<graphic>(graphics);
}


std::shared_ptr<UI_component> UI_crt_bg(std::shared_ptr<drawable> graphic) {
    return std::make_shared<background>(graphic);
}


std::shared_ptr<screen> UI_crt_scr(int x, int y, int w, int h) {
    return std::make_shared<screen>(x, y, w, h);
}

