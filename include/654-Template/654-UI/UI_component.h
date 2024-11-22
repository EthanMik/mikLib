#pragma once

#include "vex.h"

enum class distance_units {inches, centimeters, pixels};

class UI_component {
public:
    virtual ~UI_component() = default;

    virtual void render() = 0;

    virtual int get_x_pos() = 0;
    virtual int get_y_pos() = 0;
    virtual int get_w_pos() = 0;
    virtual int get_h_pos() = 0;

    virtual void set_x_pos(int x) = 0;
    virtual void set_y_pos(int y) = 0;    

    virtual void is_pressing() {}
    virtual void execute() {}

};