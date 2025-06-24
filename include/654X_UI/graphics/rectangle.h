#pragma once

#include "vex.h"

class rectangle : public drawable
{
public:
    rectangle(float x, float y, float w, float h, uint32_t fill_color, uint32_t outline_color, UI_distance_units units);
    rectangle(float x, float y, float w, float h, vex::color fill_color, vex::color outline_color, UI_distance_units units);

    rectangle(float x, float y, float w, float h, uint32_t hue, UI_distance_units units);
    rectangle(float x, float y, float w, float h, vex::color hue, UI_distance_units units);

    int get_x_pos() override;
    int get_y_pos() override;
    int get_width() override;
    int get_height() override;

    void set_x_pos(int x) override;
    void set_y_pos(int y) override;
    void set_position(int x, int y) override;

    void set_width(int w) override;
    void set_height(int h) override;

    void render() override;

private:
    int x, y, w, h;
    uint32_t fill_color;
    uint32_t outline_color;
};