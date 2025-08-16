#pragma once

#include "vex.h"

namespace mik {

class toggle : public UI_component
{
public:
    toggle(std::shared_ptr<drawable> toggle_graphic, std::function<void()> callback, int id);
    toggle(std::shared_ptr<drawable> toggle_graphic, std::function<void()> callback);
    toggle(std::shared_ptr<drawable> toggle_graphic);

    int get_x_pos() override;
    int get_y_pos() override;
    int get_width() override;
    int get_height() override;

    void set_x_pos(int x) override;
    void set_y_pos(int y) override;
    void set_position(int x, int y) override;
    void set_callback(std::function<void()> cb, bool call_once = true) override;
    void set_states(std::shared_ptr<drawable> pressing_state, std::shared_ptr<drawable> triggered) override;
    
    bool is_locked();
    void lock_toggle();
    void unlock_toggle();

    bool needs_update() override;
    void render() override;

    void is_pressing(input_type input_type) override;
    void is_pressing_touch();
    void is_pressing_controller();

    void press();
    void unpress();

    void execute();
    bool get_toggle_state();

private:
    enum class toggle_state { INACTIVE, PRESSING, TOGGLED };

    toggle_state state = toggle_state::INACTIVE;
    toggle_state prev_state;
    bool needs_render_update;

    std::shared_ptr<drawable> toggle_graphic = nullptr;
    std::shared_ptr<drawable> pressing_toggle_graphic = nullptr;
    std::shared_ptr<drawable> toggled_graphic = nullptr;

    int x, y, w, h;
    std::function<void()> callback;
    int id;

    bool locked = false;
    bool call_once = true;

    bool pressed = false;
    bool is_toggled = false;

    int initial_msec = 0;
    const int cooldown_msec = 300;
    bool cooldown = false;
};
}