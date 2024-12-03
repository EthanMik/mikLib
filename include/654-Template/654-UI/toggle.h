#pragma once

#include "vex.h"

class toggle : public UI_component
{
public:
    toggle(std::shared_ptr<drawable> toggle_graphic, std::shared_ptr<drawable> pressed_toggle_graphic, std::function<void()> callback, int id);
    toggle(std::shared_ptr<drawable> toggle_graphic, std::shared_ptr<drawable> pressed_toggle_graphic, std::function<void()> callback);
    toggle(std::shared_ptr<drawable> toggle_graphic, std::shared_ptr<drawable> pressed_toggle_graphic);

    int get_x_pos() override;
    int get_y_pos() override;
    int get_width() override;
    int get_height() override;

    void set_x_pos(int x) override;
    void set_y_pos(int y) override;
    void set_position(int x, int y) override;
    void set_callback(std::function<void()> cb) override;

    void lock_toggle();
    void unlock_toggle();

    void render() override;
    
    void is_pressing() override;
    void unpress();

    int get_ID() override;

    void execute();
    bool get_toggle_state();

private:    
    std::shared_ptr<drawable> toggle_graphic;
    std::shared_ptr<drawable> pressed_toggle_graphic;
    int x, y, w, h;
    std::function<void()> callback;
    int id;

    bool locked = false;

    bool pressed = false;
    bool is_toggled = false;
};