#include "vex.h"

using namespace mik;

screen::screen(int x, int y, int w, int h) :
    x(x), y(y), w(w), h(h)
{
    check_bounds();
};

void screen::check_bounds() {
    if (w > SCREEN_WIDTH && h  > SCREEN_HEIGHT) {
        print("screen::check_bounds() - BOTH SCREEN SIZE BOUNDS LARGER THAN DISPLAY");
        std::abort();
    }

    if (h > SCREEN_HEIGHT - y) {
        scroll_dir = scroll_direction::VERTICAL;
    }
    if (w > SCREEN_WIDTH - x) {
        scroll_dir = scroll_direction::HORIZONTAL;
    }
}

int screen::get_width() { return(this->w); }
int screen::get_height() { return(this->h); }
int screen::get_component_delta_pos() { return(component_delta_position); }
int screen::get_x_pos() { return(this->x); }
int screen::get_y_pos() { return(this->y); }
void screen::set_width(int w) { 
    this->w = w; 
    check_bounds(); 
}
void screen::set_height(int h) { 
    this->h = h;
    check_bounds(); 
} 

void screen::set_x_pos(int x) {
    this->x = x;
    for (const auto& component : UI_components) {
        component->set_position(component->get_x_pos() + x, component->get_y_pos() + y);
    }
} 
void screen::set_y_pos(int y) { 
    this->y = y;
    for (const auto& component : UI_components) {
        component->set_position(component->get_x_pos() + x, component->get_y_pos() + y);
    }
} 

void screen::add_scroll_bar(std::shared_ptr<drawable> scroll_bar) {
    if (w < scroll_bar->get_width() || h < scroll_bar->get_height()) {
        Brain.Screen.printAt(30, 30, "SCROLL BAR CANNOT BE LARGER THAN SCREEN");
        exit(1);
    }
    this->scroll_bar = scroll_bar;
}

void screen::add_scroll_bar(std::shared_ptr<drawable> scroll_bar, alignment scroll_bar_align) {
    int align_pos = get_aligment_pos(scroll_bar_align, scroll_bar->get_width(), scroll_bar->get_height());
    scroll_bar->set_position(align_pos, align_pos);
    add_scroll_bar(scroll_bar);
}

void screen::update_scroll_bar() {
    switch (scroll_dir) {
    case scroll_direction::VERTICAL:
        scroll_bar->set_y_pos((float)screen_pos * -(((float)SCREEN_HEIGHT - scroll_bar->get_height() - y) / (h - SCREEN_HEIGHT + y)) + y);
        break;
    case scroll_direction::HORIZONTAL:
        scroll_bar->set_x_pos((float)screen_pos * -(((float)SCREEN_WIDTH - scroll_bar->get_width() - x) / (w - SCREEN_WIDTH + x)) + x);
        break; 
    case scroll_direction::NONE:
        break;   
    }
    scroll_bar->render();
}


bool screen::is_render_exception(const std::shared_ptr<UI_component>& component) {
    bool is_exception = false;

    if ((scroll_dir == scroll_direction::VERTICAL) &&
        (component->get_y_pos() + component->get_height() < this->y || 
        component->get_y_pos() + component->get_height() > this->y + this->h)) {
            is_exception = true;
    }
    if ((scroll_dir == scroll_direction::HORIZONTAL) &&
        (component->get_x_pos() + component->get_width() < this->x || 
        component->get_x_pos() > this->x + this->w)) {
            is_exception = true;

    }
    if (component->get_ID() < 0) {
        is_exception = true;
    }

    return is_exception;
}

bool screen::is_clickable_exception(const std::shared_ptr<UI_component>& component) {
    bool is_exception = false;

    if ((scroll_dir == scroll_direction::VERTICAL) &&
        (component->get_y_pos() < this->y || 
        component->get_y_pos() > this->y + this->h)) {
            is_exception = true;
    }
    if ((scroll_dir == scroll_direction::HORIZONTAL) &&
        (component->get_x_pos() + component->get_width() < this->x || 
        component->get_x_pos() > this->x + this->w)) {
            is_exception = true;

    }
    if (component->get_ID() < 0) {
        is_exception = true;
    }

    return is_exception;
}

bool screen::needs_update() {
    if (removal_scheduled) {
        execute_removal();
        removal_scheduled = false;
        needs_render_update = true;
    }

    for (std::size_t i = 0; i < UI_components.size(); ++i) {
        auto& component = UI_components[i];
        if (is_render_exception(component)) {
            continue;
        }
        if (!pressed && !is_clickable_exception(component)) {
            component->is_pressing(input_type);
        }
        if (component->needs_update()) {
            if (i < render_index || render_index == 0) {
                render_index = i;
            }

            needs_render_update = true;
        }
    }

    if (scroll_dir == scroll_direction::VERTICAL || scroll_dir == scroll_direction::HORIZONTAL) {
        if (is_scrolling()) {
            render_index = 0;
        }
    }

    if (needs_render_update) {
        needs_render_update = false;
        return true;
    }
    return false;
}

bool screen::needs_full_refresh() {
    if (screen_needs_full_refresh) {
        screen_needs_full_refresh = false;
        return true;
    }
    return false;
}

void screen::refresh() {
    screen_needs_refresh = true;
}

void screen::render(bool full_refresh) {
    if (full_refresh || screen_needs_refresh) {
        render_index = 0;
        screen_needs_refresh = false;
    }

    for (std::size_t i = render_index; i < UI_components.size(); ++i) {
        auto& component = UI_components[i];

        if (is_render_exception(component)) {
            continue;
        }

        component->render();

        if (scroll_dir == scroll_direction::VERTICAL || scroll_dir == scroll_direction::HORIZONTAL) {
            update_scroll_bar();
        }
    }
    render_index = 0;
}

bool screen::is_scrolling() {
    bool scrolled = false;
    float touch_x = Brain.Screen.xPosition();
    float touch_y = Brain.Screen.yPosition();
    bool is_touch_within_screen = touch_x >= x && touch_x <= x + w && touch_y >= y && touch_y <= y + h;

    if (finished_scrolling) {
        finished_scrolling = false;
        screen_needs_full_refresh = true;
    }

    if (Brain.Screen.pressing() && !pressed && is_touch_within_screen) {
        pressed = true;
        prev_touch = get_touch_pos();
    }
    if (pressed && Brain.Screen.pressing() && is_touch_within_screen) {
        int current_touch = get_touch_pos();
        int delta_touch = current_touch - prev_touch;

        int direction = (delta_touch > 0) ? 1 : -1;
        int dimension;

        if (scroll_dir == scroll_direction::VERTICAL) {
            dimension = h - SCREEN_HEIGHT + y;
        } else {
            dimension = w - SCREEN_WIDTH + x;
        }

        float distance_to_lower_bound = screen_pos;
        float distance_to_upper_bound = -dimension - screen_pos;

        scr_speed_limit = 1.0;
        float threshold = 20.0;

        if (direction < 0 && distance_to_upper_bound > threshold) {
            threshold = 5;
            scr_speed_limit = distance_to_upper_bound / -threshold;
            scr_speed_limit = std::max(scr_speed_limit, 0.1f);
        } else if (direction > 0 && distance_to_lower_bound > -threshold) {
            threshold = 20;
             scr_speed_limit = distance_to_lower_bound / threshold;
             scr_speed_limit = std::max(scr_speed_limit, 0.1f);
        }

        int local_position = (delta_touch * scroll_speed) * scr_speed_limit + 1;
        local_position = local_position < 0 ? local_position - 1 : local_position + 1; 
        if (screen_pos + local_position <= this->x && screen_pos + local_position >= -dimension && std::abs(delta_touch) > 10) {
            scr_speed_limit = 1;
            for (const auto& component : UI_components) {
                if (scroll_dir == scroll_direction::VERTICAL) {
                    int _y = component->get_y_pos() + local_position;
                    if (_y < SCREEN_HEIGHT && _y < h) { finished_scrolling = true; screen_needs_full_refresh = true; }
                    component->set_y_pos(_y);
                } else {
                    int _x = component->get_x_pos() + local_position;
                    if (_x < SCREEN_WIDTH && _x > w) { finished_scrolling = true; screen_needs_full_refresh = true; }
                    component->set_x_pos(_x);
                }
                if (local_position != 0) {
                    scrolled = true;
                }
            }
            component_delta_position += local_position;
            
            screen_pos += local_position;
        }
    }
    if (!Brain.Screen.pressing()) {
        pressed = false;
    }
    return scrolled;
}

int screen::get_touch_pos() {
    switch (scroll_dir) {
    case scroll_direction::HORIZONTAL:
        return Brain.Screen.xPosition();    
    case scroll_direction::VERTICAL:
        return Brain.Screen.yPosition();
    case scroll_direction::NONE:
        return 0;
    }
}

void screen::add_UI_component(std::shared_ptr<UI_component> component) {
    component->set_position(component->get_x_pos() + x, component->get_y_pos() + y);
    UI_components.push_back(component);
    id_to_index[component->get_ID()] = UI_components.size() - 1;
}

void screen::add_UI_components(std::vector<std::shared_ptr<UI_component>> components) {
    for (const auto& component : components) {
        component->set_position(component->get_x_pos() + x, component->get_y_pos() + y);
        UI_components.push_back(component);
        id_to_index[component->get_ID()] = UI_components.size() - 1;
    }
}

void screen::remove_UI_component(std::vector<int> id) {
    removal_id.swap(id);
    removal_scheduled = true;
}

void screen::execute_removal() {
    for (auto id : removal_id) {
        auto it = id_to_index.find(id);
        if (it != id_to_index.end()) {
            size_t index_to_remove = it->second;
            size_t last_index = UI_components.size() - 1;

            if (index_to_remove != last_index) {
                std::swap(UI_components[index_to_remove], UI_components[last_index]);
                int moved_element_id = UI_components[index_to_remove]->get_ID();
                id_to_index[moved_element_id] = index_to_remove;
            }

            UI_components.pop_back();
            id_to_index.erase(it);
        }
    }
}

const std::vector<std::shared_ptr<UI_component>> screen::get_UI_components() {
    return UI_components;
}

int screen::get_aligment_pos(alignment alignment, int scroll_bar_w, int scroll_bar_h) {
    switch (alignment) {
        case alignment::BOTTOM:
            return (h + y) - scroll_bar_h;
        case alignment::TOP:
            return y;
        case alignment::LEFT:
            return x;
        case alignment::RIGHT:
            return (SCREEN_WIDTH + x) - scroll_bar_w;
    }
}
