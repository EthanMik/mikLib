#pragma once

#include "vex.h"

class toggle : public UI_component
{
public:
    toggle(const std::string& toggle_file_name, const std::string& toggled_file_name, int x, int y, int w, int h, distance_units units, std::function<void()> callback, int id);
    toggle(const std::string& toggle_file_name, const std::string& toggled_file_name, int x, int y, int w, int h, distance_units units, std::function<void()> callback);
    toggle(const std::string& toggle_file_name, const std::string& toggled_file_name, int x, int y, int w, int h, distance_units units);

    int get_x_pos() override;
    int get_y_pos() override;
    int get_w_pos() override;
    int get_h_pos() override;

    void set_x_pos(int x) override;
    void set_y_pos(int y) override;

    void render() override;

    void is_pressing() override;

    void execute();

    bool get_toggle_state();
    int get_toggle_id();

private:
    std::string toggle_file_name;
    std::string toggled_file_name;
    int x;
    int y;
    int w;
    int h;
    distance_units units;
    std::function<void()> callback;
    int id;

    bool pressed = false;
    bool is_toggled = false;
};