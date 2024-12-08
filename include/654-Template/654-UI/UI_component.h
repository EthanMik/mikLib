#pragma once

#include "vex.h"

enum class UI_distance_units {inches, centimeters, pixels};

//   ID-1 -> Graphic
//   ID-2 -> Background
//   ID-3 -> Label
//   ID-4 -> Button
//   ID-5 -> Toggle

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

    virtual void is_pressing() {}
    
    virtual void set_callback(std::function<void()> cb) {}
    virtual void set_states(std::shared_ptr<drawable> pressing, std::shared_ptr<drawable> triggered) {}

    virtual int get_ID() const { return unique_id; }
    virtual void set_ID(int id) { unique_id = id; }
};