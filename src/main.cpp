#include "vex.h"

using namespace vex;

vex::competition Competition;
int current_auton_selection = 0;
bool auto_started = false;

void pre_auton() {
  init();
  default_constants();

  while(!auto_started) {
    Brain.Screen.printAt(5, 20, "Absolute Heading:");
    Brain.Screen.printAt(5, 40, "%f", chassis.get_absolute_heading());
    Brain.Screen.printAt(5, 80, "Auton:");
    switch(current_auton_selection){
      case 0:
        Brain.Screen.printAt(5, 100, "4 ring Red");
        break;
      case 1:
        Brain.Screen.printAt(5, 100, "4 ring Blue");
        break;
      case 2:
        Brain.Screen.printAt(5, 100, "1 ring Blue");
        break;
      case 3:
        Brain.Screen.printAt(5, 100, "1 ring Red");
        break;
      case 4:
        Brain.Screen.printAt(5, 100, "No Auton       ");
        break;
    }
    if(Brain.Screen.pressing()){
      while(Brain.Screen.pressing()) {}
      current_auton_selection++;
    } else if (current_auton_selection == 5){
      current_auton_selection = 0;
    }
    vex::task::sleep(10);
  }
}

void auton(void) {
  auto_started = true;

  switch (current_auton_selection) { 
    case 0:
      four_ring_red();
      break;
    case 1:
      four_ring_blue();
      break;
    case 2:
      one_ring_blue();
      break;
    case 3:
      one_ring_red();
      break;
    default:
      break;
 }
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
    assembly.match_timer();
    assembly.align_robot();

    vex::task::sleep(20);
  }
}

void UI_temp(void) {
  // auto btn = UI_crt_btn(UI_crt_rec(30, 30, 100, 100, vex::color::red, UI_distance_units::pixels), nullptr);
  //   btn->set_states(UI_crt_rec(30, 30, 100, 100, vex::color::blue, UI_distance_units::pixels), UI_crt_rec(30, 30, 100, 100, vex::color::green, UI_distance_units::pixels));
  
  // auto tgl = UI_crt_tgl(UI_crt_rec(130, 130, 100, 100, vex::color::red, UI_distance_units::pixels), nullptr);
  //   tgl->set_states(UI_crt_rec(130, 130, 100, 100, vex::color::blue, UI_distance_units::pixels), UI_crt_rec(130, 130, 100, 100, vex::color::green, UI_distance_units::pixels));
  
  // auto scr = UI_crt_scr(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
  // scr->add_UI_components({btn, tgl});

  // UI_render_queue = {scr};
  // UI_render();

  // vex::thread UI(test_palette);
}


int main() {
  init();
  default_constants();
  // test_spin_all_motors({chassis.left_drive, chassis.right_drive});

  // four_ring_red();
  chassis.set_coordinates(-60.589, -0.858, 90);

  vex::thread odom(print_coordinates);
  task::sleep(2000);
  skills();

  vex::task hook_pos([](){
    while(1) {
      // Brain.Screen.printAt(30, 30, "%d", assembly.unjam_intake);
    }
    return 0;
  });

  // user_control();
  // // initialize_auton();
  // task::sleep(2000);
  // four_ring_red();
  // user_control();


  // Competition.autonomous(auton);
  // Competition.drivercontrol(user_control);

  // pre_auton();

  // while (true) {
  //   vex::wait(100, vex::msec);
  // }
}







