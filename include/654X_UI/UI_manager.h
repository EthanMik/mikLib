#pragma once

#include "vex.h"

void UI_init();
void UI_render();

static void UI_swap_screens(const std::vector<std::shared_ptr<screen>>& scr);

void UI_execute_selector_toggles(std::shared_ptr<UI_component> tgl, std::shared_ptr<screen> scr, bool lock_toggles = false);

