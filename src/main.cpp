#include "vex.h"

using namespace vex;

vex::competition Competition;
int current_auton_selection = 0;
bool auto_started = false;

void four_ring_red(void) {
  chassis.drive_on_PID(-21);
  chassis.turn_on_PID(340);
  chassis.drive_max_voltage = 5;
  chassis.drive_on_PID(-11);
  assembly.mogo_clamp_piston.set(true);
  chassis.turn_on_PID(106);
  assembly.intake_motor.spin(vex::fwd, 12, vex::volt);
  chassis.drive_on_PID(18);
  wait(1, vex::sec);
  assembly.intake_motor.spin(vex::reverse, 12, vex::volt);
  chassis.turn_on_PID(160);
  assembly.intake_motor.spin(vex::fwd, 12, vex::volt);
  chassis.drive_on_PID(15);
  wait(1, vex::sec);
  chassis.drive_on_PID(-10);
  chassis.turn_on_PID(140);
  chassis.drive_on_PID(13);
  wait(3, vex::sec);
  assembly.intake_motor.stop();
}

void four_ring_blue(void) {
  chassis.drive_on_PID(-21);
  chassis.turn_on_PID(20);
  chassis.drive_max_voltage = 5;
  chassis.drive_on_PID(-11);
  assembly.mogo_clamp_piston.set(true);
  chassis.turn_on_PID(254);
  assembly.intake_motor.spin(vex::fwd, 12, vex::volt);
  chassis.drive_on_PID(18);
  wait(1, vex::sec);
  assembly.intake_motor.spin(vex::reverse, 12, vex::volt);
  chassis.turn_on_PID(200);
  assembly.intake_motor.spin(vex::fwd, 12, vex::volt);
  chassis.drive_on_PID(15);
  wait(1, vex::sec);
  chassis.drive_on_PID(-10);
  chassis.turn_on_PID(220);
  chassis.drive_on_PID(13);
  wait(3, vex::sec);
  assembly.intake_motor.stop();
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
        Brain.Screen.printAt(5, 100, "4 ring Red");
        break;
      case 1:
        Brain.Screen.printAt(5, 100, "4 ring Blue");
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
      break;
 }
}

void user_control(void) {
  assembly.user_control_tasks();
}

int main() {
  // init();
  // default_constants();
  // vex::thread odom(print_coordinates);
  // chassis.drive_on_PID(2);
  // assembly.intake_motor.spin(fwd, 12, volt);
  // task::sleep(300);
  // assembly.intake_motor.spin(fwd, -12, volt);
  // chassis.drive_on_PID(12);
  // assembly.intake_motor.stop();



  // vex::thread odom(print_coordinates);
  // chassis.drive_to_pose(10, 30, 0);

/* ------------------THREADS----------------------- */

  // chassis.drive_on_PID(10);
  // turn_right_arc(30,90,0.4,false);
  // left_spiral(30, 180, 0.4);
  // How to use console screen
  // int sum = 0;
  // console_scr->add(sum); // variable render updates occur every 100ms

  // console_scr->add("text"); // can add text
  // console_scr->add("Sum = ", sum); // can add text with variables
  // console_scr->add([](){ return chassis.get_X_position(); }); // can add functions but they must not be void!!!

  // while(true) {
  //   sum++;
  //   task::sleep(10); // make sure you dont flood cpu
  // }
  
/* ------------------------------------------------ */


  Competition.autonomous(auton);
  Competition.drivercontrol(user_control);

  pre_auton();

  while (true) {
    vex::wait(100, vex::msec);
  }
}

      // CS3 Ranking // 
/*
Stanley Project with picross - High mid (100)
Unity Flappy Bird + Toaster timed reaction game - low mid (85)
Guy who learned HR how to talk with people - so low i cant rank (40)
Unity Platformer - High mid (100)
Google IT Certification - very low (70)
Unity Flappy Bird - very low + stolen assets + tutorial + cap (60)
Java vs. Python??? - so low i cant rank (50)

*/







