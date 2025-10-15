#include "vex.h"

using namespace mik;

#define default_padding 10
#define next_line 20

textbox::textbox(std::string text, std::shared_ptr<drawable> box) :
    text(text), box(box), text_color("#ffffff"), bg_color("#000000"), alignment(text_align::LEFT)
{
    unique_id = UI_create_ID(UI_Textbox_ID);
    
    this->x = get_x_pos();
    this->y = get_y_pos();
    this->w = get_width();
    this->h = get_height();

    wrap_text();
};

textbox::textbox(std::string text, text_align text_alignment, std::shared_ptr<drawable> box) :
    text(text), box(box), text_color("#ffffff"), bg_color("#000000"), alignment(text_alignment)
{
    unique_id = UI_create_ID(UI_Textbox_ID);
    
    this->x = get_x_pos();
    this->y = get_y_pos();
    this->w = get_width();
    this->h = get_height();

    wrap_text();
};

textbox::textbox(std::string text, text_align text_alignment, const std::string& bg_color, std::shared_ptr<drawable> box) :
    text(text), box(box), text_color("#ffffff"), bg_color(bg_color), alignment(text_alignment)
{
    unique_id = UI_create_ID(UI_Textbox_ID);
    
    this->x = get_x_pos();
    this->y = get_y_pos();
    this->w = get_width();
    this->h = get_height();

    wrap_text();
};

textbox::textbox(std::string text, const std::string& text_color, const std::string& bg_color, text_align text_alignment, std::shared_ptr<drawable> box) :
    text(text), box(box), text_color(text_color), bg_color(bg_color), alignment(text_alignment)
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
std::string textbox::get_text() { return(text); }

void textbox::set_x_pos(int x) {
    box->set_x_pos(x);
    this->x = x;
    needs_render_update = true;
}

void textbox::set_y_pos(int y) { 
    box->set_y_pos(y);
    this->y = y;
    needs_render_update = true;
}

void textbox::set_position(int x, int y) { 
    set_x_pos(x);
    set_y_pos(y);
}

void textbox::set_width(int w) { 
    box->set_width(w);
    this->w = w;
    needs_render_update = true;
}
void textbox::set_height(int h) { 
    box->set_height(h);
    this->h = h;
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
    needs_render_update = true;
}

void textbox::wrap_text() {
    std::vector<std::string> words;
    std::istringstream iss(text);
    std::string word;

    while (iss >> word)
        words.push_back(word);
    
    std::string line;
    for (int i = 0; i < words.size(); ++i) {
        if (Brain.Screen.getStringWidth((line + words[i] + " ").c_str()) > w - default_padding) {
            wrapped_text.push_back(line);
            line = "";
        }
        line += words[i] + " ";
    }
    wrapped_text.push_back(line);
}

void textbox::draw_text() {
    int newline = next_line;
    int x_pos = x + default_padding;
    for (int i = 0; i < wrapped_text.size(); ++i) {
        if (alignment == text_align::CENTER) {
            x_pos = x + ((w + default_padding) - Brain.Screen.getStringWidth(wrapped_text[i].c_str())) / 2;
        }
        
        Brain.Screen.setPenColor(text_color.c_str());
        Brain.Screen.setFillColor(bg_color.c_str());
        Brain.Screen.printAt(x_pos, y + newline, wrapped_text[i].c_str());
        // Brain.Screen.setPenColor(vex::color::white);
        newline += next_line;
    }
}

void textbox::render() {
    box->render();
    draw_text();
}