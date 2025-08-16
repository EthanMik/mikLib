#pragma once

#include "vex.h"

namespace mik {

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
    int get_size();

    void set_x_pos(int x) override;
    void set_y_pos(int y) override;
    void set_position(int x, int y) override;

    void replace_graphic(std::shared_ptr<drawable> graphic);
    void replace_graphic(std::vector<std::shared_ptr<drawable>> graphic);
    void remove_first_graphic();

    void set_width(int w) override;
    void set_height(int h) override;
    
    bool needs_update() override;
    void render() override;

    void add_graphic(std::shared_ptr<drawable> graphic);

private:
    bool needs_render_update;
    std::vector<std::shared_ptr<drawable>> graphics;

    int x, y, w, h;
    UI_distance_units units;
};  
}