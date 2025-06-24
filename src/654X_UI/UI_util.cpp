#include "vex.h"

static std::pair<int, int> cursor_position;

int UI_get_cursor_x_position() { return(cursor_position.first); }
int UI_get_cursor_y_position() { return(cursor_position.second); }

static int UI_id = 0;

int UI_create_ID(int component_type, int toggle_group) {
    // Assume component_type and toggle_group are in [0..9]
    // We allocate one digit for component_type, one digit for toggle_group,
    // and then UI_id is appended at the end.
    // Format: CC TT U...
    // Example: component_type=1, toggle_group=1, UI_id=13 -> 1 * 10000 + 1 * 100 + 13 = 11013
    
    if (component_type < 0 || component_type > 9 ||
        toggle_group < 0 || toggle_group > 9) {
            Brain.Screen.printAt(30, 30, "0-9 MAX");
            print("0-9 MAX");
            std::abort();
    }

    int id = component_type * 10000 + toggle_group * 1000 + ++UI_id;
    return id;
}

int UI_decode_component_type(int id) {
    return(id / 10000);
}

int UI_decode_toggle_group(int id) {
    return((id % 10000) / 1000);
}

int UI_decode_unique_id(int id) {
    return ((id % 10000) % 1000);
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
          return (96 * distance);
      case UI_distance_units::centimeters: 
          return (37.79527559 * distance);
      case UI_distance_units::pixels:
          return (1 * distance);
  }
}

std::shared_ptr<drawable> UI_crt_img(const std::string& file_name, float x, float y, float w, float h, UI_distance_units units) {
    return std::make_shared<image>(file_name, x, y, w, h, units);
}

std::shared_ptr<drawable> UI_crt_px(float x, float y, uint32_t hue, UI_distance_units units) {
    return std::make_shared<pixel>(x, y, hue, units);
}

std::shared_ptr<drawable> UI_crt_ln(float x1, float y1, float x2, float y2, uint32_t hue, UI_distance_units units) {
    return std::make_shared<line>(x1, y1, x2, y2, hue, units);
}

std::shared_ptr<drawable> UI_crt_txt(const std::string& text_label, float x, float y, UI_distance_units units) {
    return std::make_shared<text>(text_label, x, y, units);
}
std::shared_ptr<drawable> UI_crt_txt(const std::string& text_label, float x, float y, uint32_t hue, UI_distance_units units) {
    return std::make_shared<text>(text_label, x, y, hue, units);
}
std::shared_ptr<drawable> UI_crt_txt(const std::string& text_label, float x, float y, vex::color hue, UI_distance_units units) {
    return std::make_shared<text>(text_label, x, y, hue, units);
}

std::shared_ptr<drawable> UI_crt_rec(float x, float y, float w, float h, uint32_t fill_color, uint32_t outline_color, UI_distance_units units) {
    return std::make_shared<rectangle>(x, y, w, h, fill_color, outline_color, units);
}

std::shared_ptr<drawable> UI_crt_rec(float x, float y, float w, float h, vex::color fill_color, vex::color outline_color, UI_distance_units units) {
    return std::make_shared<rectangle>(x, y, w, h, fill_color, outline_color, units);
}

std::shared_ptr<drawable> UI_crt_rec(float x, float y, float w, float h, uint32_t hue, UI_distance_units units) {
    return std::make_shared<rectangle>(x, y, w, h, hue, units);
}

std::shared_ptr<drawable> UI_crt_rec(float x, float y, float w, float h, vex::color hue, UI_distance_units units) {
    return std::make_shared<rectangle>(x, y, w, h, hue, units);
}

std::shared_ptr<drawable> UI_crt_grp(std::shared_ptr<drawable> graphic_) {
    return std::make_shared<group>(graphic_);
}

std::shared_ptr<drawable> UI_crt_grp(std::vector<std::shared_ptr<drawable>> graphics) {
    return std::make_shared<group>(graphics);
}


std::shared_ptr<UI_component> UI_crt_txtbox(std::string text, std::shared_ptr<drawable> box) {
    return std::make_shared<textbox>(text, box);
}

std::shared_ptr<UI_component> UI_crt_txtbox(std::string text, text_align text_alignment, std::shared_ptr<drawable> box) {
    return std::make_shared<textbox>(text, text_alignment, box);
}

std::shared_ptr<UI_component> UI_crt_txtbox(std::string text, uint32_t text_color, std::shared_ptr<drawable> box) {
    return std::make_shared<textbox>(text, text_color, box);
}

std::shared_ptr<UI_component> UI_crt_txtbox(std::string text, uint32_t text_color, text_align text_alignment, std::shared_ptr<drawable> box) {
    return std::make_shared<textbox>(text, text_color, text_alignment, box);
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


std::shared_ptr<UI_component> UI_crt_lbl(const std::string& label_text, float x, float y, UI_distance_units units) {
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

