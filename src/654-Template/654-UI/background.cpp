#include "vex.h"

background::background(std::shared_ptr<drawable> graphic) { 
    this->graphic = graphic;
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
    position_is_set = true;
}

void background::set_y_pos(int y) { 
    if (!position_is_set) {
        graphic->set_y_pos(y);
    }
    position_is_set = true;
}

void background::set_position(int x, int y) { 
    if (!position_is_set) {
        graphic->set_x_pos(x);
        graphic->set_y_pos(y);
    }
    position_is_set = true;
}

void background::render() {
    graphic->render();
}
