#include "vex.h"

using namespace vex;

competition Competition;
int current_auton_selection = 0;
bool auto_started = false;

void win_point_blue(void) {
  chassis.drive_on_PID(-26);
  chassis.turn_on_PID(30);
  chassis.drive_on_PID(-9);
  assembly.mogo_clamp_piston.set(true);
  chassis.turn_on_PID(100);
  assembly.intake_motor.spin(fwd, 12, volt);
  chassis.drive_max_voltage = 6;
  chassis.drive_on_PID(35);

}

void win_point_red(void) {
  chassis.drive_on_PID(-26);
  chassis.turn_on_PID(330);
  chassis.drive_on_PID(-9);
  assembly.mogo_clamp_piston.set(true);
  chassis.turn_on_PID(260);
  assembly.intake_motor.spin(fwd, 12, volt);
  chassis.drive_max_voltage = 6;
  chassis.drive_on_PID(35);

}

void goal_rush(void) {
  chassis.drive_on_PID(-23);
  chassis.turn_on_PID(340);
  chassis.drive_on_PID(-24);
  assembly.mogo_clamp_piston.set(true);
}

void pre_auton() {
  init();
  default_constants();

  while(!auto_started) {
    Brain.Screen.printAt(5, 20, "Absolute Heading:");
    Brain.Screen.printAt(5, 40, "%f", chassis.get_absolute_heading());
    Brain.Screen.printAt(5, 80, "Auton:");
    switch(current_auton_selection){
      case 0:
        Brain.Screen.printAt(5, 100, "Win point Red");
        break;
      case 1:
        Brain.Screen.printAt(5, 100, "Win point Blue");
        break;
      case 2:
        Brain.Screen.printAt(5, 100, "Goal Rush      ");
        break;
      case 3:
        Brain.Screen.printAt(5, 100, "No Auton       ");
        break;
    }
    if(Brain.Screen.pressing()){
      while(Brain.Screen.pressing()) {}
      current_auton_selection++;
    } else if (current_auton_selection == 4){
      current_auton_selection = 0;
    }
    task::sleep(10);
  }
}

void auton(void) {
  auto_started = true;
  switch (current_auton_selection) { 
    case 0:
      win_point_red();
      break;
    case 1:
      win_point_blue();
      break;
    case 2:
      goal_rush();
      break;
    case 3:
      break;
 }
}

void user_control(void) {
  assembly.user_control_tasks();
}


int main() {
  init();
  default_constants();

/* ------------------THREADS----------------------- */
  // print_coordinates();

  // How to use console screen
  int sum = 0;
  UI_console_scr_add(sum); // variable render updates occur every 100ms
  UI_console_scr_add("text"); // can add text
  UI_console_scr_add([](){ return chassis.get_X_position(); }); // can add functions but they must not be void!!!

  while(true) {
    sum++;
    task::sleep(10); // make sure you dont flood cpu
  }
/* ------------------------------------------------ */

  // Competition.autonomous(auton);
  // Competition.drivercontrol(user_control);

  // pre_auton();

  // while (true) {
  //   wait(100, msec);
  // }
}







