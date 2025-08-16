#include "vex.h"

using namespace mik;

background::background(std::shared_ptr<drawable> graphic) { 
    this->graphic = graphic;
    unique_id = UI_create_ID(UI_Background_ID);
    x = get_x_pos();
    y = get_y_pos();
    w = get_width();
    h = get_height();
};

int background::get_x_pos() { return(graphic->get_x_pos()); }
int background::get_y_pos() { return(graphic->get_y_pos()); }
int background::get_width() { return(graphic->get_width()); }
int background::get_height() { return(graphic->get_height()); }

void background::set_x_pos(int x) {
    if (!position_is_set) {
        graphic->set_x_pos(x);
    }
    needs_render_update = true;
    position_is_set = true;
}

void background::set_y_pos(int y) { 
    if (!position_is_set) {
        graphic->set_y_pos(y);
    }
    needs_render_update = true;
    position_is_set = true;
}

void background::set_position(int x, int y) { 
    if (!position_is_set) {
        graphic->set_x_pos(x);
        graphic->set_y_pos(y);
    }
    position_is_set = true;
}

bool background::needs_update() {
    if (needs_render_update) {
        needs_render_update = false;
        return true;
    }
    return false;
}

void background::render() {
    graphic->render();
}
