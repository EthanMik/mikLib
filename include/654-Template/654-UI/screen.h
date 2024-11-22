#pragma once

#include "vex.h"

class screen 
{
public:
    screen(int x, int y, int w, int h);

    void render();

    void is_scrolling();
    void execute_toggles();

    void add_UI_component(std::shared_ptr<UI_component> component);
    void add_UI_components(std::vector<std::shared_ptr<UI_component>> components);
    void set_UI_components(std::vector<std::shared_ptr<UI_component>> components);

private:
    int x;
    int y;
    int w;
    int h;

    void clear_buffer(uint32_t* buffer, uint32_t pixel_color);
    void render_buffer(uint32_t* buffer);
    std::vector<std::shared_ptr<UI_component>> UI_components;
    bool pressed = false;
    int delta_y = 0;
    float scroll_speed = 0.1;
};