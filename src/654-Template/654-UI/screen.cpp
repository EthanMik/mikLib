#include "vex.h"

screen::screen(int x, int y, int w, int h) :
    x(x), y(y), w(w), h(h)
{
    check_bounds(w, h);
};

void screen::check_bounds(int w, int h) {
    if (w > SCREEN_WIDTH && h  > SCREEN_HEIGHT) {
        Brain.Screen.printAt(30, 30, "BOTH SCREEN SIZE BOUNDS LARGER THAN DISPLAY");
        exit(1);
    }

    if (h > SCREEN_HEIGHT) {
        scroll_dir = scroll_direction::VERTICAL;
    }
    if (w > SCREEN_WIDTH) {
        scroll_dir = scroll_direction::HORIZONTAL;
    }
}

int screen::get_width() { return(this->w); }
int screen::get_height() { return(this->h); }
int screen::get_x_pos() { return(this->x); }
int screen::get_y_pos() { return(this->y); }
void screen::set_width(int w) { check_bounds(w, h); this->w = w; }
void screen::set_height(int h) { check_bounds(w, h); this->h = h; } 

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
        scroll_bar->set_y_pos((float)screen_pos * -(((float)SCREEN_HEIGHT - scroll_bar->get_height() - y) / h) + y);
        break;
    case scroll_direction::HORIZONTAL:
        scroll_bar->set_x_pos((float)screen_pos * -(((float)SCREEN_WIDTH - scroll_bar->get_width() - x) / w) + x);
        break;    
    }
    scroll_bar->render();
}

void screen::render() {
    for (const auto& component : UI_components) {
        component->render();
        if(!pressed) {
            component->is_pressing();
        }
    }
    if (scroll_dir == scroll_direction::VERTICAL || scroll_dir == scroll_direction::HORIZONTAL) {
        is_scrolling();
    }
}

void screen::is_scrolling() {
    float touch_x = Brain.Screen.xPosition();
    float touch_y = Brain.Screen.yPosition();
    bool is_touch_within_screen = touch_x >= x && touch_x <= x + w && touch_y >= y && touch_y <= y + h;

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
            dimension = h;
        } else {
            dimension = w;
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

        int local_position = (delta_touch * scroll_speed) * scr_speed_limit;
        if (screen_pos + local_position <= 0 && screen_pos + local_position >= -dimension && std::abs(delta_touch) > 10) {
            scr_speed_limit = 1;
            for (const auto& component : UI_components) {
                if (scroll_dir == scroll_direction::VERTICAL) {
                    component->set_y_pos(component->get_y_pos() + local_position);
                } else {
                    component->set_x_pos(component->get_x_pos() + local_position);
                }
            }
            screen_pos += local_position;
        }
        update_scroll_bar();
    }
    if (!Brain.Screen.pressing()) {
        pressed = false;
    }
}

int screen::get_touch_pos() {
    switch (scroll_dir) {
    case scroll_direction::HORIZONTAL:
        return Brain.Screen.xPosition();    
    case scroll_direction::VERTICAL:
        return Brain.Screen.yPosition();
    }
}

void screen::execute_toggles() {
    for (const auto& component : UI_components) {
        component->execute();
    }
}

void screen::add_UI_component(std::shared_ptr<UI_component> component) {
    component->set_position(component->get_x_pos() + x, component->get_y_pos() + y);
    UI_components.push_back(component);
}

void screen::add_UI_components(std::vector<std::shared_ptr<UI_component>> components) {
    for (const auto& component : components) {
        component->set_position(component->get_x_pos() + x, component->get_y_pos() + y);
        UI_components.push_back(component);
    }
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
