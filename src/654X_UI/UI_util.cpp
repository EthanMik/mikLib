#include "vex.h"

static std::pair<int, int> cursor_position;
static std::pair<int, int> cursor_bound;

static bool up_pressed = false;
static bool down_pressed = false;
static bool left_pressed = false;
static bool right_pressed = false;

int UI_get_cursor_x_position() { return(cursor_position.first); }
int UI_get_cursor_y_position() { return(cursor_position.second); }

int UI_get_cursor_x_bound() { return(cursor_bound.first); }
int UI_get_cursor_y_bound() { return(cursor_bound.second); }

void UI_update_cursor_position(std::shared_ptr<screen> scr) {
    
    std::vector<std::pair<int, int>> cursor_positions;
    std::vector<std::pair<int, int>> cursor_bounds;

    for (const auto& component : scr->get_UI_components()) {
        int comp_type = UI_decode_component_type(component->get_ID());
        if (comp_type == UI_Button_ID || comp_type == UI_Toggle_ID) {
            if (comp_type == UI_Toggle_ID) {
                auto* toggle_component = static_cast<toggle*>(component.get());
                if (toggle_component->is_locked()) {
                    continue;
                }
            }
            int x_midpoint = (component->get_x_pos() * 2 + component->get_width()) / 2;
            int y_midpoint = (component->get_y_pos() * 2 + component->get_height()) / 2;
            cursor_positions.emplace_back(x_midpoint, y_midpoint);
            cursor_bounds.emplace_back(x_midpoint - component->get_x_pos(), y_midpoint - component->get_y_pos());
        }
    }

if (Controller.ButtonUp.pressing()) {
    up_pressed = true;
}

if (up_pressed && !Controller.ButtonUp.pressing()) {
    int bestIndex  = -1;
    int bestDistSq = std::numeric_limits<int>::max();
    
    for (int i = 0; i < static_cast<int>(cursor_positions.size()); ++i) {
        const auto& p = cursor_positions[i];
        
        // "Up" means p is above current cursor
        if (p.second < cursor_position.second) {
            int dx = p.first  - cursor_position.first;
            int dy = p.second - cursor_position.second;
            int distSq = dx * dx + dy * dy;
            
            if (distSq < bestDistSq) {
                bestDistSq = distSq;
                bestIndex  = i;
            }
        }
    }
    
    if (bestIndex != -1) {
        cursor_position = cursor_positions[bestIndex];
        cursor_bound = cursor_bounds[bestIndex];
    }
    up_pressed = false;
}

// --- Copy of the logic for "Down" ---
else if (Controller.ButtonDown.pressing()) {
    down_pressed = true;
}

else if (down_pressed && !Controller.ButtonDown.pressing()) {
    int bestIndex  = -1;
    int bestDistSq = std::numeric_limits<int>::max();

    for (int i = 0; i < static_cast<int>(cursor_positions.size()); ++i) {
        const auto& p = cursor_positions[i];

        // "Down" means p is below current cursor
        if (p.second > cursor_position.second) {
            int dx = p.first  - cursor_position.first;
            int dy = p.second - cursor_position.second;
            int distSq = dx * dx + dy * dy;

            if (distSq < bestDistSq) {
                bestDistSq = distSq;
                bestIndex  = i;
            }
        }
    }

    if (bestIndex != -1) {
        cursor_position = cursor_positions[bestIndex];
        cursor_bound = cursor_bounds[bestIndex];
    }
    down_pressed = false;
}

// --- Copy of the logic for "Left" ---
else if (Controller.ButtonLeft.pressing()) {
    left_pressed = true;
}

else if (left_pressed && !Controller.ButtonLeft.pressing()) {
    int bestIndex  = -1;
    int bestDistSq = std::numeric_limits<int>::max();

    for (int i = 0; i < static_cast<int>(cursor_positions.size()); ++i) {
        const auto& p = cursor_positions[i];

        // "Left" means p is left of current cursor
        if (p.first < cursor_position.first) {
            int dx = p.first  - cursor_position.first;
            int dy = p.second - cursor_position.second;
            int distSq = dx * dx + dy * dy;

            if (distSq < bestDistSq) {
                bestDistSq = distSq;
                bestIndex  = i;
            }
        }
    }

    if (bestIndex != -1) {
        cursor_position = cursor_positions[bestIndex];
        cursor_bound = cursor_bounds[bestIndex];
    }
    left_pressed = false;
}

// --- Copy of the logic for "Right" ---
else if (Controller.ButtonRight.pressing()) {
    right_pressed = true;
}

else if (right_pressed && !Controller.ButtonRight.pressing()) {
    int bestIndex  = -1;
    int bestDistSq = std::numeric_limits<int>::max();

    for (int i = 0; i < static_cast<int>(cursor_positions.size()); ++i) {
        const auto& p = cursor_positions[i];

        // "Right" means p is right of current cursor
        if (p.first > cursor_position.first) {
            int dx = p.first  - cursor_position.first;
            int dy = p.second - cursor_position.second;
            int distSq = dx * dx + dy * dy;

            if (distSq < bestDistSq) {
                bestDistSq = distSq;
                bestIndex  = i;
            }
        }
    }

    if (bestIndex != -1) {
        cursor_position = cursor_positions[bestIndex];
        cursor_bound = cursor_bounds[bestIndex];
    }
    right_pressed = false;
}
}

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

std::shared_ptr<drawable> UI_crt_txt(const std::string& text_label, int x, int y, UI_distance_units units) {
    return std::make_shared<text>(text_label, x, y, units);
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

