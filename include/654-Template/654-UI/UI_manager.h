#pragma once

#include "vex.h"

void UI_run();

static void UI_display_screen(std::shared_ptr<screen> scr);
static void UI_display_screens(const std::vector<std::shared_ptr<screen>>& render_queue);

void UI_setup_queue_whitelist(std::vector<std::vector<int>> states);
void UI_flush_whitelist();

static void UI_add_function_to_queue(std::function<void()> func, int id);

void UI_flush_queue(); 

static void UI_click(screen* scr);

static void UI_run_toggles(screen* scr);

int bruh();

// extern screen* selector_panel;
// screen* macros_screen_1;
// screen* drive_mode_screen_1;

