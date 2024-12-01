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

    void render() override;
    
    void is_pressing() override;

    void execute();

    bool get_toggle_state();
    int get_toggle_id();

private:
    std::shared_ptr<drawable> toggle_graphic;
    std::shared_ptr<drawable> pressed_toggle_graphic;
    int x, y, w, h;
    std::function<void()> callback;
    int id;

    bool pressed = false;
    bool is_toggled = false;
};