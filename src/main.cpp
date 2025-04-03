#include "vex.h"

using namespace vex;

vex::competition Competition;
int current_auton_selection = 0;
bool auto_started = false;
bool update_coords = true;

void pre_auton() {
  init();
  default_constants();

  while(!auto_started) {
    Brain.Screen.printAt(5, 20, "Absolute Heading:");
    Brain.Screen.printAt(5, 40, "%f", chassis.get_absolute_heading());
    Brain.Screen.printAt(5, 80, "Auton:");
    switch(current_auton_selection){
      case 0:
        Brain.Screen.printAt(5, 100, "Goalside Red  ");
        if (update_coords) {
          goalside_red(true);
          update_coords = false;
        }
        break;
      case 1:
        Brain.Screen.printAt(5, 100, "Goalside Blue ");
        if (update_coords) {
          goalside_blue(true);
          update_coords = false;
        }
        break;
      case 2:
        Brain.Screen.printAt(5, 100, "Ringside Red  ");
        if (update_coords) {
          ring_side_red(true);
          update_coords = false;
        }
        break;
      case 3:
        Brain.Screen.printAt(5, 100, "Ringside Blue  ");
        if (update_coords) {
          ring_side_blue(true);
          update_coords = false;
        }
        break;
      case 4:
        Brain.Screen.printAt(5, 100, "Winpoint Red  ");
        if (update_coords) {
          win_point_red(true);
          update_coords = false;
        }
        break;
      case 5:
        Brain.Screen.printAt(5, 100, "Winpoint Blue ");
        if (update_coords) {
          win_point_blue(true);
          update_coords = false;
        }
        break;
      case 6:
        Brain.Screen.printAt(5, 100, "SAWP Red      ");
        if (update_coords) {
          solo_win_point_red(true);
          update_coords = false;
        }
        break;
        case 7:
        Brain.Screen.printAt(5, 100, "SAWP Blue     ");
        if (update_coords) {
          solo_win_point_blue(true);
          update_coords = false;
        }
        break;
      case 8:
        Brain.Screen.printAt(5, 100, "No Auton      ");
        break;
    }
    if(Brain.Screen.pressing()){
      while(Brain.Screen.pressing()) {}
      current_auton_selection++;
      update_coords = true;
    } else if (current_auton_selection == 9){
      current_auton_selection = 0;
    }
    vex::task::sleep(10);
  }
}

void auton(void) {
  skills();
  // auto_started = true;

//   switch (current_auton_selection) { 
//     case 0:
//       goalside_red();
//       break;
//     case 1:
//       goalside_blue();
//       break;
//     case 2:
//       ring_side_red();
//       break;
//     case 3:
//       ring_side_blue();
//       break;
//     case 4:
//       win_point_red();
//       break;
//     case 5:
//       win_point_blue();
//       break;
//     case 6:
//       solo_win_point_red();
//       break;
//     case 7:
//       solo_win_point_blue();
//       break;
//     default:
//       break;
//  }
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

void UI_temp(void) {
  // auto btn = UI_crt_btn(UI_crt_rec(30, 30, 100, 100, vex::color::red, UI_distance_units::pixels), nullptr);
  //   btn->set_states(UI_crt_rec(30, 30, 100, 100, vex::color::blue, UI_distance_units::pixels), UI_crt_rec(30, 30, 100, 100, vex::color::green, UI_distance_units::pixels));
  
  // auto tgl = UI_crt_tgl(UI_crt_rec(130, 130, 100, 100, vex::color::red, UI_distance_units::pixels), nullptr);
  //   tgl->set_states(UI_crt_rec(130, 130, 100, 100, vex::color::blue, UI_distance_units::pixels), UI_crt_rec(130, 130, 100, 100, vex::color::green, UI_distance_units::pixels));
  
  // auto scr = UI_crt_scr(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
  // scr->add_UI_components({btn, tgl});

  // UI_render_queue = {scr};
  // UI_render();


  vex::thread UI(test_palette);
}

void skills_driver_run() {
  Controller.Screen.setCursor(1, 1);
  Controller.Screen.print("SKILLS DRIVER RUN               ");
  task::sleep(1000);
  Controller.Screen.setCursor(1, 1);
  Controller.Screen.print("             3                 ");
  Controller.rumble(".");
  task::sleep(1000);
  Controller.Screen.setCursor(1, 1);
  Controller.Screen.print("             2                 ");
  Controller.rumble(".");
  task::sleep(1000);
  Controller.Screen.setCursor(1, 1);
  Controller.Screen.print("             1                 ");
  Controller.rumble(".");
  task::sleep(1000);
  Controller.Screen.setCursor(1, 1);
  Controller.Screen.print("            GO                 ");
  Controller.rumble("-");
  Controller.Screen.setCursor(1, 1);
  Controller.Screen.print("                               ");

  vex::task time_left([](){
    while(1) {
      Controller.Screen.setCursor(1, 1);
      Controller.Screen.print("           ");
      Controller.Screen.print(assembly.time_remaining);
      Controller.Screen.print("  ");
    }
    return 0;
  });

  user_control();
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
  Competition.autonomous(auton);
  Competition.drivercontrol(user_control);

  pre_auton();

  while (true) {
    vex::wait(100, vex::msec);
  }
  // init();
  // default_constants();
  // UI_temp();
  // skills();
  // run_competition();
  
  // assembly.mogo_clamp_piston.set(true);
  // PID_tuner();
  
  // test_spin_all_motors({chassis.left_drive, chassis.right_drive});
}