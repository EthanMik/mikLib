#pragma once

#include "vex.h"

class textbox : public UI_component
{
public:
    textbox(std::string text, std::shared_ptr<drawable> box);

    int get_x_pos() override;
    int get_y_pos() override;
    int get_width() override;
    int get_height() override;

    void set_x_pos(int x) override;
    void set_y_pos(int y) override;
    void set_position(int x, int y) override;

    void set_width(int w) override;
    void set_height(int h) override;
    
    bool needs_update() override;
    void render() override;

private:
    bool needs_render_update;

    int x, y, w, h;
    UI_distance_units units;
    std::string text;
    std::shared_ptr<drawable> box;
};  