#pragma once

#include <memory>
#include "mikLib/ui.h"

namespace mik {

class textbox : public UI_component
{
public:
    textbox(std::string text, std::shared_ptr<drawable> box, vex::fontType font, int padding = 10);
    textbox(std::string text, text_align text_alignment, std::shared_ptr<drawable> box, vex::fontType font, int padding = 10);
    textbox(std::string text, text_align text_alignment, const std::string& bg_color, std::shared_ptr<drawable> box, vex::fontType font, int padding = 10);
    textbox(std::string text, const std::string& text_color, const std::string& bg_color, text_align text_alignment, std::shared_ptr<drawable> box, vex::fontType font, int padding = 10);

    int get_x_pos() override;
    int get_y_pos() override;
    int get_width() override;
    int get_height() override;
    std::string get_text();

    void set_x_pos(int x) override;
    void set_y_pos(int y) override;
    void set_position(int x, int y) override;

    void set_width(int w) override;
    void set_height(int h) override;

    bool needs_update() override;
    void render() override;

    void set_text(std::string text);
    void wrap_text();

    void set_text_color(const std::string& color);
    const std::string& get_text_color();

private:
    void draw_text();
    
    bool needs_render_update;

    int x, y, w, h;
    UI_distance_units units;
    std::string text;
    std::shared_ptr<drawable> box;
    std::string text_color;
    std::string bg_color;
    text_align alignment;
    vex::fontType font;
    int padding;
    std::vector<std::string> wrapped_text;
};
}