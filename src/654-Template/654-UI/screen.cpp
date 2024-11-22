#include "vex.h"

screen::screen(int x, int y, int w, int h) :
    x(x), y(y), w(w), h(h)
{};

void screen::render() {
    for (const auto& component : UI_components) {
        component->render();
        component->is_pressing();
    }
    is_scrolling();
}

void screen::is_scrolling() {
    if (Brain.Screen.pressing() && !pressed) {
        pressed = true;
        delta_y = Brain.Screen.yPosition();
    }
    if (pressed && Brain.Screen.pressing()) {
        for (const auto& component : UI_components) {
            component->set_y_pos(component->get_y_pos() + (Brain.Screen.yPosition() - delta_y) * scroll_speed);
        }
    }
    if (!Brain.Screen.pressing()) {
        pressed = false;
    }

}

void screen::execute_toggles() {
    for (const auto& component : UI_components) {
        component->execute();
    }
}

void screen::add_UI_component(std::shared_ptr<UI_component> component) {
    UI_components.push_back(component);
}

void screen::add_UI_components(std::vector<std::shared_ptr<UI_component>> components) {
    for (const auto& component : components) {
        UI_components.push_back(component);
    }
}

void screen::clear_buffer(uint32_t* buffer, uint32_t pixel_color) {
    std::fill(buffer, buffer + (w * h), pixel_color);
}

void screen::render_buffer(uint32_t* buffer) {
    Brain.Screen.drawImageFromBuffer(buffer, x, y, w, h);
}
