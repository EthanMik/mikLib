#pragma once

#include "vex.h"

#define SCREEN_WIDTH 480
#define SCREEN_HEIGHT 240

class screen 
{
public:
    enum class alignment { LEFT, RIGHT, TOP, BOTTOM };

    screen(int x, int y, int w, int h);
    
    int get_width();
    int get_height();
    int get_x_pos();
    int get_y_pos();
    void set_width(int w);
    void set_height(int h);
    void set_x_pos(int x);
    void set_y_pos(int y);

    void set_swap_pending();
    bool is_swap_pending();
    void clear_swap_pending();

    void add_scroll_bar(std::shared_ptr<drawable> scroll_bar);
    void add_scroll_bar(std::shared_ptr<drawable> scroll_bar, alignment scroll_bar_align);

    void render();

    void add_UI_component(std::shared_ptr<UI_component> component);
    void add_UI_components(std::vector<std::shared_ptr<UI_component>> components);
    void set_UI_components(std::vector<std::shared_ptr<UI_component>> components);
    std::vector<std::shared_ptr<UI_component>> get_UI_components();

private:
    enum class scroll_direction { HORIZONTAL, VERTICAL };

    bool swap_pending = false;
    
    void check_bounds(int w, int h);

    void is_scrolling();
    void update_scroll_bar();

    int get_touch_pos();
    int get_aligment_pos(alignment align, int scroll_bar_w, int scroll_bar_h);

    int x, y, w, h;
    std::vector<std::shared_ptr<UI_component>> UI_components;

    std::shared_ptr<drawable> scroll_bar;
    scroll_direction scroll_dir;
    bool pressed = false;
    int prev_touch = 0;
    const float scroll_speed = 0.1;
    int screen_pos = 0;
    float scr_speed_limit = 1;
};