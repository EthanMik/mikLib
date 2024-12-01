#pragma once

#include "vex.h"

class graphic : public UI_component
{
public:
    graphic();
    graphic(std::shared_ptr<drawable> graphic);
    graphic(std::vector<std::shared_ptr<drawable>> graphics);

    void calculate_bounds();

    int get_x_pos() override;
    int get_y_pos() override;
    int get_width() override;
    int get_height() override;

    void set_x_pos(int x) override;
    void set_y_pos(int y) override;
    void set_position(int x, int y) override;

    void render() override;

    void add_graphic();

private:
    int x, y, w, h;
    UI_distance_units units;
    std::vector<std::shared_ptr<drawable>> graphics;
};  