#include "vex.h"

using namespace vex;

vex::competition Competition;
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
    chassis.split_arcade();
    assembly.select_ring_sort_mode();
    assembly.intake();
    assembly.lady_brown();
    assembly.mogo_clamp();
    assembly.doinker();
    // assembly.match_timer();
    assembly.align_robot();

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

  // pre_auton();
  // skills(false);

  // chassis.set_coordinates(0, 54.5, 0);

  // while(1) {
  //   distance_reset();
  //   Brain.Screen.printAt(30, 70, " X_r: %f", chassis.get_X_position());
  //   Brain.Screen.printAt(30, 90, " Y:_r %f", chassis.get_Y_position());

  // }

  // pre_auton();
  // vex::task e([](){
  //   while(1) {
  //     Brain.Screen.printAt(30, 30, "%f", chassis.left_drive.get_wattage());
  //     Brain.Screen.printAt(30, 50, "%f", chassis.right_drive.get_wattage());
  //   }
  //   return 0;
  // });
  // user_control();
  run_competition();
  // LB_task(ACTIVE);
  // ring_side_red(true);
  // ring_side_red(false);


  // // user_control();
  // // test_turn();  
}