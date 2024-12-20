#pragma once

#include "vex.h"

extern std::vector<std::shared_ptr<screen>> UI_render_queue;
extern std::vector<std::shared_ptr<screen>> UI_render_buffer;

extern std::shared_ptr<UI_console_screen> console_scr;
// extern std::shared_ptr<screen> UI_console_scr; 

extern std::shared_ptr<UI_auton_screen> auton_scr;
// extern std::shared_ptr<screen> UI_auton_scr; 


extern bool is_screen_swapping;

void UI_init();
void UI_render();

static void UI_swap_screens(const std::vector<std::shared_ptr<screen>>& scr);

void UI_execute_selector_toggles(std::shared_ptr<UI_component> tgl, std::shared_ptr<screen> scr, bool lock_toggles = false);

