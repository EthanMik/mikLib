#include "vex.h"

static std::pair<int, int> cursor_position;

int UI_get_cursor_x_position() { return(cursor_position.first); }
int UI_get_cursor_y_position() { return(cursor_position.second); }

static int UI_id = 0;

int UI_create_ID(int component_type, int toggle_group) {
    // Assume component_type and toggle_group are in [0..99]
    // We allocate two digits for component_type, two digits for toggle_group,
    // and then UI_id is appended at the end.
    // Format: CC TT U...
    // Example: component_type=1, toggle_group=1, UI_id=13 -> 1 * 10000 + 1 * 100 + 13 = 10113
    
    if (component_type < 0 || component_type > 99 ||
        toggle_group < 0 || toggle_group > 99) {
            Brain.Screen.printAt(30, 30, "0-99 MAX");
            exit(1);
    }

    int id = component_type * 10000 + toggle_group * 100 + ++UI_id;
    return id;
}

int UI_decode_component_type(int id) {
    return(id / 10000);
}

int UI_decode_toggle_group(int id) {
    return((id % 10000) / 100);
}

int UI_decode_unique_id(int id) {
    return ((id % 10000) % 100);
}

std::shared_ptr<UI_component> UI_to_component(std::shared_ptr<UI_component> component) {
    int id = UI_decode_component_type(component->get_ID());
    switch (id)
    {
    case 1:
        return std::static_pointer_cast<graphic>(component);
    case 2:
        return std::static_pointer_cast<background>(component);
    case 3:
        return std::static_pointer_cast<label>(component);
    case 4:
        return std::static_pointer_cast<button>(component);
    case 5:
        return std::static_pointer_cast<toggle>(component);
    case 6:
        return std::static_pointer_cast<textbox>(component);
    default:
        return nullptr;
    }
}

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

void UI_img_exists(const std::string& file_name) {
    if (!Brain.SDcard.isInserted()) {
        Brain.Screen.printAt(30, 30, "SD CARD NOT INSERTED DUMMY");
    }
    else if (!Brain.SDcard.exists(file_name.c_str())) {
        Brain.Screen.printAt(30, 30, (file_name + " IMG DOES NOT EXIST").c_str());
    } else {
        Brain.Screen.printAt(30, 30, "EXISTS");
    }
    Brain.Screen.render();

    exit(1);
}

std::shared_ptr<drawable> UI_crt_img(const std::string& file_name, int x, int y, int w, int h, UI_distance_units units) {
    return std::make_shared<image>(file_name, x, y, w, h, units);
}

std::shared_ptr<drawable> UI_crt_px(int x, int y, uint32_t hue, UI_distance_units units) {
    return std::make_shared<pixel>(x, y, hue, units);
}

std::shared_ptr<drawable> UI_crt_ln(int x, int y, int w, int h, uint32_t hue, UI_distance_units units) {
    return std::make_shared<line>(x, y, w, h, hue, units);
}

std::shared_ptr<drawable> UI_crt_txt(const std::string& text_label, int x, int y, UI_distance_units units) {
    return std::make_shared<text>(text_label, x, y, units);
}
std::shared_ptr<drawable> UI_crt_txt(const std::string& text_label, int x, int y, uint32_t hue, UI_distance_units units) {
    return std::make_shared<text>(text_label, x, y, hue, units);
}
std::shared_ptr<drawable> UI_crt_txt(const std::string& text_label, int x, int y, vex::color hue, UI_distance_units units) {
    return std::make_shared<text>(text_label, x, y, hue, units);
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

std::shared_ptr<UI_component> UI_crt_txtbox(std::string text, std::shared_ptr<drawable> box) {
    return std::make_shared<textbox>(text, box);
}

std::shared_ptr<UI_component> UI_crt_tgl(std::shared_ptr<drawable> toggle_graphic, std::function<void()> callback, int id) {
    return std::make_shared<toggle>(toggle_graphic, callback, id);
}

std::shared_ptr<UI_component> UI_crt_tgl(std::shared_ptr<drawable> toggle_graphic, std::function<void()> callback) {
    return std::make_shared<toggle>(toggle_graphic, callback);
}

std::shared_ptr<UI_component> UI_crt_tgl(std::shared_ptr<drawable> toggle_graphic) {
    return std::make_shared<toggle>(toggle_graphic);
}

std::shared_ptr<UI_component> UI_crt_btn(std::shared_ptr<drawable> button_graphic, std::function<void()> on_click) {
    return std::make_shared<button>(button_graphic, on_click);
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

