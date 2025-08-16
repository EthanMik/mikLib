#pragma once

#include "vex.h"

namespace mik {

class image : public drawable 
{
public:
    image(const std::string& file_name, float x, float y, float w, float h, UI_distance_units units);
    image(uint8_t* img_binary, float x, float y, float w, float h, UI_distance_units units);
    // ~image();

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
    std::string file_name;
    uint8_t* img_binary;
    bool no_image_found = false;
    bool using_SD;
    std::shared_ptr<drawable> image_no_texture;
    int x;
    int y;
    int w;
    int h;
    UI_distance_units units;
};
}