#include "vex.h"

using namespace vex;

vex::competition Competition;

void UI_temp(void) {
  // auto btn = UI_crt_btn(UI_crt_rec(30, 30, 100, 100, vex::color::red, UI_distance_units::pixels), nullptr);
  //   btn->set_states(UI_crt_rec(30, 30, 100, 100, vex::color::blue, UI_distance_units::pixels), UI_crt_rec(30, 30, 100, 100, vex::color::green, UI_distance_units::pixels));
  
  // auto tgl = UI_crt_tgl(UI_crt_rec(130, 130, 100, 100, vex::color::red, UI_distance_units::pixels), nullptr);
  //   tgl->set_states(UI_crt_rec(130, 130, 100, 100, vex::color::blue, UI_distance_units::pixels), UI_crt_rec(130, 130, 100, 100, vex::color::green, UI_distance_units::pixels));
  
  // auto scr = UI_crt_scr(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
  // scr->add_UI_components({btn, tgl});

  // UI_render_queue = {scr};
  // UI_render();


  vex::task UI([](){
    test_palette();
    return 0;
  });
}

void pre_auton() {
  init();
  default_constants();
  UI_temp();
}

void auton(void) {
  // auton_scr->start_auton();
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
  // Competition.autonomous(auton);
  // Competition.drivercontrol(user_control);

  // while (true) {
  //   vex::wait(100, vex::msec);
  // }


  // UI_temp();
  // skills();

  // vex::task e([](){
  //   while(1) {
  //     Brain.Screen.printAt(30, 30, "Active: %d", assembly.is_active);
  //     Brain.Screen.printAt(30, 50, "Scoring: %d", assembly.is_scoring);
  //     Brain.Screen.printAt(30, 70, "Holding: %d", assembly.is_holding);
  //     Brain.Screen.printAt(30, 90, "Hanging: %d", assembly.is_hanging);
  //     Brain.Screen.printAt(30, 110, "Descore_top: %d", assembly.is_descoring_top);
  //     Brain.Screen.printAt(30, 130, "Descore_bot: %d", assembly.is_descoring_bot);
  //     Brain.Screen.printAt(30, 150, "prev: %d", assembly.LB_prev_state);
  //     Brain.Screen.printAt(30, 170, "prev_state: %d", assembly.prev_state);
  //   }
  //   return 0;
  // });

  run_competition();
  
  // skills();
  // thread odom(print_coordinates);
  // print(chassis.get_ForwardTracker_position());
  // assembly.mogo_clamp_piston.set(true);
  // PID_tuner();
  
  // test_spin_all_motors({chassis.left_drive, chassis.right_drive});
}