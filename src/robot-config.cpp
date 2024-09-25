#include "654-Template/auton_drive.h"
#include "vex.h"

using namespace vex;

brain Brain;
controller Controller;
inertial Inertial = inertial(PORT20);


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