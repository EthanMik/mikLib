#include "vex.h"

using namespace vex;

brain Brain;
controller Controller;
inertial Inertial = inertial(PORT2);

motor motorLF(PORT16, ratio36_1, true);
motor motorLM(PORT17, ratio36_1, true);
motor motorLB(PORT19, ratio36_1, true);
motor_chain leftDrive = motor_chain({motorLF, motorLM, motorLB});

motor motorRF(PORT1, ratio36_1, false);
motor motorRM(PORT10, ratio36_1, false);
motor motorRB(PORT18, ratio36_1, false);
motor_chain rightDrive = motor_chain({motorRF, motorRM, motorRB});

//Input Forward Tracker center distance (a positive distance corresponds to a tracker on the right side of the robot, negative is left.)
//Sideways tracker center distance (positive distance is behindcl the center of the robot, negative is in front):
//This distance is in inches:
auton_drive chassis(leftDrive, rightDrive, 2.75, 36/48, PORT20, -2.75, 0, PORT8, 2.75, 5.4);

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