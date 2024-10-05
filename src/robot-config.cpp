#include "654-Template/auton_drive.h"
#include "vex.h"

using namespace vex;

brain Brain;
controller Controller;
inertial Inertial = inertial(PORT20);

motor motorLF(PORT11, ratio18_1, true);
motor motorLM(PORT19, ratio18_1, true);
motor motorLB(PORT18, ratio18_1, true);
motor_chain leftDrive = motor_chain({motorLF, motorLM, motorLB});

motor motorRF(PORT1, ratio18_1, false);
motor motorRM(PORT9, ratio18_1, false);
motor motorRB(PORT10, ratio18_1, false);
motor_chain rightDrive = motor_chain({motorRF, motorRM, motorRM});

//Input Forward Tracker center distance (a positive distance corresponds to a tracker on the right side of the robot, negative is left.)
//Sideways tracker center distance (positive distance is behind the center of the robot, negative is in front):
//This distance is in inches:

auton_drive chassis(leftDrive, rightDrive, 2.75, 36/48, PORT12, -2.75, 1.3125, PORT5, -2.75, -1.75);
manual_drive manual_tasks(leftDrive, rightDrive);

void vexcodeInit( void ) {
  Brain.Screen.print("Device initialization...");
  Brain.Screen.setCursor(2, 1);

  wait(200, msec);
  Inertial.calibrate();

  while (Inertial.isCalibrating()) {
    wait(25, msec);
  }

  Brain.Screen.clearScreen();
  Brain.Screen.setCursor(1,1);
  wait(50, msec);
  Brain.Screen.clearScreen();
}