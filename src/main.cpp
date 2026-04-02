#include "vex.h"

task UI;

// If you want to disable Brain UI, and reduce upload times
// Go into `makefile` and set `FAST_COMPILE = 1`
static int run_UI() {
    UI_init();

    // Running the auton selector on the controller disables user control,
    // press X on the controller to close auton selector and enable user control
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
    while (chassis.calibrating) { task::sleep(50); }

    enable_user_control();

    // How you want your drivetrain to stop during driver
    chassis.set_brake_type(brakeType::coast);

    while (true) {
        if (!control_disabled()) {
            // Add your user control code here
            chassis.control(drive_mode::SPLIT_ARCADE);
            // assembly.control();
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
