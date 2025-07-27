#include "vex.h"

using namespace mik;

graphic::graphic() {
    unique_id = UI_create_ID(UI_Graphic_ID);
};

graphic::graphic(std::shared_ptr<drawable> graphic) {
    unique_id = UI_create_ID(UI_Graphic_ID);
    
    graphics.push_back(graphic);

    calculate_bounds();
};

graphic::graphic(std::vector<std::shared_ptr<drawable>> graphics) :
    graphics(graphics)
{
    unique_id = UI_create_ID(1);
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
int graphic::get_size() { return(graphics.size()); }

void graphic::set_x_pos(int x) {
    int delta_x = x - this->x;
    for (const auto& graphic : graphics) {
        graphic->set_x_pos(graphic->get_x_pos() + delta_x);
    }
    needs_render_update = true;
    this->x = x;
}

void graphic::set_y_pos(int y) { 
    int delta_y = y - this->y;
    for (const auto& graphic : graphics) {
        graphic->set_y_pos(graphic->get_y_pos() + delta_y);
    }
    needs_render_update = true;
    this->y = y;
}

void graphic::set_position(int x, int y) { 
    set_x_pos(x);
    set_y_pos(y);
}

void graphic::set_width(int w) { 
    int delta_w = w - this->w;
    for (const auto& graphic : graphics) {
        graphic->set_width(graphic->get_width() + delta_w);
    }
    this->w = w;
}
void graphic::set_height(int h) { 
    int delta_h = h - this->h;
    for (const auto& graphic : graphics) {
        graphic->set_height(graphic->get_height() + delta_h);
    }
    this->h = h;
}

void graphic::add_graphic(std::shared_ptr<drawable> graphic) {
    graphics.push_back(graphic);
    needs_render_update = true;
}


void graphic::replace_graphic(std::shared_ptr<drawable> new_graphic) {
    graphics.clear();
    graphics.push_back(new_graphic);
    needs_render_update = true;
}

void graphic::replace_graphic(std::vector<std::shared_ptr<drawable>> new_graphics) {
    graphics.clear();
    graphics = new_graphics;
    needs_render_update = true;
}

void graphic::remove_first_graphic() {
    graphics.erase(graphics.begin());
    needs_render_update = true;
}

bool graphic::needs_update() {    
    if (needs_render_update) {
        needs_render_update = false;
        return true;
    }
    return false;
}

void graphic::render() {
    for (const auto& graphic : graphics) {
        graphic->render();
    }
}