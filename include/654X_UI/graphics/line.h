#pragma once

#include "vex.h"

class line : public drawable 
{
public:
    line(int x1, int y1, int x2, int y2, uint32_t hue, UI_distance_units units);

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
    int x;
    int y;
    int w;
    int h;
    uint32_t hue;
};