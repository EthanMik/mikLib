#pragma once

#include "vex.h"

void UI_init();
void UI_render();

extern std::shared_ptr<UI_auton_screen> auton_scr;
extern std::shared_ptr<UI_console_screen> console_scr;
extern std::shared_ptr<UI_graph_screen> graph_scr;
extern std::shared_ptr<UI_config_screen> config_scr;

extern std::vector<std::shared_ptr<screen>> UI_render_queue;

void UI_swap_screens(const std::vector<std::shared_ptr<screen>>& scr);

void UI_select_scr(std::shared_ptr<screen> scr);

void UI_execute_selector_toggles(std::shared_ptr<UI_component> tgl, std::shared_ptr<screen> scr, bool lock_toggles = false);

