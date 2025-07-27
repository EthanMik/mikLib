#pragma once

#include "vex.h"

namespace mik {

class group : public drawable
{
public:
    group();
    group(std::shared_ptr<drawable> graphic);
    group(std::vector<std::shared_ptr<drawable>> graphics);

    void calculate_bounds();

    int get_x_pos() override;
    int get_y_pos() override;
    int get_width() override;
    int get_height() override;
    int get_size();

    void set_x_pos(int x) override;
    void set_y_pos(int y) override;
    void set_position(int x, int y) override;

    void set_width(int w) override;
    void set_height(int h) override;
    
    void render() override;

private:
    int x, y, w, h;
    UI_distance_units units;
    std::vector<std::shared_ptr<drawable>> graphics;
};
}  