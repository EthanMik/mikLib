#include "vex.h"

textbox::textbox(std::string text, std::shared_ptr<drawable> box) :
    text(text), box(box)
{
    unique_id = UI_create_ID(UI_Textbox_ID);
    
    this->x = get_x_pos();
    this->y = get_y_pos();
    this->w = get_width();
    this->h = get_height();

    wrap_text();
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

void textbox::set_text(std::string text) {
    wrapped_text.clear();
    this->text = text;
    wrap_text();
    needs_render_update = false;
}

void textbox::wrap_text() {
    std::vector<std::string> words;
    std::istringstream iss(text);
    std::string word;
    while (iss >> word)
        words.push_back(word);
    
    std::string line;
    for (int i = 0; i < words.size(); ++i) {
        if (Brain.Screen.getStringWidth((line + words[i] + " ").c_str()) > w-10) {
            wrapped_text.push_back(line);
            line = "";
        }
        line += words[i] + " ";
    }
    wrapped_text.push_back(line);
}

void textbox::draw_text() {
    int newline = 20;
    for (int i = 0; i < wrapped_text.size(); ++i) {
        Brain.Screen.printAt(x+10, y + newline, wrapped_text[i].c_str());
        newline+=20;
    }
}

void textbox::render() {
    box->render();
    draw_text();
}