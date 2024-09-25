#include "654-Template/motor_chain.h"
#include "654-Template/manual_drive.h"
#include "654-Template/auton_drive.h"
#include "robot-config.h"
#include "vex.h"

#include <chrono>
#include <iostream>
#include <vector>

using namespace vex;

int main() {
  vexcodeInit();

  motor_chain leftDrive(PORT11, true, PORT19, true, PORT18, true, ratio18_1);
  motor_chain rightDrive(PORT1, false, PORT9, false, PORT10, false, ratio18_1);

  manual_drive manual_drive(leftDrive, rightDrive);
  auton_drive auton_drive(leftDrive, rightDrive);

  wait(5, seconds);
  auton_drive.turn_on_PID(180, 12, 1, 300, 1000000, .4, .03, 3, 15);
  
  return 0;
}


