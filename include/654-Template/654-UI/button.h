#pragma once

#include "vex.h"

class button : public UI_component 
{
public:
    button(std::shared_ptr<drawable> button_graphic, std::shared_ptr<drawable> pressed_button_graphic, std::function<void()> on_click_func);

    int get_x_pos() override;
    int get_y_pos() override;
    int get_width() override;
    int get_height() override;

    void set_x_pos(int x) override;
    void set_y_pos(int y) override;
    void set_position(int x, int y) override;

    void render() override;
    
    void is_pressing() override;

private:
    std::shared_ptr<drawable> button_graphic;
    std::shared_ptr<drawable> pressed_button_graphic;
    int x, y, w, h;
    std::function<void()> on_click;
    bool pressed = false;
};
