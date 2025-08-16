#include "vex.h"

using namespace mik;

group::group() {};

group::group(std::shared_ptr<drawable> graphic) {    
    graphics.push_back(graphic);

    calculate_bounds();
};

group::group(std::vector<std::shared_ptr<drawable>> graphics) :
    graphics(graphics)
{
    calculate_bounds();
};

void group::calculate_bounds() {
    int min_x = graphics[0]->get_x_pos();
    int min_y = graphics[0]->get_y_pos();
    int max_x = min_x + graphics[0]->get_width();
    int max_y = min_y + graphics[0]->get_height();

    for (const auto& graphic : graphics) {
        int x = graphic->get_x_pos();
        int y = graphic->get_y_pos();
        int w = graphic->get_width();
        int h = graphic->get_height();

        min_x = std::min(min_x, x);
        min_y = std::min(min_y, y);
        max_x = std::max(max_x, x + w);
        max_y = std::max(max_y, y + h);
    }

    this->x = min_x;
    this->y = min_y;
    this->w = max_x - min_x;   
    this->h = max_y - min_y;   
}

int group::get_x_pos() { return(x); }
int group::get_y_pos() { return(y); }
int group::get_width() { return(w); }
int group::get_height() { return(h); }
int group::get_size() { return(graphics.size()); }

void group::set_x_pos(int x) {
    int delta_x = x - this->x;
    for (const auto& graphic : graphics) {
        graphic->set_x_pos(graphic->get_x_pos() + delta_x);
    }
    this->x = x;
}

void group::set_y_pos(int y) { 
    int delta_y = y - this->y;
    for (const auto& graphic : graphics) {
        graphic->set_y_pos(graphic->get_y_pos() + delta_y);
    }
    this->y = y;
}

void group::set_position(int x, int y) { 
    set_x_pos(x);
    set_y_pos(y);
}

void group::set_width(int w) { 
    int delta_w = w - this->w;
    for (const auto& graphic : graphics) {
        graphic->set_width(graphic->get_width() + delta_w);
    }
    this->w = w;
}
void group::set_height(int h) { 
    int delta_h = h - this->h;
    for (const auto& graphic : graphics) {
        graphic->set_height(graphic->get_height() + delta_h);
    }
    this->h = h;
}

void group::render() {
    for (const auto& graphic : graphics) {
        graphic->render();
    }
}