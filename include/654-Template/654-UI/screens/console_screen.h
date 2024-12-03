#pragma once

#include "vex.h"

extern std::shared_ptr<screen> UI_console_scr;
extern int text_start_pos_x;
extern int text_start_pos_y;

extern std::shared_ptr<UI_component> UI_console_scr_border_sides;
extern std::shared_ptr<UI_component> UI_console_scr_border_bottom;

void UI_crt_console_scr();

void UI_console_scr_add();
