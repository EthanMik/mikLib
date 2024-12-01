#pragma once

#include "vex.h"

class rectangle : public drawable
{
public:
    rectangle(int x, int y, int w, int h, uint32_t fill_color, uint32_t outline_color, UI_distance_units units);
    rectangle(int x, int y, int w, int h, vex::color fill_color, vex::color outline_color, UI_distance_units units);

    rectangle(int x, int y, int w, int h, uint32_t hue, UI_distance_units units);
    rectangle(int x, int y, int w, int h, vex::color hue, UI_distance_units units);

    int get_x_pos() override;
    int get_y_pos() override;
    int get_width() override;
    int get_height() override;

    void set_x_pos(int x) override;
    void set_y_pos(int y) override;
    void set_position(int x, int y) override;

    void render() override;

private:
    int x, y, w, h;
    uint32_t fill_color;
    uint32_t outline_color;
};