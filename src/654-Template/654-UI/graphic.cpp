#include "vex.h"

graphic::graphic() {};

graphic::graphic(std::shared_ptr<drawable> graphic) {
    graphics.push_back(graphic);

    calculate_bounds();
};

graphic::graphic(std::vector<std::shared_ptr<drawable>> graphics) :
    graphics(graphics)
{
    calculate_bounds();
};

void graphic::calculate_bounds() {
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

int graphic::get_x_pos() { return(x); }
int graphic::get_y_pos() { return(y); }
int graphic::get_width() { return(w); }
int graphic::get_height() { return(h); }

void graphic::set_x_pos(int x) {
    for (const auto& graphic : graphics) {
        graphic->set_x_pos(graphic->get_x_pos() + x);
    }
}

void graphic::set_y_pos(int y) { 
    for (const auto& graphic : graphics) {
        graphic->set_y_pos(graphic->get_y_pos() + y);
    }
}

void graphic::set_position(int x, int y) { 
    set_x_pos(x);
    set_y_pos(y);
}

void graphic::render() {
    for (const auto& graphic : graphics) {
        graphic->render();
    }
}