#include "vex.h"

using namespace vex;

void test_serial_output() {
  while (true) {
    printf("%f\n", Controller.Axis1.position());
    fflush(stdout);
    wait(1, sec);
  }
}

void print_coordinates() {
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
  // test_serial_output();
  //(maxVoltage, kP, kI, kD, startI).
  //chassis.set_drive_constants(10, 1.5, 0, 10, 0);
  //chassis.set_heading_constants(6, .4, 0, 1, 0);
  // chassis.heading_max_voltage = 10;
  // chassis.drive_max_voltage = 8;
  // chassis.drive_settle_error = 3;
  // chassis.boomerang_lead = .5;
  // chassis.drive_min_voltage = 0;

  // Each exit condition set is in the form of (settle_error, settle_time, timeout).
  //chassis.set_drive_exit_conditions(1.5, 300, 5000);
  //chassis.set_turn_exit_conditions(1, 300, 3000);
  //thread odom(print_coordinates);
  // chassis.drive_to_pose(30, -50, 180, 0.45, 1, 0, 8, 10, 1.5, 300, 5000, 1.5, 0, 10, 0, .4, 0, 1, 0);

  //chassis.turn_left_arc(30, 180, 1);

  // motorRF.spinFor(1, sec);
  // wait(1, sec);
  // motorRF.spinFor(1, sec);
  // wait(1, sec);
  // motorRF.spinFor(1, sec);
  // wait(1, sec);

  // wait(1, sec);
  
  // motorLF.spinFor(1, sec);
  // wait(1, sec);
  // motorLF.spinFor(1, sec);
  // wait(1, sec);
  // motorLF.spinFor(1, sec);
  // wait(1, sec);

  //spin_motors({leftDrive, leftDrive});

  // wait(5, seconds);
  // auton_drive.turn_on_PID(180, 12, 1, 300, 1000000, .4, .03, 3, 15);

  return 0;
}




