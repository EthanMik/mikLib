#pragma once

#include "vex.h"

namespace mik {
    
class screen 
{
public:
    enum class alignment { LEFT, RIGHT, TOP, BOTTOM };

    screen(int x, int y, int w, int h);
    
    int get_width();
    int get_height();
    int get_x_pos();
    int get_y_pos();
    int get_component_delta_pos();
    void set_width(int w);
    void set_height(int h);
    void set_x_pos(int x);
    void set_y_pos(int y);
    
    void add_scroll_bar(std::shared_ptr<drawable> scroll_bar);
    void add_scroll_bar(std::shared_ptr<drawable> scroll_bar, alignment scroll_bar_align);

    bool needs_update();
    bool needs_full_refresh();
    void render(bool full_refresh);
    void refresh();

    void add_UI_component(std::shared_ptr<UI_component> component);
    void add_UI_components(std::vector<std::shared_ptr<UI_component>> components);
    void remove_UI_component(std::vector<int> id);
    void set_UI_components(std::vector<std::shared_ptr<UI_component>> components);
    const std::vector<std::shared_ptr<UI_component>> get_UI_components();

private:
    enum class scroll_direction { NONE, HORIZONTAL, VERTICAL };
    
    void check_bounds();
    bool is_render_exception(const std::shared_ptr<UI_component>& component);
    bool is_clickable_exception(const std::shared_ptr<UI_component>& component);

    bool is_scrolling();
    
    void update_scroll_bar();

    int get_touch_pos();
    int get_aligment_pos(alignment align, int scroll_bar_w, int scroll_bar_h);

    void execute_removal();

    int x, y, w, h;
    int component_delta_position = 0;
    std::vector<std::shared_ptr<UI_component>> UI_components;

    std::shared_ptr<drawable> scroll_bar;
    scroll_direction scroll_dir = scroll_direction::NONE;
    bool finished_scrolling;
    bool pressed = false;
    int prev_touch = 0;
    const float scroll_speed = 0.1;
    int screen_pos = 0;
    float scr_speed_limit = 1;

    std::unordered_map<int, size_t> id_to_index;
    bool removal_scheduled = false;
    std::vector<int> removal_id;

    bool screen_needs_refresh;
    bool screen_needs_full_refresh;
    bool needs_render_update;
    int render_index;
    input_type input_type = input_type::TOUCHSCREEN;
};
}