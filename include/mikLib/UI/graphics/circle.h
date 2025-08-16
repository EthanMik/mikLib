#pragma once

#include "vex.h"

namespace mik {

class circle : public drawable
{
public:
    circle(float x, float y, float w, float h, uint32_t fill_color, UI_distance_units units);
    circle(float x, float y, float w, float h, const std::string& fill_color_hex, UI_distance_units units);

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
    int x, y;
    float r;
    uint32_t fill_color;
    const std::string fill_color_hex;
    bool using_hex = false;
};
}