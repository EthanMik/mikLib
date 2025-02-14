#include "vex.h"

textbox::textbox(std::string text, std::shared_ptr<drawable> box) :
    text(text), box(box)
{
    unique_id = UI_create_ID(UI_Textbox_ID);

    this->x = get_x_pos();
    this->y = get_y_pos();
    this->w = get_width();
    this->h = get_height();
};

int textbox::get_x_pos() { return(box->get_x_pos()); }
int textbox::get_y_pos() { return(box->get_y_pos()); }
int textbox::get_width() { return(box->get_width()); }
int textbox::get_height() { return(box->get_height()); }

void textbox::set_x_pos(int x) {
    box->set_x_pos(x);
    needs_render_update = true;
}

void textbox::set_y_pos(int y) { 
    box->set_y_pos(y);
    needs_render_update = true;
}

void textbox::set_position(int x, int y) { 
    set_x_pos(x);
    set_y_pos(y);
}

void textbox::set_width(int w) { 
    box->set_width(w);
    needs_render_update = true;
}
void textbox::set_height(int h) { 
    box->set_height(h);
    needs_render_update = true;
}

bool textbox::needs_update() {    
    if (needs_render_update) {
        needs_render_update = false;
        return true;
    }
    return false;
}

void textbox::render() {
    // box->render();
    // Brain.Screen.setFont(vex::fontType::mono20);    Brain.Screen.setFillColor(vex::red);
    // printf("%f\n", Brain.Screen.getStringHeight(text.c_str()));
    // Brain.SDcard.
    // Brain.Screen.printAt(x, y + 16, text.c_str());
}