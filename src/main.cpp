#include "654-Template/motor_chain.h"
#include "654-Template/manual_drive.h"
#include "654-Template/auton_drive.h"
#include "robot-config.h"
#include "vex.h"

using namespace vex;

int main() {
  vexcodeInit();

  motor_chain leftDrive(PORT1, false, PORT2, false, PORT3, false, ratio18_1);
  motor_chain rightDrive(PORT7, false, PORT7, false, PORT9, false, ratio18_1);

  manual_drive manual_drive(leftDrive, rightDrive);
  auton_drive auton();

  manual_drive.control_drive_tasks();
  
}
