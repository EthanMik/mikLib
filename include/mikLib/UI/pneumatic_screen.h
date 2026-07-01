#pragma once

#include "mikLib/ui.h"

namespace mik {

class UI_pneumatic_screen {
public:
    UI_pneumatic_screen();
    std::shared_ptr<screen> get_pneumatic_screen();

private:
    void UI_crt_pneumatic_scr();

    std::shared_ptr<screen> UI_pneumatic_scr = nullptr;
};
}
