#pragma once

#include "vex.h"

class UI_manager {
public:
    ~UI_manager();
    
    void run();

    static void display_screen(screen* scr);

    void setup_queue_whitelist(const std::vector<std::vector<int>>& states);
    void flush_whitelist();

    static void add_function_to_queue(std::function<void()> func, int id);

    void flush_queue(); 

    static void click();

    static void run_toggles(screen* scr);
    
private:
    std::vector<std::vector<int>> whitelist;
    static std::unordered_map<int, std::function<void()>> queue;

    screen* start_screen;
    // screen* print_values_screen_1;
    // screen* macros_screen_1;
    // screen* drive_mode_screen_1;

};