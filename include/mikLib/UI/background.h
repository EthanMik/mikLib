#pragma once

#include "vex.h"

namespace mik {

class background : public UI_component 
{
public:
    background(std::shared_ptr<drawable> graphic);

    int get_x_pos() override;
    int get_y_pos() override;
    int get_width() override;
    int get_height() override;

    void set_x_pos(int x) override;
    void set_y_pos(int y) override;
    void set_position(int x, int y) override;

    void render() override;
    bool needs_update() override;

private:
    bool needs_render_update;
    std::shared_ptr<drawable> graphic;
    int x, y, w, h;
    bool position_is_set = false;
};
}