#include "vex.h"

using namespace vex;

vex::task UI;

void pre_auton() {
  init();
  default_constants();
  
  UI = vex::task([](){
    UI_init();
    auton_scr->enable_controller_overlay();
    UI_render();
    return 0;
  });
}

void auton(void) {
  auton_scr->start_auton();
}

void user_control(void) {
  auton_scr->end_auton();
  assembly.initialize_user_control();
  chassis.set_brake_type(vex::brakeType::coast);

  while (1) {
    if (!disable_user_control) {
      chassis.control(drive_mode::SPLIT_ARCADE);
      assembly.select_ring_sort_mode();
      assembly.intake();
      assembly.lady_brown();
      assembly.mogo_clamp();
      assembly.doinker();
      // assembly.match_timer();
      assembly.align_robot();
    }
    vex::task::sleep(5);
  }
}

int main() {
  Competition.autonomous(auton);
  Competition.drivercontrol(user_control);
  
  pre_auton();

  while (1) {
    task::sleep(100);
  }
}
