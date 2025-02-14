#pragma once

#include "vex.h"

enum class UI_distance_units {inches, centimeters, pixels};
enum class input_type { CONTROLLER, TOUCHSCREEN };

#define UI_Graphic_ID    1
#define UI_Background_ID 2
#define UI_Label_ID      3
#define UI_Button_ID     4
#define UI_Toggle_ID     5
#define UI_Textbox_ID    6

class UI_component {
protected:
    int unique_id = -1;
public:

    virtual ~UI_component() = default;

    virtual bool needs_update() = 0;
    virtual void render() = 0;

    virtual int get_x_pos() = 0;
    virtual int get_y_pos() = 0;
    virtual int get_width() = 0;
    virtual int get_height() = 0;

    virtual void set_x_pos(int x) = 0;
    virtual void set_y_pos(int y) = 0;    
    virtual void set_position(int x, int y) = 0;
    virtual void set_width(int w) {}
    virtual void set_height(int h) {}

    virtual void is_pressing(input_type input_type) {}
    
    virtual void set_callback(std::function<void()> cb) {}
    virtual void set_states(std::shared_ptr<drawable> pressing, std::shared_ptr<drawable> triggered) {}

    virtual int get_ID() const { return unique_id; }
    virtual void set_ID(int id) { unique_id = id; }
    virtual void blacklist_ID() { unique_id = unique_id > 0 ? unique_id * -1 : unique_id; }
    virtual void whitelist_ID() { unique_id = unique_id < 0 ? unique_id * -1 : unique_id; }
};