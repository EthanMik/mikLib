#pragma once

#include <memory>
#include "mikLib/ui.h"

namespace mik {

class button : public UI_component 
{
public:
    enum class button_state { INACTIVE, PRESSING, TRIGGERED };

    button(std::shared_ptr<drawable> button_graphic, std::function<void()> on_click_func);
    
    int get_x_pos() override;
    int get_y_pos() override;
    int get_width() override;
    int get_height() override;
    button_state get_state();
    
    void set_x_pos(int x) override;
    void set_y_pos(int y) override;
    void set_position(int x, int y) override;
    void set_default_state(std::shared_ptr<drawable> default_state);
    void set_states(std::shared_ptr<drawable> pressing_state, std::shared_ptr<drawable> triggered_state) override;
    void set_callback(std::function<void()> cb, bool call_once = true) override;
    
    void render() override;
    bool needs_update() override;
    
    void is_pressing(input_type input_type) override;
    void is_pressing_touch();
    void is_pressing_controller();
    
private:
    button_state state = button_state::INACTIVE;
    button_state prev_state;
    bool needs_render_update;

    std::shared_ptr<drawable> button_graphic = nullptr;
    std::shared_ptr<drawable> pressed_button_graphic = nullptr;
    std::shared_ptr<drawable> triggered_button_graphic = nullptr;
    int x, y, w, h;
    std::function<void()> on_click;
    bool pressed = false;

    int initial_msec = 0;
    const int cooldown_msec = 200;
    bool cooldown = false;
};
}
