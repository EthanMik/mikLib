#include "vex.h"

using namespace vex;
using namespace mik;

task UI;

static int run_UI() {
    UI_init();
    UI_controller_auton_selector();
    UI_render();
    return 0;
}

void pre_auton() {
    init();
    default_constants();
    UI = task(run_UI);
}

void auton(void) {
    UI.stop();
    auton_scr->start_auton();
}

void user_control(void) {
    while (calibrating) { task::sleep(50); }

    // How you want your drivetrain to stop during driver
    chassis.set_brake_type(brakeType::coast);
    
    assembly.init();

    while (true) {
        if (!control_disabled()) {
            // Add your user control code here
            chassis.control(drive_mode::SPLIT_ARCADE_CURVED);
            assembly.control();
        }
        task::sleep(5);
    }
}

int main() {
    Competition.autonomous(auton);
    Competition.drivercontrol(user_control);

    pre_auton();

    while (true) {
        task::sleep(100);
    }
}
