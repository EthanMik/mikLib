#include "vex.h"

task UI;

// If you want to disable Brain UI, cut wireless upload times to ~7s
// Go into `makefile` and set `FAST_COMPILE = 1`
static int run_UI() {
    UI_init();
    UI_render();
    return 0;
}

void pre_auton() {
    init({
        // Running the auton selector on the controller disables user control,
        // press X on the controller to close auton selector and enable user control
        .enable_controller_selector = true,

        // Warns disconnected motors and chassis devices. 
        // Displayed on `Error Data` on Config Tab
        .check_disconnected_devices = true
    });

    default_constants();

    UI = task(run_UI);
}

void auton(void) {
    UI.stop();

    // Records the run to run.csv on the SD card so mikGen can overlay it on the planned path.
    // Without an SD card this prints a warning and the auton runs as normal.
    mik::run_log::start("run.csv");
    auton_scr->start_auton();
    mik::run_log::stop();
}

void user_control(void) {
    // An auton still running when the period ends never reaches its own stop(), so the run is
    // written here instead. Does nothing when no run is being recorded.
    mik::run_log::stop();

    while (chassis.calibrating) { task::sleep(50); }

    // How you want your drivetrain to stop during driver
    chassis.set_brake_type(brakeType::coast);

    while (true) {
        if (!control_disabled()) {
            // Add your user control code here
            
            chassis.control(drive_mode::SPLIT_ARCADE);
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
