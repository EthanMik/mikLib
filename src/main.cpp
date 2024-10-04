#include "654-Template/motor_chain.h"
#include "654-Template/manual_drive.h"
#include "654-Template/auton_drive.h"
#include "654-Template/auton_drive_methods.h"
#include "robot-config.h"
#include "vex.h"

#include <chrono>
#include <iostream>
#include <vector>

using namespace vex;

void test_serial_output() {
  // while (true) {
  //   printf("%f\n", Controller.Axis1.position());
  //   fflush(stdout);
  //   wait(100, msec);
  // }
}


void odom_test(){
  chassis.set_coordinates(0, 0, 0);
  while(true){
    Brain.Screen.clearScreen();
    Brain.Screen.printAt(0, 50, "X: %f", chassis.get_X_position());
    Brain.Screen.printAt(0, 70, "Y: %f", chassis.get_Y_position());
    Brain.Screen.printAt(0, 90, "Heading: %f", chassis.get_absolute_heading());
    Brain.Screen.printAt(0, 110, "ForwardTracker: %f", chassis.get_ForwardTracker_position());
    Brain.Screen.printAt(0, 130, "SidewaysTracker: %f", chassis.get_SidewaysTracker_position());
    task::sleep(20);
  }
}

int main() {
  vexcodeInit();

  // manual_drive manual_drive(leftDrive, rightDrive);
  // thread odom(odom_test);

  // while (true) {
  //   manual_tasks.control_split_arcade();
  // }

  turnAlongCircleLeft(30, 270);

  // wait(5, seconds);
  // auton_drive.turn_on_PID(180, 12, 1, 300, 1000000, .4, .03, 3, 15);

  return 0;
}




