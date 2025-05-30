#include "vex.h"

using namespace vex;

vex::task UI;

void pre_auton() {
  init();
  default_constants();

  UI = vex::task([](){
    UI_init();
    UI_render();
    return 0;
  });
}

void auton(void) {
  auton_scr->start_auton();
}

void user_control(void) {
  assembly.initialize_user_control();
  
  while(1) {
    if (!disable_user_control) {
      chassis.split_arcade();
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


void run_competition() {
  Competition.autonomous(auton);
  Competition.drivercontrol(user_control);

  pre_auton();

  while (true) {
    vex::wait(100, vex::msec);
  }
}

int main() {
  run_competition();
}