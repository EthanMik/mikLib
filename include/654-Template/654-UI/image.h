#pragma once

#include "vex.h"

class image : public UI_component 
{
public:
    image(const char *file_name, int x, int y, int w, int h, distance_units units);

    void render() override;
    void draw();

    int get_x_pos() override;
    int get_y_pos() override;
    int get_w_pos() override;
    int get_h_pos() override;

    void set_x_pos(int x) override;
    void set_y_pos(int y) override;

private:
    std::string file_name;
    int x;
    int y;
    int w;
    int h;
    distance_units units;
};